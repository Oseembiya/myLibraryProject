#include <iostream>
#include <vector>
#include <string>

// Forward declaration of Member class
class Member;

// Date class definition
class Date {
private:
    int day;
    int month;
    int year;

public:
    // Constructor
    Date(int day, int month, int year)
        : day(day), month(month), year(year) {}

    // Getter methods for day, month, and year
    int getDay() const {
        return day;
    }

    int getMonth() const {
        return month;
    }

    int getYear() const {
        return year;
    }
};

// Person class definition
class Person {
protected:
    std::string name;
    std::string address;
    std::string email;

public:
    // Constructors
    Person() {} // Default constructor

    Person(const std::string& name, const std::string& address, const std::string& email)
        : name(name), address(address), email(email) {}

    // Member functions
    std::string getName() const {
        return name;
    }

    void setName(const std::string& newName) {
        name = newName;
    }

    std::string getAddress() const {
        return address;
    }

    void setAddress(const std::string& newAddress) {
        address = newAddress;
    }

    std::string getEmail() const {
        return email;
    }

    void setEmail(const std::string& newEmail) {
        email = newEmail;
    }
};

// Member class definition
class Member : public Person {
private:
    int memberID;
    std::vector<Book> booksLoaned;

public:
    // Constructor
    Member(int memberID, const std::string& name, const std::string& address, const std::string& email)
        : memberID(memberID), Person(name, address, email) {}

    // Member functions
    int getMemberID() const {
        return memberID;
    }

    std::vector<Book> getBooksBorrowed() const {
        return booksLoaned;
    }

    void setBooksBorrowed(const Book& book) {
        booksLoaned.push_back(book);
    }
};

// Book class definition
class Book {
private:
    int bookID;
    std::string bookName;
    std::string authorFirstName;
    std::string authorLastName;
    std::string bookType;
    Date dueDate;
    // Assuming you have a Member class defined
    Member* borrower;

public:
    // Constructor
    Book(int id, const std::string& name, const std::string& firstName, const std::string& lastName)
        : bookID(id), bookName(name), authorFirstName(firstName), authorLastName(lastName) {
        // Initialization of other properties
    }

    // Member functions
    int getBookID() const {
        return bookID;
    }

    std::string getBookName() const {
        return bookName;
    }

    std::string getAuthorFirstName() const {
        return authorFirstName;
    }

    std::string getAuthorLastName() const {
        return authorLastName;
    }

    Date getDueDate() const {
        return dueDate;
    }

    void setDueDate(const Date& date) {
        dueDate = date;
    }

    void returnBook() {
        borrower = nullptr;
        // Additional logic for handling the returned book
    }

    void borrowBook(Member* borrower, const Date& dueDate) {
        this->borrower = borrower;
        setDueDate(dueDate);
        // Additional logic for handling the borrowed book
    }
};


// Librarian class definition
class Librarian : public Person {
private:
    int staffID;
    int salary;

public:
    // Constructor
    Librarian(int staffID, const std::string& name, const std::string& address, const std::string& email, int salary)
        : staffID(staffID), salary(salary), Person(name, address, email) {}

    // Member functions
    int getStaffID() const {
        return staffID;
    }

    void setStaffID(int newStaffID) {
        staffID = newStaffID;
    }

    int getSalary() const {
        return salary;
    }

    void setSalary(int newSalary) {
        salary = newSalary;
    }

    // Additional member functions specific to Librarian
    void addMember(Member& member) {
        // Implementation for adding a member
        // Display new member's details
        std::cout << "New member added: " << member.getName() << " - Member ID: " << member.getMemberID() << std::endl;
    }

    void issueBook(Member& member, Book& book) {
        // Implementation for issuing a book
        // Set due date (3 days from the date of issue)
        // Display issued book details
        std::cout << "Book issued to " << member.getName() << ": " << book.getBookName() << " - Due Date: " << " [calculate_due_date]" << std::endl;
    }

    void returnBook(Member& member, Book& book) {
        // Implementation for returning a book
        // Additional logic for handling the returned book
        book.returnBook();
        std::cout << "Book returned by " << member.getName() << ": " << book.getBookName() << std::endl;
    }

    void displayBorrowedBooks(const Member& member) {
        // Implementation for displaying borrowed books
        std::cout << "Books borrowed by " << member.getName() << ":" << std::endl;
        const std::vector<Book>& books = member.getBooksBorrowed();
        for (const Book& book : books) {
            std::cout << "- " << book.getBookName() << std::endl;
        }
    }

    void calculateFine(const Member& member) {
        // Implementation for calculating fine
        // Additional logic for calculating fine for overdue books
        const std::vector<Book>& books = member.getBooksBorrowed();
        for (const Book& book : books) {
            // Check if the book is overdue and calculate fine
            // Fine calculation logic here
            // std::cout << "Fine for " << member.getName() << ": £" << [calculated_fine] << std::endl;
        }
    }
};

// Main function
int main() {
    // You can test your classes here
    return 0;
}
