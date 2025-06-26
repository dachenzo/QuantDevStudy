#ifndef COLUMN_HPP
#define COLUMN_HPP
#include <vector>
#include <string>
#include <span>


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

    std::span<T> as_span() {}
    private:
    std::vector<T> col;
    std::string name;
};

#endif