#include <iostream>
#include "Library.h"

void displayMenu() {
    std::cout << "Library Management System\n";
    std::cout << "1. Add Book\n";
    std::cout << "2. Remove Book\n";
    std::cout << "3. Display All Books\n";
    std::cout << "4. Add Member\n";
    std::cout << "5. Remove Member\n";
    std::cout << "6. Display All Members\n";
    std::cout << "7. Borrow Book\n";
    std::cout << "8. Return Book\n";
    std::cout << "9. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;

        int id;
        std::string title, author, publisher, name, email;

        switch (choice) {
            case 1:
                std::cout << "Enter book ID: ";
                std::cin >> id;
                std::cout << "Enter title: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                std::cout << "Enter author: ";
                std::getline(std::cin, author);
                std::cout << "Enter publisher: ";
                std::getline(std::cin, publisher);
                library.addBook(Book(id, title, author, publisher));
                break;

            case 2:
                std::cout << "Enter book ID: ";
                std::cin >> id;
                library.removeBook(id);
                break;

            case 3:
                library.displayAllBooks();
                break;

            case 4:
                std::cout << "Enter member ID: ";
                std::cin >> id;
                std::cout << "Enter name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter email: ";
                std::getline(std::cin, email);
                library.addMember(Member(id, name, email));
                break;

            case 5:
                std::cout << "Enter member ID: ";
                std::cin >> id;
                library.removeMember(id);
                break;

            case 6:
                library.displayAllMembers();
                break;

            case 7:
                int memberID, bookID;
                std::cout << "Enter member ID: ";
                std::cin >> memberID;
                std::cout << "Enter book ID: ";
                std::cin >> bookID;
                library.borrowBook(memberID, bookID);
                break;

            case 8:
                std::cout << "Enter member ID: ";
                std::cin >> memberID;
                std::cout << "Enter book ID: ";
                std::cin >> bookID;
                library.returnBook(memberID, bookID);
                break;

            case 9:
                std::cout << "Exiting...\n";
                break;

            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 9);

    return 0;
}
