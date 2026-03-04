#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include "Book.h"
#include "Member.h"

class Library {
private:
    std::vector<Book> books;
    std::vector<Member> members;

public:
    void addBook(const Book& book);
    void removeBook(int bookID);

    void addMember(const Member& member);
    void removeMember(int memberID);

    void displayAllBooks() const;
    void displayAllMembers() const;

    void borrowBook(int memberID, int bookID);
    void returnBook(int memberID, int bookID);
};

#endif // LIBRARY_H
