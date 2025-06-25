#include <type_traits>
#include <vector>
#include <concepts>

template<typename T>
concept BinarySearchable =  
    std::is_default_constructible_v<T> && 
    requires (T a, T b) {
        {a < b} -> std::convertible_to<bool>;
        {a > b} -> std::convertible_to<bool>;
        {a == b} -> std::convertible_to<bool>;
    };


template<BinarySearchable T, typename P>
requires std::invocable<P, T>
T& binarySearch(std::vector<T>& arr, P pred) {
    size_t left = 0;
    size_t right = arr.size();
    
    while (left <= right) {
        size_t mid = (left+right) / 2;
        if pred(mid) {
            left = mid+1
        } else {
            right = mid-1
        }

    }
    return ansarr[left];
}



int main() {}