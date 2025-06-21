#include <cstdio>
#include <cstdlib>
#include <cstddef>

struct College {
    char name[256];
};

void printCollege(College* college) {
    printf("Our name is %s\n", college->name);
}

int main() {
    long num = 30;
    long *num_pointer = &num;
    printf("&num = %d\n", *(num_pointer+10));


    int nums[]{1, 2, 3};
    int* nums_ptr = nums;// points to 1
    


    printf("Size: %d\n", sizeof(nums));

    College best_colleges[] = { "Magdalen", "Nuffield", "Kellogg" };
    printCollege(best_colleges);
    std::byte* p;


    printf("Size of std::byte = %d\n", sizeof(std::byte));
    printf("Size of std::byte pointer = %d", sizeof(p));
}