#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>
#include <set>

class Member {
private:
    int memberID;
    std::string name;
    std::string email;
    std::set<int> borrowedBooks;

public:
    Member(int id, std::string n, std::string e);

    void displayMemberInfo() const;
    void borrowBook(int bookID);
    void returnBook(int bookID);

    int getMemberID() const;
    std::set<int> getBorrowedBooks() const;
};

#endif // MEMBER_H
