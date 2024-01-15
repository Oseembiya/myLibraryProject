#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "myCode\execute_myCodeFile.exe"
#include "myCode\library_books.exe"


TEST_CASE("Book class test") {
    SECTION("Book initialization and borrowing") {
        // Add test cases for Book initialization and borrowing functionality
        Book book(1, "Test Book");
        REQUIRE(book.getBookID() == 1);
        REQUIRE(book.getBookName() == "Test Book");
        REQUIRE_FALSE(book.isBorrowed());

        Date dueDate(15, 1, 2024);
        book.borrowBook(101, dueDate);
        REQUIRE(book.isBorrowed());
        REQUIRE(book.getBorrowerID() == 101);
        REQUIRE(book.getDueDate() == dueDate);
    }

    SECTION("Book return") {
        // Add test cases for Book return functionality
        Book book(2, "Another Book");
        Date dueDate(10, 1, 2024);

        book.borrowBook(102, dueDate);
        REQUIRE(book.isBorrowed());

        book.returnBook();
        REQUIRE_FALSE(book.isBorrowed());
        REQUIRE(book.getBorrowerID() == -1);
        // Additional checks if needed
    }
}

TEST_CASE("Person Class Test") {
    SECTION("Default Constructor and Getter Methods") {
        Person person("John Doe", "123 Main St", "john@example.com");

        REQUIRE(person.getName() == "John Doe");
        REQUIRE(person.getAddress() == "123 Main St");
        REQUIRE(person.getEmail() == "john@example.com");
    }

    SECTION("Setter Methods") {
        Person person("John Doe", "123 Main St", "john@example.com");

        person.setName("Jane Doe");
        REQUIRE(person.getName() == "Jane Doe");

        person.setAddress("456 Oak St");
        REQUIRE(person.getAddress() == "456 Oak St");

        person.setEmail("jane@example.com");
        REQUIRE(person.getEmail() == "jane@example.com");
    }

    SECTION("Display Details Method") {
        Person person("John Doe", "123 Main St", "john@example.com");

        // Redirect cout to a stringstream to capture the output
        std::stringstream ss;
        std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());

        person.displayDetails();

        // Restore cout
        std::cout.rdbuf(old_cout);

        // Checking if the output matches the expected output
        REQUIRE(ss.str() == "Name: John Doe\nAddress: 123 Main St\nEmail: john@example.com\n");
    }
}

TEST_CASE("Book Class Test") {
    SECTION("Default Constructor and Getter Methods") {
        Book book(1, "Sample Book");

        REQUIRE(book.getBookID() == 1);
        REQUIRE(book.getBookName() == "Sample Book");
        REQUIRE(book.isBorrowed() == false);
        REQUIRE(book.getBorrowerID() == -1);

        Date defaultDueDate;  // Default-constructed Date object
        REQUIRE(book.getDueDate() == defaultDueDate);
    }

    SECTION("Operator== Method") {
        Book book1(1, "Sample Book");
        Book book2(1, "Another Book");
        Book book3(2, "Sample Book");

        REQUIRE(book1 == book2);
        REQUIRE(!(book1 == book3));
    }

    SECTION("Borrow and Return Book Methods") {
        Book book(1, "Sample Book");
        Date dueDate(2024, 1, 15);

        REQUIRE(book.isBorrowed() == false);
        REQUIRE(book.getBorrowerID() == -1);

        book.borrowBook(123, dueDate);

        REQUIRE(book.isBorrowed() == true);
        REQUIRE(book.getBorrowerID() == 123);
        REQUIRE(book.getDueDate() == dueDate);

        book.returnBook();

        REQUIRE(book.isBorrowed() == false);
        REQUIRE(book.getBorrowerID() == -1);
    }

    SECTION("Display Details Method") {
        Book book(1, "Sample Book");
        Date dueDate(2024, 1, 15);

        book.borrowBook(123, dueDate);

        // Redirect cout to a stringstream to capture the output
        std::stringstream ss;
        std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());

        book.displayDetails();

        // Restore cout
        std::cout.rdbuf(old_cout);

        // Check if the output matches the expected output
        REQUIRE(ss.str() == "Book ID: 1\nBook Name: Sample Book\nBorrowed by Member ID: 123\nDue Date: 15/1/2024\n");
    }
}

TEST_CASE("Member class test") {
    SECTION("Member initialization and borrowing books") {
        // Add test cases for Member initialization and borrowing books functionality
        Member member(201, "John Doe", "456 Oak St", "john@example.com");
        REQUIRE(member.getMemberID() == 201);
        REQUIRE(member.getName() == "John Doe");

        Book book(3, "Library Book");
        member.setBooksBorrowed(book);
        const std::vector<Book>& booksBorrowed = member.getBooksBorrowed();
        REQUIRE(booksBorrowed.size() == 1);
        REQUIRE(booksBorrowed[0] == book);
    }

    SECTION("Member returning books") {
        // Add test cases for Member returning books functionality
        Member member(202, "Jane Doe", "789 Pine St", "jane@example.com");

        Book book1(4, "Book One");
        Book book2(5, "Book Two");

        member.setBooksBorrowed(book1);
        member.setBooksBorrowed(book2);
        const std::vector<Book>& booksBorrowed = member.getBooksBorrowed();
        REQUIRE(booksBorrowed.size() == 2);

        member.returnBook(book1);
        REQUIRE(booksBorrowed.size() == 1);
        REQUIRE(booksBorrowed[0] == book2);
    }
}

