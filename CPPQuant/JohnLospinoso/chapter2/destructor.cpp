#include <cstdint>
#include <cstdlib>
#include <cstdio>

struct Earth{
    ~Earth() // CANNOT TAKE ARGUMENTS
    {
        printf("Making way for Mike");
    }
};

