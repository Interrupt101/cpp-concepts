#include "Member.h"
#include <iostream>
#include <algorithm>

Member::Member(int id, std::string n, std::string e)
    : memberID(id), name(n), email(e) {}

void Member::displayMemberInfo() const {
    std::cout << "Member ID: " << memberID << "\nName: " << name 
              << "\nEmail: " << email << std::endl;
}

void Member::borrowBook(int bookID) {
    borrowedBooks.insert(bookID);
    std::cout << "Book borrowed successfully." << std::endl;
}

void Member::returnBook(int bookID) {
    auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), bookID);
    if (it != borrowedBooks.end()) {
        borrowedBooks.erase(it);
        std::cout << "Book returned successfully." << std::endl;
    } else {
        std::cout << "Book not found in borrowed list." << std::endl;
    }
}

int Member::getMemberID() const { return memberID; }

std::set<int> Member::getBorrowedBooks() const { return borrowedBooks; }
