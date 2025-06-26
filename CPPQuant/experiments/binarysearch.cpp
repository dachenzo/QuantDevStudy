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


template<BinarySearchable T,typename P, std::invocable<P, T>>
T& binarySearch(std::vector<T>& arr, P pred, T& target, T* result) {
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




template<std::size_t Index, typename T, std::size_t Length>
constexpr T& get(T (&arr)[Length])               // Index is part of the type
{
    static_assert(Index < Length and Index > -1, "Out-of-bounds access");
    
    return arr[Index];
}