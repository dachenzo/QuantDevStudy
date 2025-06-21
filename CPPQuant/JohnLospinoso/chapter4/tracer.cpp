#include <cstdio>

struct Tracer {
    Tracer(const char* name): name{name} {
        printf("%s Constructed\n", name);
    }

    ~Tracer() {
        printf("%s destructured\n", name);
    }

    private:
    const char* name;
};


static Tracer t1{"Static Variable"};
thread_local Tracer t2{"Thread-local variable"};



int main() {
    Tracer t3{"Automatic variable"};
    const auto* t4 = new Tracer{"Dynamic Variable"};

    (void)&t2;

    delete t4;

    // pause so we can see everything in the console
    printf("Press Enter to exit…");
    getchar();

}
