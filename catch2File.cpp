#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "myCodeFile.cpp"

// Include your header file(s) here

TEST_CASE("Book class test") {
    SECTION("Book initialization and borrowing") {
        // Add test cases for Book initialization and borrowing functionality
        Book book(1, "Test Book");
        REQUIRE(book.getBookID() == 1);
        REQUIRE(book.getBookName() == "Test Book");
        REQUIRE_FALSE(book.isBorrowed());

        Date dueDate(2024, 1, 15);
        book.borrowBook(101, dueDate);
        REQUIRE(book.isBorrowed());
        REQUIRE(book.getBorrowerID() == 101);
        REQUIRE(book.getDueDate() == dueDate);
    }

    SECTION("Book return") {
        // Add test cases for Book return functionality
        Book book(2, "Another Book");
        Date dueDate(2024, 1, 10);

        book.borrowBook(102, dueDate);
        REQUIRE(book.isBorrowed());

        book.returnBook();
        REQUIRE_FALSE(book.isBorrowed());
        REQUIRE(book.getBorrowerID() == -1);
        // Additional checks if needed
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
        // Additional checks if needed
    }
}

// Add more test cases for other classes if necessary

// Optionally, add more test cases to cover the Librarian class and its methods

TEST_CASE("Librarian class test") {
    // Add test cases for the Librarian class and its methods
    // You may want to mock or stub external dependencies if necessary
    // Additional checks and verifications can be added
}
