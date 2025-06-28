#ifndef CSV_HPP
#define CSV_HPP
#include <cstddef>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <tuple>
#include <charconv>
#include <type_traits>



std::size_t extractRowItem(std::string::iterator it, std::string::iterator end);

void splitLine(std::vector<std::string>& buff, std::string& line);

std::size_t getColumnCount(std::string& line);

template<typename T>
void printColumn(std::vector<T>& vec) {
    for (T c: vec) {std::cout << c <<", ";}
    std::cout << '\n';

}



template<typename T>
T parseItem(std::string_view sv) {
    if constexpr(std::is_integral_v<T> && !std::is_same_v<T, bool>) {
        T x{};
        auto [p, ec] = std::from_chars(sv.data(), sv.data()+sv.size(), x);
        if (ec != std::errc()) throw std::runtime_error("Parse error");
        return x;
    }
    else if constexpr(std::is_floating_point_v<T>) {
        return std::stod(std::string(sv));
    } else if constexpr(std::is_same_v<T,std::string>) {
        return std::string(sv);
    } else {
        static_assert(!sizeof(T), "no parseValue for this type");
    }
}

template<typename... Ts, std::size_t... Is>
void pushRow(std::tuple<std::vector<Ts>...>& columns,
            const std::vector<std::string>& row,
            std::index_sequence<Is...>) {
    (void) std::initializer_list<int>{
        (std::get<Is>(columns).push_back(parseItem<Ts>(row[Is])), 0)...
    };
}

template<typename... Ts, std::size_t... Is>
void printCsv(std::tuple<std::vector<Ts>...>& columns,
                std::index_sequence<Is...>) {
    (void) std::initializer_list<int>{
        (printColumn<Ts>(std::get<Is>(columns)), 0)...
    };
}

template< typename ...Ts>
using tupleofColumns = std::tuple<std::vector<Ts>...>;
template< typename ...Ts>
void parseCSV(std::string path, bool headers) {
    std::ifstream file{path};
    if (!file.is_open()) {
        std::cerr << "Could not open file!\n";
        return;
    }
    std::size_t rowIdx = 0;
    if (headers) {
        std::string fstLine{};
        std::getline(file, fstLine);
        auto count = getColumnCount(fstLine);
        rowIdx += 1;
    }

    auto columns = tupleofColumns<Ts...>{};
    constexpr std::size_t colCount = std::tuple_size_v<decltype(columns)>;

    std::string line{};

    while (std::getline(file, line)) {
        rowIdx += 1;
        std::vector<std::string> row;
        splitLine(row, line);
        if (row.size() != colCount) {
            std::cerr << "Parse failed on row " << rowIdx << ", different count of csv columns and given columns";
        }

        pushRow(columns, row, std::make_index_sequence<colCount>{});


    }
    printCsv(columns, std::make_index_sequence<colCount>{});

}


#endif