#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
    int bookID;
    std::string title;
    std::string author;
    std::string publisher;
    bool isBorrowed;

public:
    Book(int id, std::string t, std::string a, std::string p);

    void displayBookInfo() const;
    void borrowBook();
    void returnBook();

    int getBookID() const;
    bool getBorrowedStatus() const;
};

#endif // BOOK_H
