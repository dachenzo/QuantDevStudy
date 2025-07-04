#include "dataframe.hpp"





int main() {
    DataFrame df = DataFrame::fromCsv<int, std::string, int, double>(
    "example.csv",
    {"id", "name", "age", "salary"}
    );
    df.print();
}
