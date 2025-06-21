#include <cstdio>

struct Human {
    const char* name;
    int age;
    //we use initialiser lists if we want to initialise const members from constructor arguments
    Human(const char* name, int age): name{name}, age{age} {

    }

    void introduce() {
        printf("My name is %s and I'm %d years old", name, age);
    }
};


int main() {
    Human mark{"Mark", 20};

    mark.introduce();
}