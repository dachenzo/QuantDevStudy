#include <cstdint>

struct PodStruct {
    uint64_t a;
    char b[256];
    bool c;
};



struct JohnVanAlek {
    bool gold = true;
    int birthYear{2006};
    char location[8] = {"London"};
};


int main() {
    PodStruct pod1{}; // all fields are zero
    PodStruct pod2 = {}; //all fields zerod

    PodStruct pod3{42, "Hello"};// all fileds initialised except c, c is set to 0
    PodStruct pod4{42, "Hello", false};

    int arr1[]{1, 2, 3}; // size 3, 1, 2, 3
    int arr2[5]{}; // size 5, 0, 0, 0, 0, 0
    int array_3[5]{ 1, 2, 3 };  // Array of length 5; 1, 2, 3, 0, 0
    int array_4[5];// Array of length 5; uninitialized values


}