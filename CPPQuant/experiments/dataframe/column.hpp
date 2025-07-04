// base_column.hpp
#ifndef COLUMN_HPP
#define COLUMN_HPP

#include <typeinfo>
#include <string>
#include <vector>
#include <span>  
#include <iostream>

// The minimal abstract interface for any column:
struct BaseColumn {
    virtual ~BaseColumn() = default;

    // unambiguously const, returns a const type_info&
    virtual const std::type_info& type() const = 0;

    // print the column in whatever format you like
    virtual void printColumn() const = 0;
};





template<typename T>
struct Column : BaseColumn {
    // construct from a span of items
    Column(const std::string& name, std::span<const T> items)
      : data_(items.begin(), items.end()), name_(name)
    {}

    // construct a column all filled with `def`
    Column(const std::string& name, const T& def, size_t n)
      : data_(n, def), name_(name)
    {}

    // satisfy BaseColumn
    const std::type_info& type() const noexcept override {
        return typeid(T);
    }

    void printColumn() const override {
        // e.g. print the header, then every element...
        std::cout << name_ << ": ";
        for (auto const& x : data_) std::cout << x << " ";
        std::cout << "\n";
    }

    // let DataFrame pull out a span
    std::span<const T> as_span() const noexcept {
        return { data_.data(), data_.size() };
    }

private:
    std::vector<T> data_;
    std::string   name_;
};


#endif // COLUMN_HPP
