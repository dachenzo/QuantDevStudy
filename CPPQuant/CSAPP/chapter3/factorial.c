long fact_while(long n) {
    long result = 1;
    while (n>1) {
        result *= n;
        n -= 1;
    }
    return result;
}

short test_one(unsigned short x) {
    short val = 1;
    while (x != 0) {
        val ^= x;
        x >>= 1;
    }
    val &= 1;
    return val;
}

int main() {}