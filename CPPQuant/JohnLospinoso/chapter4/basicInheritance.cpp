struct Superclass {
    int x;
};


struct Subclass: Superclass {
    int y;
    int foo() {
        return x+y;
    }
};   
