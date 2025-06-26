#include <vector>
#include <span>
#include <string>
#include "column.hpp"

struct BaseColumn {
    virtual void printColumn() = 0;
    virtual ~BaseColumn() = default;
};


template<typename T>
struct Column: BaseColumn {
    Column(std::string name, std::span<T> items): col{items.begin(), items.end()}, name{name} {}

    Column(std::string name, T def, size_t size): name{name}, col(def, size) {}

    ~Column() {
        delete col;
    }

    std::span<T> as_span() {
        return std::span{col};
    }


   
    private:
    std::vector<T> col;
    std::string name;
};