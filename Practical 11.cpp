#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

struct Student {
    int id;
    std::string name;
    double marks;
};

// Part 1A: Write student records to students.csv (Format: ID,Name,Marks)
bool writeStudentsToCSV(const std::string& filename, const std::vector<Student>& students) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open " << filename << " for writing.\n";
        return false;
    }

    // Write CSV Header
    outFile << "ID,Name,Marks\n";
    for (const auto& s : students) {
        outFile << s.id << "," << s.name << "," << s.marks << "\n";
    }

    if (!outFile.good()) {
        std::cerr << "Error: Failed while writing to " << filename << ".\n";
        return false;
    }

    outFile.close();
    return true;
}

// Part 1B: Read and display student records from students.csv
void readStudentsFromCSV(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open " << filename << " for reading.\n";
        return;
    }

    std::string line;
    std::getline(inFile, line); // Skip header line

    std::cout << std::left << std::setw(8) << "ID"
              << std::setw(20) << "Name"
              << std::setw(10) << "Marks" << "\n";
    std::cout << "--------------------------------------\n";

    while (std::getline(inFile, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string idStr, name, marksStr;

        // Parse comma-separated values safely
        if (std::getline(ss, idStr, ',') &&
            std::getline(ss, name, ',') &&
            std::getline(ss, marksStr, ',')) {
            try {
                int id = std::stoi(idStr);
                double marks = std::stod(marksStr);
                std::cout << std::left << std::setw(8) << id
                          << std::setw(20) << name
                          << std::fixed << std::setprecision(2) << marks << "\n";
            } catch (...) {
                std::cerr << "[Warning] Skipped malformed numeric line: " << line << "\n";
            }
        } else {
            std::cerr << "[Warning] Skipped malformed CSV line: " << line << "\n";
        }
    }

    inFile.close();
}

// Part 2: Demonstrate tellp(), seekp(), tellg(), and seekg()
void demonstrateFilePositions() {
    const std::string demoFile = "position_demo.txt";

    // --- Output (Put) Pointer: tellp() and seekp() ---
    std::cout << "\n=== 2. Demonstrating tellp() and seekp() (Write Position) ===\n";
    std::fstream file(demoFile, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << demoFile << "\n";
        return;
    }

    file << "Hello_World_CPP";
    std::cout << "After writing 'Hello_World_CPP', tellp() = " << file.tellp() << "\n";

    // Move put pointer to index 6 ('W') and overwrite "World" with "CPlus"
    file.seekp(6, std::ios::beg);
    std::cout << "Moved write pointer with seekp(6). Current tellp() = " << file.tellp() << "\n";
    file << "CPlus";
    file.close();

    // --- Input (Get) Pointer: tellg() and seekg() ---
    std::cout << "\n=== 3. Demonstrating tellg() and seekg() (Read Position) ===\n";
    std::ifstream inFile(demoFile);
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open " << demoFile << " for reading.\n";
        return;
    }

    std::string fullContent;
    std::getline(inFile, fullContent);
    std::cout << "Updated file content : " << fullContent << "\n";

    // Reset stream state and inspect read position
    inFile.clear();
    inFile.seekg(0, std::ios::beg);
    std::cout << "At start of file, tellg() = " << inFile.tellg() << "\n";

    // Move get pointer to index 6 and read from there
    inFile.seekg(6, std::ios::beg);
    std::cout << "After seekg(6), tellg() = " << inFile.tellg() << "\n";

    std::string partialContent;
    std::getline(inFile, partialContent);
    std::cout << "Reading from position 6: " << partialContent << "\n";

    inFile.close();
}

int main() {
    const std::string csvFile = "students.csv";

    std::vector<Student> students = {
        {101, "Aarav Sharma", 88.5},
        {102, "Priya Deshmukh", 92.0},
        {103, "Rohan Patil", 79.25}
    };

    std::cout << "=== 1. Writing & Reading CSV Student Records ===\n";
    if (writeStudentsToCSV(csvFile, students)) {
        std::cout << "Successfully wrote " << students.size() << " records to " << csvFile << ".\n\n";
        readStudentsFromCSV(csvFile);
    }

    demonstrateFilePositions();

    return 0;
}