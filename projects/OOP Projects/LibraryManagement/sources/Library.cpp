#include "Library.h"
#include <iostream>

void Library::addBook(const Book& book) {
    books.push_back(book);
    std::cout << "Book added successfully." << std::endl;
}

void Library::removeBook(int bookID) {
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->getBookID() == bookID) {
            books.erase(it);
            std::cout << "Book removed successfully." << std::endl;
            return;
        }
    }
    std::cout << "Book not found." << std::endl;
}

void Library::addMember(const Member& member) {
    members.push_back(member);
    std::cout << "Member added successfully." << std::endl;
}

void Library::removeMember(int memberID) {
    for (auto it = members.begin(); it != members.end(); ++it) {
        if (it->getMemberID() == memberID) {
            members.erase(it);
            std::cout << "Member removed successfully." << std::endl;
            return;
        }
    }
    std::cout << "Member not found." << std::endl;
}

void Library::displayAllBooks() const {
    for (const auto& book : books) {
        book.displayBookInfo();
        std::cout << "-------------------" << std::endl;
    }
}

void Library::displayAllMembers() const {
    for (const auto& member : members) {
        member.displayMemberInfo();
        std::cout << "-------------------" << std::endl;
    }
}

void Library::borrowBook(int memberID, int bookID) {
    for (auto& book : books) {
        if (book.getBookID() == bookID && !book.getBorrowedStatus()) {
            for (auto& member : members) {
                if (member.getMemberID() == memberID) {
                    book.borrowBook();
                    member.borrowBook(bookID);
                    return;
                }
            }
            std::cout << "Member not found." << std::endl;
            return;
        }
    }
    std::cout << "Book not available for borrowing." << std::endl;
}

void Library::returnBook(int memberID, int bookID) {
    for (auto& book : books) {
        if (book.getBookID() == bookID && book.getBorrowedStatus()) {
            for (auto& member : members) {
                if (member.getMemberID() == memberID) {
                    book.returnBook();
                    member.returnBook(bookID);
                    return;
                }
            }
            std::cout << "Member not found." << std::endl;
            return;
        }
    }
    std::cout << "Book not borrowed." << std::endl;
}
