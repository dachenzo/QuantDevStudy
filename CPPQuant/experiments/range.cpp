#include <iostream>


struct range{
    struct it {
        int v;
        void operator++() {++v;}
        int operator*() const {return v;}
        bool operator!=(const it& o ) {return *o != v;}
    };
    int from, to;
    it begin() {return it{from};}
    it end() {return it{to};}
};


int main() {
    for (auto x: range{2, 8}) {
        std::cout << x << " ,";
    }
}
