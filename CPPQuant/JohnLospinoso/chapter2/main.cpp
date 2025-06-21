#include <cstdio>

enum class Days {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday
};

const char* toString(Days day) {
    switch(day) {
        case Days::Friday: return "Friday";
        default: return "unknown";
    }
}

int main() {
    Days today = Days::Monday;

}