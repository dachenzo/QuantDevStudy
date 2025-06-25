template <typename T>
struct  MyUniquePtr 
{
    // MyUniquePtr() = delete;
    MyUniquePtr(T* pointer): ptr{pointer} {}
    MyUniquePtr(MyUniquePtr& other) = delete;
    MyUniquePtr& operator= (const MyUniquePtr& other) = delete;
    MyUniquePtr(MyUniquePtr&& other)noexcept : ptr{other.ptr} {
        other.pointer = nullptr;
    }

    MyUniquePtr& operator=(MyUniquePtr&& other) noexcept {
        if (ptr) {delete ptr};
        ptr = other.ptr;
        other.ptr = nullptr;
        return *this;
    }
    ~MyUniquePtr() {
        if (ptr) {delete ptr;}
    }

    T* get() {
        return ptr
    }

    private:
    T* ptr;
};
