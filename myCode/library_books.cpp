#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

int main() {
    // Open the CSV file
    std::ifstream inputFile("library_books.csv");

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Variables to store data
    std::vector<std::vector<std::string>> data;

    // Read each line from the file
    std::string line;
    while (std::getline(inputFile, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;

        // Split the line into cells using comma as the delimiter
        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        // Add the row to the data vector
        data.push_back(row);
    }

    // Close the file
    inputFile.close();

    // Print the data
    for (const auto& row : data) {
        for (const auto& cell : row) {
            std::cout << cell << "\t";
        }
        std::cout << std::endl;
    }

    return 0;
}
