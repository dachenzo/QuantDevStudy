#include <vector>

struct Book {
    char name[256];
    int year;
    int pages;
    bool hardcover;
};

struct Library {
    Library() {
    }

    Library(Book b) {
        books.push_back(b);
    }

    void addBook(Book b) {
        books.push_back(b);
    }

    std::vector<Book> getBooks() {
        return books;
    }


    private:
    std::vector<Book> books;
    int bookCount;
};



int main() {
    Book cppCrashCourse;
    cppCrashCourse.pages = 500;
   

}