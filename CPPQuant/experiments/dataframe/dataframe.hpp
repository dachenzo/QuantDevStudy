// dataframe.hpp
#ifndef DATAFRAME_HPP
#define DATAFRAME_HPP

#include <tuple>
#include <unordered_map>
#include <string>
#include <vector>
#include <span>               // C++20
#include <memory>

#include "column.hpp"
#include "csv_reader/csv.hpp"

// helper alias so that tupleofColumns<Ts...> IS a std::tuple< vector<Ts>... >
template<typename... Ts>
using tupleofColumns = std::tuple<std::vector<Ts>...>;

struct DataFrame {
    DataFrame() = default;

    // delete any direct, confusing template ctor
    template<typename... Ts>
    DataFrame(std::string, std::vector<std::string>) = delete;

    // the only way to load from CSV
    template<typename... Ts>
    static DataFrame fromCsv(const std::string& location,
                             const std::vector<std::string>& colNames)
    {
        DataFrame df;

        // build the empty tuple-of-vectors
        auto csvCols = tupleofColumns<Ts...>{};
        constexpr size_t N = sizeof...(Ts);

        // parseCSV is assumed to fill each vector inside csvCols
        ::parseCSV<Ts...>(csvCols, location, /*hasHeader=*/true);

        df.size_ = std::get<0>(csvCols).size();

        // move each vector into a Column<T> and stash it
        df.addColumnFromCsv<Ts...>(colNames, csvCols, std::make_index_sequence<N>{});

        return df;  // guaranteed elision in C++17+, or moved at worst
    }

    // your other APIs…
    template<typename K>
    std::span<const K> getColumn(const std::string& name) const {
        auto it = columns_.find(name);
        if (it == columns_.end())  
            throw std::runtime_error("no such column");

        BaseColumn* base = it->second.get();
        if (base->type() != typeid(K))
            throw std::runtime_error("wrong column type");

        return static_cast<Column<K>*>(base)->as_span();
    }

    void print() const {
        for (auto const& [nm, col] : columns_) {
            col->printColumn();
        }
    }

    size_t size() const { return size_; }

private:
    std::unordered_map<std::string, std::unique_ptr<BaseColumn>> columns_;
    size_t size_{0};

    // helper to wrap each vector<Ts> into a Column<Ts>
    template<typename... Ts, size_t... Is>
    void addColumnFromCsv(const std::vector<std::string>& names,
                          tupleofColumns<Ts...>& csvCols,
                          std::index_sequence<Is...>)
    {
        // the initializer_list trick just expands the pack in a fold-like way
        (void)std::initializer_list<int>{
            ( 
              [&] {
                  auto ptr = std::make_unique<Column<Ts>>(
                      names[Is],
                      std::get<Is>(csvCols)
                  );
                  columns_.emplace(names[Is], std::move(ptr));
              }(),
              0
            )...
        };
    }

    // assume you’ve got something like this in csv_reader/csv.hpp:

};

#endif // DATAFRAME_HPP
