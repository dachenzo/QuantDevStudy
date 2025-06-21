#include <stdio.h>
void multstore(long, long, long*);

int main() {
    long d;
    multstore(2, 3, &d);
    printf("2 * 3 -> %ld\n", d);
    return 0;
}

void decode1(long* xp, long* yp, long* zp) {
    long x = *xp;
    long y = *yp;
    long z = *zp;
    *yp = x;
    *zp = y;
    *xp = z;
    return;
}

long mult2(long a, long b) {
    long s = a*b;
    return s;
}