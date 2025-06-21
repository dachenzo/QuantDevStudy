// long mult2(long, long);

// void multstore(long x, long y, long* dest) {
//     long t = mult2(x, y);
//     *dest = t;
// }

// short test(short x, short y, short z) {
//     short val = z+y-x;
//     if (z <= 5) {
//         if (z >= 2) {
            
//         }else {
//             val = z / y;
//         }
//     } else if (3 <= y) {
//         val = x / y;
//         return val;
//     }
//     val = x / z;
      
//     return val;
// }


// long rfun(unsigned long x) {
    
//     if (x == 0) {
//         return ;
//     }
    
//     unsigned long nx = x >> 2;
//     long rv = rfun(nx);
//     rv += x;
//     return rv;
// }

#include <stdio.h>

// int main() {
//     long local;
//     printf("local at %p\n", &local);
//     return 0;
// }

// void echo()
// {
//     char buf[8]; /* Way too small! */
//     gets(buf);
//     puts(buf);
// }

float float_mov(float v1, float *src, float *dst) {
    float v2 = *src;
    *dst = v1;
    return v2;
}

int main() {}