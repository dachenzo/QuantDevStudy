#include <stdexcept>
#include <cstdio>
#include <cstring>



struct SimpleString
{
    SimpleString(size_t maxSize): maxSize{maxSize}, size{0} {
        if (maxSize == 0) {
            throw std::runtime_error{"Max size must be atleast 1"};
        }
        buffer = new char[maxSize];

    }

    SimpleString(const SimpleString& other): maxSize{other.maxSize}, buffer{new char[maxSize]}, size{other.size} {
        std::strncpy(buffer, other.buffer, maxSize);
    }

    SimpleString& operator=(SimpleString& other) {

    }

    SimpleString(SimpleString&& other) noexcept: maxSize{other.maxSize}, buffer{other.buffer}, size{other.size}{
        other.size = 0;
        other.buffer = nullptr;
        other.maxSize = 0;
    }

    SimpleString& operator=(SimpleString&& other) noexcept {
        if (this == &other) return *this;
        delete[] buffer;
        buffer = other.buffer;
        size = other.size;
        maxSize = other.maxSize;
        other.buffer = nullptr;
        other.size = 0;
        other.maxSize = 0;
        return *this;    
    }

    

    bool appendLine(const char* x) {
        const auto x_len = strlen(x);
        if (x_len + size + 2 > maxSize) return false;
        std::strncpy(buffer+size, x, maxSize - size);
        size+= x_len;
        buffer[size++] = '\n';
        buffer[size] = 0;
        return true;

    }

 
    ~SimpleString() {
        delete[] buffer;
    }
    private:
    size_t maxSize;
    char* buffer;
    int size;
};
