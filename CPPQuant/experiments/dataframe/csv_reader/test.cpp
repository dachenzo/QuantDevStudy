#include "csv.hpp"
#include <string>
#include <iostream>


int main() {
    parseCSV<int, std::string, double>("test_csv.csv", false);

    std::string tst{"1,peeop,jamie"};
    std::cout << getColumnCount(tst);

}