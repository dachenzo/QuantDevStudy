#include <chrono>

struct Timer {
    Timer() {
        auto now = std::chrono::system_clock::now();
        timestamp = std::chrono::system_clock::to_time_t(now);
    }

    ~Timer() {
        
    }
    private:
    std::time_t timestamp;
};   