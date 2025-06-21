#include <cstdio>
#include <utility>

void ref_type(int& x) {
    printf("Lvalue reference for %d\n", x);
}

void ref_type(int&& x) {
    printf("Rvalue reference for %d\n", x);
}


int main() {
    int x = 4;
    ref_type(std::move(x));
    ref_type(2);
    ref_type(x+5);
}