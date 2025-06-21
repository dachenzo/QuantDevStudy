// cache_latency_fixed.cpp
#include <cstdint>
#include <iostream>
#include <vector>
#include <thread>
#include <sched.h>      // for CPU_ZERO / CPU_SET / sched_setaffinity on Linux
#include <x86intrin.h>  // for _mm_clflush, __rdtscp, _mm_lfence

// Helper to pin THIS thread to core 0 (Linux). Omit or adapt if you're on Windows.
static void pin_to_core0() {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    if (sched_setaffinity(0, sizeof(cpuset), &cpuset) != 0) {
        std::cerr << "WARNING: failed to set CPU affinity\n";
    }
}

// A fully-serialized RDTSC read (returns cycle count).
static inline uint64_t rdtsc_serialized() {
    unsigned aux;
    _mm_lfence();                // wait for any prior loads to finish
    uint64_t t = __rdtscp(&aux); // read TSC (serialized)
    _mm_lfence();                // prevent later loads from starting early
    return t;
}

int main() {
    pin_to_core0(); // lock to core 0—important to keep TSC consistent

    constexpr size_t BUF_SIZE = 16 * 1024 * 1024; // 16 MiB (bigger than most L3s)
    constexpr size_t STRIDE   = 64;               // one full cache line
    constexpr int    ITER     = 5'000'000;        // 5 million samples

    // Allocate and touch the buffer so pages are mapped.
    std::vector<uint8_t> buffer(BUF_SIZE, 0xAB);
    volatile uint8_t sink;       // ‘volatile’ prevents the compiler from optimizing away our loads

    // Pick a target offset (somewhere in the buffer).
    size_t target_idx = STRIDE * 10;

    // === PHASE 1: Measure “just fence+timestamp” overhead ===
    uint64_t sumOverhead = 0;
    for (int i = 0; i < ITER; i++) {
        _mm_lfence();
        unsigned aux1;
        uint64_t t1 = __rdtscp(&aux1);
        _mm_lfence();

        // —— NO load here —— 

        _mm_lfence();
        unsigned aux2;
        uint64_t t2 = __rdtscp(&aux2);
        _mm_lfence();

        sumOverhead += (t2 - t1);
    }
    double avgOverhead = double(sumOverhead) / double(ITER);

    // === PHASE 2: Measure “fence+timestamp + ONE L1 load” ===
    // Warm the line into L1 exactly once:
    sink = buffer[target_idx]; // now buffer[target_idx] lives in L1

    uint64_t sumWithLoad = 0;
    for (int i = 0; i < ITER; i++) {
        _mm_lfence();
        unsigned aux1;
        uint64_t t1 = __rdtscp(&aux1);
        _mm_lfence();

        // ----- The single load we want to time (true L1 hit) -----
        sink = buffer[target_idx];
        // ---------------------------------------------------------

        _mm_lfence();
        unsigned aux2;
        uint64_t t2 = __rdtscp(&aux2);
        _mm_lfence();

        sumWithLoad += (t2 - t1);
    }
    double avgWithLoad = double(sumWithLoad) / double(ITER);

    // === PHASE 3: Subtract to isolate “pure L1‐hit” ===
    double avgL1hit = avgWithLoad - avgOverhead;

    std::cout << "Average fence+RDTSC overhead:       " << avgOverhead
              << " cycles\n";
    std::cout << "Average (overhead + single L1 load): " << avgWithLoad
              << " cycles\n";
    std::cout << "=> Pure L1‐hit latency:             " << avgL1hit
              << " cycles\n";

    (void)sink; // just to silence any warning

    return 0;
}
