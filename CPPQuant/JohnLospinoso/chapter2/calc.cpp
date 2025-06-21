enum class Operation {
    Add,
    Subtract,
    Multiply,
    Divide
};

struct Calculator {
    private:
    Operation op; // Using both private and public members means u might not have in linear order of the member declarations but the structs are still stoired contiguous in memory

    public:
    Calculator(Operation o) {
        op = o;
    }

    int calculate(int a, int b) {
        switch (op) {
            case Operation::Add: return a+b;
            case Operation::Subtract: return a-b;
            case Operation::Multiply: return a*b;
            case Operation::Divide: return a/b;
            default: return -1;
        }
    }

};