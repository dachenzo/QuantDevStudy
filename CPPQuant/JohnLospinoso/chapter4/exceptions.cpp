#include <stdexcept>
#include <cstdio>

struct Femi {
    Femi(int age) {
        this->age = age;
    }
    void verify(int x) {
        if (!(x == age)) {
            throw std::runtime_error{"Not Femi"};
        }
    }
    private: 
    int age;
};


int main() {
    Femi f{19};
    try {
        f.verify(18);
    } catch(const std::runtime_error& e) {
        printf("Exception caught with %s", e.what());
    }
}