#include<iostream>
#include<string>
#include<vector> 

using namespace std;


class Book
{
	private:
		string title;
		string author;
		bool available;
	
	public:
		Book(string title_p, string author_p) : title(title_p), author(author_p) {}
		string getTitle() const {
			return title;
		}
		string getAuthor() const {
			return author;
		}	
		bool isAvailable() const {
			return available;
		}
		void setAvailable(bool availability)
		{
			available = availability;
		}
		void getDetails() const {
			cout << "Title : " << title 
			     << " Author : " << author 
			     << " Available: "<< available << endl;
		}
		void setTitle(const string& t) {title = t;}
	       	void setAuthor(const string& a) {author = a;}	

};








class Person
{
	protected:
		string name;
		int id;
	public:
		Person(string name_p, int id_p) : name(name_p), id(id_p) {}

		// Getters 
		string getName() const {
			return name;
		}
		int getId() const {
			return id;
		}
		// Setters
		void setName(const string& n) {
			name = n;
		}
		void setId(const int& id_p) {
			id = id_p;
		}
		
};


class Admin : public Person
{
	public:
		Admin(string name, int id) : Person(name, id) {}

		void manageBooks() {
			cout << "Managing books ..." << endl;
		}
		
		void manageMembers() {
			cout << "Managing Members ..." << endl;
		}

};

class Member : public Person 
{
	public:
		Member(string name, int id) : Person(name, id) {}

		void borrowBook(Book &book)
		{
			if(book.isAvailable())
			{
				cout << name << " borrowed the book : " 
				     << book.getTitle() << endl;
				book.setAvailable(false);
			}
			else{
				cout << "Book is currently unavailable!" << endl;
			}
		}
		
		void returnBook(Book &book)
		{
			cout << name << " returned the book: " << book.getTitle() << endl;
			book.setAvailable(true);
		}

};


class Library
{
private:
	vector<Book> books;
	vector<Member> members;

public:
	void addBook(const Book& book)
	{
		books.push_back(book);
		cout << "Book added to library: " << book.getTitle() << endl;
	}

	void removeBook(const string& title)
	{
		for(auto it = books.begin(); it != books.end(); ++it)
		{
			if(it->getTitle() == title)
			{
				books.erase(it);
				cout << "Book removed from the library: " << title << endl;
				return;
			}
		}
		cout << "Book not found!" << endl;
	}
	
	void addMember(const Member& member)
	{
		members.push_back(member);
		cout << "Member added: " << member.getName() << endl;
	}

	void issueBook(const string& title, Member& member)
	{
		for(auto &book : books)
		{
			if(book.getTitle() == title && book.isAvailable())
			{
				member.borrowBook(book);
				return;
			}
		}
		cout << "Book not available or not found" << endl;
	}

	void returnBook(const string& title, Member& member)
	{
		for(auto &book : books)
		{
			if(book.getTitle() == title)
			{
				member.returnBook(book);
				return;
			}
		}
		cout << "Book not found in the library" << endl;
	}

	void displayBooks() const {
		cout << "Books in the library: " << endl;
		for(const auto& book : books)
		{
			book.getDetails();
		}
		
	}
};



int main()
{
	Library library;

	Book book1("Moqadimat Ibn Khaldoun", "Ibn Khaldoon");
	Book book2("C++ programming language", "bjarne stroustrup");

	Admin admin("Mohamed", 101);
	Member member("Ahmed", 102);

	library.addBook(book1);
	library.addBook(book2);

	library.displayBooks();

	library.addMember(member);
	library.issueBook("C++ programming language", member);
	library.issueBook("C++ programming language", member);	
	library.returnBook("C++ programming language", member);

	return 0;
}
