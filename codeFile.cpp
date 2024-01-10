#include <iostream>
#include <vector>
#include <string>




class Date {
private:
    int day;
    int month;
    int year;

public:
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
};

class Member;

















class Book {
private:
    int bookID;
    std::string bookName;
    std::string authorFirstName;
    std::string authorLastName;
    std::string bookType;
    Date dueDate;
    Member* borrower;

public:
    Book(int id, const std::string& name, const std::string& firstName, const std::string& lastName, const Date& dueDate);

    Book(int id, const std::string& name, const std::string& firstName, const std::string& lastName)
        : bookID(id), bookName(name), authorFirstName(firstName), authorLastName(lastName), borrower(nullptr){}

    void setDueDate(const Date& date);
    void returnBook();
    void borrowBook(Member* borrower, const Date& dueDate);

    int getBookID() const {
        return bookID;
    }

    std::string getBookName() const {
        return bookName;
    }

    Date getDueDate() const {
        return dueDate;
    }
    // Inside the Book class
Book(int id, const std::string& name, const std::string& firstName, const std::string& lastName)
    : bookID(id), bookName(name), authorFirstName(firstName), authorLastName(lastName), borrower(nullptr) {}

// Inside the Librarian class
void displayBorrowedBooks(const Member& member);
void calculateFine(const Member& member);

// Implementation of Librarian member functions
void Librarian::displayBorrowedBooks(const Member& member) {
    std::cout << "Books borrowed by " << member.getName() << ":" << std::endl;
    const std::vector<Book>& books = member.getBooksBorrowed();
    for (const Book& book : books) {
        std::cout << "- " << book.getBookName() << std::endl;
    }
}

void Librarian::calculateFine(const Member& member) {
    const std::vector<Book>& books = member.getBooksBorrowed();

    // Assuming a fixed fine amount for each overdue book
    const double finePerDay = 2.50;  // Adjust this value as needed

    for (const Book& book : books) {
        // Check if the book is overdue and calculate fine
        Date currentDate(2024, 1, 10);  // Replace with the actual current date
        Date dueDate = book.getDueDate();

        if (currentDate.getYear() > dueDate.getYear() ||
            (currentDate.getYear() == dueDate.getYear() && currentDate.getMonth() > dueDate.getMonth()) ||
            (currentDate.getYear() == dueDate.getYear() && currentDate.getMonth() == dueDate.getMonth() && currentDate.getDay() > dueDate.getDay())) {
            // Calculate the number of days overdue
            int daysOverdue = currentDate.getDay() - dueDate.getDay();

            // Calculate the fine for the overdue book
            double calculatedFine = finePerDay * daysOverdue;

            // Display the fine information
            std::cout << "Fine for " << member.getName() << ": £" << calculatedFine << " for book '"
                      << book.getBookName() << "' (Days overdue: " << daysOverdue << ")" << std::endl;
        }
    }
}
};
























class Member : public Person {
private:
    int memberID;
    std::vector<Book> booksLoaned;

public:
    Member(int memberID, const std::string& name, const std::string& address, const std::string& email);

    int getMemberID() const {
        return memberID;
    }

    std::vector<Book>& getBooksBorrowed() {
        return booksLoaned;
    }

    const std::vector<Book>& getBooksBorrowed() const {
        return booksLoaned;
    }

    void setBooksBorrowed(const Book& book);
};
































class Librarian : public Person {
private:
    int staffID;
    int salary;

public:
    Librarian(int staffID, const std::string& name, const std::string& address, const std::string& email, int salary);

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


   /* void Librarian::displayBorrowedBooks(const Member& member) {
    std::cout << "Books borrowed by " << member.getName() << ":" << std::endl;
    const std::vector<Book>& books = member.getBooksBorrowed();
    for (const Book& book : books) {
        std::cout << "- " << book.getBookName() << std::endl;
    }
}*/
    void Librarian::calculateFine(const Member& member) {
    const std::vector<Book>& books = member.getBooksBorrowed();

    // Assuming a fixed fine amount for each overdue book
    const double finePerDay = 2.50;  // Adjust this value as needed

    for (const Book& book : books) {
        // Check if the book is overdue and calculate fine
        Date currentDate(2024, 1, 10);  // Replace with the actual current date
        Date dueDate = book.getDueDate();

        if (currentDate.getYear() > dueDate.getYear() ||
            (currentDate.getYear() == dueDate.getYear() && currentDate.getMonth() > dueDate.getMonth()) ||
            (currentDate.getYear() == dueDate.getYear() && currentDate.getMonth() == dueDate.getMonth() && currentDate.getDay() > dueDate.getDay())) {
            // Calculate the number of days overdue
            int daysOverdue = currentDate.getDay() - dueDate.getDay();

            // Calculate the fine for the overdue book
            double calculatedFine = finePerDay * daysOverdue;

            // Display the fine information
            std::cout << "Fine for " << member.getName() << ": £" << calculatedFine << " for book '"
                      << book.getBookName() << "' (Days overdue: " << daysOverdue << ")" << std::endl;
        }
    }
}
};


















// Implementation of Book member functions
Book::Book(int id, const std::string& name, const std::string& firstName, const std::string& lastName, const Date& dueDate)
    Book(int id, const std::string& name, const std::string& firstName, const std::string& lastName)
    : bookID(id), bookName(name), authorFirstName(firstName), authorLastName(lastName), borrower(nullptr) {}







void Book::setDueDate(const Date& date) {
    dueDate = date;
}






void Book::returnBook() {
    borrower = nullptr;
    // Additional logic for handling the returned book
}






void Book::borrowBook(Member* borrower, const Date& dueDate) {
    this->borrower = borrower;
    setDueDate(dueDate);
    // Additional logic for handling the borrowed book
}










// Implementation of Member member functions
Member::Member(int memberID, const std::string& name, const std::string& address, const std::string& email)
    : memberID(memberID), Person(name, address, email) {}










void Member::setBooksBorrowed(const Book& book) {
    booksLoaned.push_back(book);
}















// Implementation of Librarian member functions
Librarian::Librarian(int staffID, const std::string& name, const std::string& address, const std::string& email, int salary)
    : staffID(staffID), salary(salary), Person(name, address, email) {}










void Librarian::addMember(Member& member) {
    std::cout << "New member added: " << member.getName() << " - Member ID: " << member.getMemberID() << std::endl;
}















void Librarian::issueBook(Member& member, Book& book) {
    // Set due date (3 days from the date of issue)
    Date dueDate(2024, 1, 13);  // Adjust this based on the actual logic
    book.borrowBook(&member, dueDate);

    // Display issued book details
  std::cout << "Book issued to " << member.getName() << ": " << book.getBookName() << " - Due Date: "
              << book.getDueDate().getYear() << "-" << book.getDueDate().getMonth() << "-" << book.getDueDate().getDay() << std::endl;

}















void Librarian::returnBook(Member& member, Book& book) {
    book.returnBook();
    std::cout << "Book returned by " << member.getName() << ": " << book.getBookName() << std::endl;
}
















void Librarian::displayBorrowedBooks(const Member& member) {
    std::cout << "Books borrowed by " << member.getName() << ":" << std::endl;
    const std::vector<Book>& books = member.getBooksBorrowed();
    for (const Book& book : books) {
        std::cout << "- " << book.getBookName() << std::endl;
    }
}





















void Librarian::calculateFine(const Member& member) {
    const std::vector<Book>& books = member.getBooksBorrowed();

    // Assuming a fixed fine amount for each overdue book
    const double finePerDay = 2.50;  // Adjust this value as needed

    for (const Book& book : books) {
        // Check if the book is overdue and calculate fine
        Date currentDate(2024, 1, 10);  // Replace with the actual current date
        Date dueDate = book.getDueDate();

        if (currentDate.getYear() > dueDate.getYear() ||
            (currentDate.getYear() == dueDate.getYear() && currentDate.getMonth() > dueDate.getMonth()) ||
            (currentDate.getYear() == dueDate.getYear() && currentDate.getMonth() == dueDate.getMonth() && currentDate.getDay() > dueDate.getDay())) {
            // Calculate the number of days overdue
            int daysOverdue = currentDate.getDay() - dueDate.getDay();

            // Calculate the fine for the overdue book
            double calculatedFine = finePerDay * daysOverdue;

            // Display the fine information
            std::cout << "Fine for " << member.getName() << ": £" << calculatedFine << " for book '"
                      << book.getBookName() << "' (Days overdue: " << daysOverdue << ")" << std::endl;
        }
    }
}

































int main() {
    Member member1(1, "John Doe", "123 Main St", "john@example.com");
    Book book1(101, "The Great Gatsby", "F. Scott", "Fitzgerald");
    Librarian librarian(1001, "Alice Librarian", "456 Library Ave", "alice@example.com", 50000);

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
                int memberId;
                std::string name, address, email;
                std::cout << "Enter Member ID: ";
                std::cin >> memberId;
                std::cout << "Enter Name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter Address: ";
                std::getline(std::cin, address);
                std::cout << "Enter Email: ";
                std::cin >> email;

                Member newMember(memberId, name, address, email);
                librarian.addMember(newMember);
                break;
            }
            case 2: {
                librarian.issueBook(member1, book1);
                break;
            }
            case 3: {
                librarian.returnBook(member1, book1);
                break;
            }
            case 4: {
                librarian.displayBorrowedBooks(member1);
                break;
            }
            case 5: {
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
