#include "Book.h"
#include <iostream>

Book::Book(int id, std::string t, std::string a, std::string p)
    : bookID(id), title(t), author(a), publisher(p), isBorrowed(false) {}

void Book::displayBookInfo() const{
    std::cout << "Book ID: " << bookID << "\nTitle: " << title 
              << "\nAuthor: " << author << "\nPublisher: " << publisher 
              << "\nBorrowed: " << (isBorrowed ? "Yes" : "No") << std::endl;
}

void Book::borrowBook() {
    if (!isBorrowed) {
        isBorrowed = true;
        std::cout << "Book borrowed successfully." << std::endl;
    } else {
        std::cout << "Book is already borrowed." << std::endl;
    }
}

void Book::returnBook() {
    if (isBorrowed) {
        isBorrowed = false;
        std::cout << "Book returned successfully." << std::endl;
    } else {
        std::cout << "Book was not borrowed." << std::endl;
    }
}

int Book::getBookID() const { return bookID; }

bool Book::getBorrowedStatus() const { return isBorrowed; }
