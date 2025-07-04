#include "csv.hpp"
#include <string>
#include <iostream>


int main() {
    tupleofColumns<int, std::string, double> cols;
    parseCSV<int, std::string, double>(cols, "test_csv.csv", false);

    std::string tst{"1,peeop,jamie"};
    std::cout << getColumnCount(tst);

}