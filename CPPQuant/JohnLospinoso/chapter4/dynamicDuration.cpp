#include <cstdio>


int main() {
    int* intptr = new int{56};
    delete intptr;

    int* myarr = new int[10]{9, 0};
    delete[] myarr;
    printf("size:: %d", sizeof(myarr));

}