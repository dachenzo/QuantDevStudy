#include <unordered_map>
#include <array>
#include <string>
#include <vector>
#include <stdexcept>
#include <span>
#include <memory>
#include <typeinfo>
#include "column.hpp"
#include "filetype.hpp"

struct DataFrame {
    DataFrame() {}

    DataFrame(FileType type, std::string location) {

    }

    template<typename K>
    void addColumn(std::string name, std::span<K> in) {
        // Assumes the user inpust the correct size
        Column<K>* col = new Column<K>{name, in};
        columns.insert({name, std::unique_ptr{static_cast<BaseColumn*>(col)}});

    }

    template<typename K>
    void addColumn(std::string name, K def) {
        Column<K>* col = new Column<K>{name, def, size};
        columns.insert({name, std::unique_ptr{static_cast<BaseColumn*>(col)}});
    }

    template<typename K>
    std::span<K> getColumn(std::string name) {
        auto it = columns.find(name);
        if (it == columns.end()) {throw std::runtime_error{"accessed non existent column"}};

        BaseColumn* base = it->second.get();
        if (base->type() != typeid(K)) {throw std::runtime_error{"Bad columnn type"}};

        return static_cast<Column<K>*>(base)->as_span();
    }
    
    private:
    std::unordered_map<std::string, std::unique_ptr<BaseColumn*>> columns;
    size_t size;
    
};