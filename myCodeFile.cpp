#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

// this is a date class
class Date {
private:
    int day;
    int month;
    int year;

public:
    Date() : day(0), month(0), year(0) {}  
    Date(int day, int month, int year)
        : day(day), month(month), year(year) {}

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

// this is a person class
class Person {
protected:
    std::string name;
    std::string address;
    std::string email;

public:
    Person(const std::string& name, const std::string& address, const std::string& email)
        : name(name), address(address), email(email) {}

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

    virtual void displayDetails() const {
        std::cout << "Name: " << name << "\nAddress: " << address << "\nEmail: " << email << std::endl;
    }
};
// this is a class 
class Book {
private:
    int bookID;
    std::string bookName;
    Date dueDate;  //i Added for due date handling
    bool borrowed;
    int borrowerID;

public:
    Book(int id, const std::string& name)
        : bookID(id), bookName(name), borrowed(false), borrowerID(-1), dueDate() {}

    int getBookID() const {
        return bookID;
    }

    std::string getBookName() const {
        return bookName;
    }

    bool isBorrowed() const {
        return borrowed;
    }

    int getBorrowerID() const {
        return borrowerID;
    }

    Date getDueDate() const {  // Getter for dueDate
        return dueDate;
    }

    void displayDetails() const {
        std::cout << "Book ID: " << bookID << "\nBook Name: " << bookName;
        if (borrowed) {
            std::cout << "\nBorrowed by Member ID: " << borrowerID << "\nDue Date: " << dueDate.getDay() << "/" << dueDate.getMonth() << "/" << dueDate.getYear();
        }
        std::cout << std::endl;
    }

    bool operator==(const Book& other) const {
        return bookID == other.bookID;
    }

    void borrowBook(int memberID, const Date& dueDate);
    void returnBook();
};

void Book::borrowBook(int memberID, const Date& dueDate) {
    borrowed = true;
    borrowerID = memberID;
    this->dueDate = dueDate;
}

void Book::returnBook() {
    borrowed = false;
    borrowerID = -1;
    // Additional logic for handling the returned book
}

class Member : public Person {
private:
    int memberID;
    std::vector<Book> booksLoaned;

public:
    Member(int memberID, const std::string& name, const std::string& address, const std::string& email)
        : memberID(memberID), Person(name, address, email) {}

    int getMemberID() const {
        return memberID;
    }

    const std::vector<Book>& getBooksBorrowed() const {
        return booksLoaned;
    }

    void setBooksBorrowed(const Book& book);
    void returnBook(const Book& book);
    void displayBorrowedBooks() const;

    void displayDetails() const override {
        Person::displayDetails();
        std::cout << "Member ID: " << memberID << std::endl;
    }
};

void Member::setBooksBorrowed(const Book& book) {
    booksLoaned.push_back(book);
}

void Member::returnBook(const Book& book) {
    auto it = std::find(booksLoaned.begin(), booksLoaned.end(), book);
    if (it != booksLoaned.end()) {
        it->returnBook();
        booksLoaned.erase(it);
    }
}

void Member::displayBorrowedBooks() const {
    std::cout << "Books borrowed by " << getName() << ":" << std::endl;
    for (const Book& book : booksLoaned) {
        book.displayDetails();
    }
}

class Librarian : public Person {
private:
    int staffID;
    int salary;

public:
    Librarian(int staffID, const std::string& name, const std::string& address, const std::string& email, int salary)
        : staffID(staffID), salary(salary), Person(name, address, email) {}

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

    void addMember(Member& member);
    void issueBook(Member& member, Book& book);
    void returnBook(Member& member, Book& book);
    void displayBorrowedBooks(const Member& member);
    void calculateFine(const Member& member);
};

void Librarian::addMember(Member& member) {
    std::cout << "New member added: " << member.getName() << " - Member ID: " << member.getMemberID() << std::endl;
}

void Librarian::issueBook(Member& member, Book& book) {
    time_t t = time(0);
    struct tm* now = localtime(&t);
    Date dueDate(now->tm_mday + 3, now->tm_mon + 1, now->tm_year + 1900);  // 3 days from now

    book.borrowBook(member.getMemberID(), dueDate);
    member.setBooksBorrowed(book);

    std::cout << "Book issued to " << member.getName() << ": " << book.getBookName() << " - Due Date: "
              << dueDate.getDay() << "/" << dueDate.getMonth() << "/" << dueDate.getYear() << std::endl;
}

void Librarian::returnBook(Member& member, Book& book) {
    book.returnBook();
    member.returnBook(book);
    std::cout << "Book returned by " << member.getName() << ": " << book.getBookName() << std::endl;
}

void Librarian::displayBorrowedBooks(const Member& member) {
    member.displayBorrowedBooks();
}

void Librarian::calculateFine(const Member& member) {
    const std::vector<Book>& books = member.getBooksBorrowed();
    const double finePerDay = 1.0;

    for (const Book& book : books) {
        if (book.isBorrowed()) {
            time_t t = time(0);
            struct tm* now = localtime(&t);
            Date currentDate(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);

            Date dueDate = book.getDueDate();

            if (currentDate.getYear() > dueDate.getYear() ||
                (currentDate.getYear() == dueDate.getYear() && currentDate.getMonth() > dueDate.getMonth()) ||
                (currentDate.getYear() == dueDate.getYear() && currentDate.getMonth() == dueDate.getMonth() && currentDate.getDay() > dueDate.getDay())) {
                int daysOverdue = currentDate.getDay() - dueDate.getDay();
                double calculatedFine = finePerDay * daysOverdue;

                std::cout << "Fine for " << member.getName() << ": £" << calculatedFine << " for book '"
                          << book.getBookName() << "' (Days overdue: " << daysOverdue << ")" << std::endl;
            }
        }
    }
}


// this is the main code
int main() { 
    std::string librarianName, librarianAddress, librarianEmail;
    int librarianID, librarianSalary;

    std::cout << "Enter Librarian Name: ";
    std::getline(std::cin, librarianName);

    std::cout << "Enter Librarian Address: ";
    std::getline(std::cin, librarianAddress);

    std::cout << "Enter Librarian Email: ";
    std::getline(std::cin, librarianEmail);

    std::cout << "Enter Librarian ID: ";
    std::cin >> librarianID;

    std::cout << "Enter Librarian Salary: ";
    std::cin >> librarianSalary;

    Librarian librarian(librarianID, librarianName, librarianAddress, librarianEmail, librarianSalary);

    int choice;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Member\n";
        std::cout << "2. Issue Book\n";
        std::cout << "3. Return Book\n";
        std::cout << "4. Display Borrowed Books\n";
        std::cout << "5. Calculate Fine\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string memberName, memberAddress, memberEmail;
                int memberID;

                std::cout << "Enter Member Name: ";
                std::cin.ignore(); 
                std::getline(std::cin, memberName);

                std::cout << "Enter Member Address: ";
                std::getline(std::cin, memberAddress);

                std::cout << "Enter Member Email: ";
                std::getline(std::cin, memberEmail);

                std::cout << "Enter Member ID: ";
                std::cin >> memberID;

                Member newMember(memberID, memberName, memberAddress, memberEmail);
                librarian.addMember(newMember);
                break;
            }
            case 2: {
                int memberID, bookID;

                std::cout << "Enter Member ID: ";
                std::cin >> memberID;

                std::cout << "Enter Book ID: ";
                std::cin >> bookID;

                Book book1(bookID, "Sample Book");
                Member member1(memberID, "John Doe", "123 Main St", "john@example.com");

                librarian.issueBook(member1, book1);
                break;
            }
            case 3: {
                int memberID, bookID;

                std::cout << "Enter Member ID: ";
                std::cin >> memberID;

                std::cout << "Enter Book ID: ";
                std::cin >> bookID;

                Book book1(bookID, "Sample Book");
                Member member1(memberID, "John Doe", "123 Main St", "john@example.com");

                librarian.returnBook(member1, book1);
                break;
            }
            case 4: {
                int memberID;

                std::cout << "Enter Member ID: ";
                std::cin >> memberID;

                Member member1(memberID, "John Doe", "123 Main St", "john@example.com");

                librarian.displayBorrowedBooks(member1);
                break;
            }
            case 5: {
                int memberID;

                std::cout << "Enter Member ID: ";
                std::cin >> memberID;

                
                Member member1(memberID, "John Doe", "123 Main St", "john@example.com");

                librarian.calculateFine(member1);
                break;
            }
            case 0:
                std::cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0; 
}
