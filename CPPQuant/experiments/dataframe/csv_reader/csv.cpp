#include <cstddef>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <tuple>
#include <charconv>
#include <type_traits>
#include "csv.hpp"




std::size_t extractRowItem(std::string::iterator it, std::string::iterator end) {
    std::size_t cnt = 0;
    while (it != end && *it != ',') {it += 1; cnt+=1;}
    return cnt;
}




void splitLine(std::vector<std::string>& buff, std::string& line) {
    auto it = line.begin();
    auto end = line.end();

    while (it != end) {
        auto len = extractRowItem(it, end);
        buff.emplace_back(it, it+len);

        it += len;
        // if we're at a comma, skip it too
        if (it != end && *it == ',')
            ++it;

    }
    
}


std::size_t getColumnCount(std::string& line)  {
    size_t ans = 0;
    auto it = line.begin();
    auto end = line.end();

    while (it != end) {
        auto dist = extractRowItem(it, end);
        it += (dist);

        if (it != end && *it == ',')
            ++it;
        ans += 1;
    } 
    return ans;
}

