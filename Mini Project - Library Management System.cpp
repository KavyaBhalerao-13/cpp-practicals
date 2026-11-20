#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <limits>

// --- Custom Exception Hierarchy ---
class LibraryException : public std::runtime_error {
public:
    explicit LibraryException(const std::string& msg) : std::runtime_error(msg) {}
};

class BookNotFoundException : public LibraryException {
public:
    explicit BookNotFoundException(int id)
        : LibraryException("Book with ID " + std::to_string(id) + " was not found.") {}
};

class BookUnavailableException : public LibraryException {
public:
    explicit BookUnavailableException(const std::string& msg) : LibraryException(msg) {}
};

// --- Base Class (Encapsulation + Polymorphism) ---
class LibraryItem {
protected:
    int id;
    std::string title;

public:
    LibraryItem(int itemId, const std::string& itemTitle)
        : id(itemId), title(itemTitle) {}

    virtual ~LibraryItem() = default;

    int getId() const { return id; }
    std::string getTitle() const { return title; }

    virtual void display() const = 0; // Pure virtual function
};

// --- Derived Class: Book ---
class Book : public LibraryItem {
private:
    std::string author;
    bool available;

public:
    Book(int bookId, const std::string& bookTitle, const std::string& bookAuthor, bool isAvail = true)
        : LibraryItem(bookId, bookTitle), author(bookAuthor), available(isAvail) {}

    std::string getAuthor() const { return author; }
    bool isAvailable() const { return available; }

    void issueBook() {
        if (!available) {
            throw BookUnavailableException("Book '" + title + "' is already issued.");
        }
        available = false;
    }

    void returnBook() {
        if (available) {
            throw BookUnavailableException("Book '" + title + "' is already in the library.");
        }
        available = true;
    }

    void display() const override {
        std::cout << std::left << std::setw(8) << id
                  << std::setw(26) << title
                  << std::setw(20) << author
                  << (available ? "Available" : "Issued") << "\n";
    }

    std::string toCSV() const {
        return std::to_string(id) + "," + title + "," + author + "," + (available ? "1" : "0");
    }
};

// --- Library Manager (STL + File I/O) ---
class Library {
private:
    std::vector<Book> books;
    std::string filename;

    Book& findBookById(int id) {
        for (auto& b : books) {
            if (b.getId() == id) {
                return b;
            }
        }
        throw BookNotFoundException(id);
    }

public:
    explicit Library(const std::string& csvFile) : filename(csvFile) {
        loadFromFile();
    }

    void loadFromFile() {
        std::ifstream inFile(filename);
        if (!inFile.is_open()) {
            // Seed with sample data if file does not exist yet
            books.emplace_back(101, "Clean Code", "Robert C. Martin", true);
            books.emplace_back(102, "Effective C++", "Scott Meyers", true);
            books.emplace_back(103, "Design Patterns", "Erich Gamma", false);
            saveToFile();
            return;
        }

        books.clear();
        std::string line;
        std::getline(inFile, line); // Skip header

        while (std::getline(inFile, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string idStr, title, author, availStr;

            if (std::getline(ss, idStr, ',') &&
                std::getline(ss, title, ',') &&
                std::getline(ss, author, ',') &&
                std::getline(ss, availStr, ',')) {
                try {
                    books.emplace_back(std::stoi(idStr), title, author, availStr == "1");
                } catch (...) {
                    // Skip malformed lines safely
                }
            }
        }
        inFile.close();
    }

    void saveToFile() const {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            throw LibraryException("Failed to open " + filename + " for saving.");
        }
        outFile << "ID,Title,Author,Available\n";
        for (const auto& b : books) {
            outFile << b.toCSV() << "\n";
        }
        outFile.close();
    }

    void addBook(int id, const std::string& title, const std::string& author) {
        for (const auto& b : books) {
            if (b.getId() == id) {
                throw LibraryException("A book with ID " + std::to_string(id) + " already exists.");
            }
        }
        books.emplace_back(id, title, author, true);
        saveToFile();
        std::cout << "[Success] Book added and saved to " << filename << ".\n";
    }

    void listBooks() const {
        if (books.empty()) {
            std::cout << "No books in the library.\n";
            return;
        }
        std::cout << "\n" << std::left << std::setw(8) << "ID"
                  << std::setw(26) << "Title"
                  << std::setw(20) << "Author"
                  << "Status\n";
        std::cout << "----------------------------------------------------------------\n";
        for (const auto& b : books) {
            b.display();
        }
    }

    void searchBook(int id) {
        const Book& b = findBookById(id);
        std::cout << "\nBook Found:\n";
        b.display();
    }

    void issueBook(int id) {
        Book& b = findBookById(id);
        b.issueBook();
        saveToFile();
        std::cout << "[Success] Book ID " << id << " issued.\n";
    }

    void returnBook(int id) {
        Book& b = findBookById(id);
        b.returnBook();
        saveToFile();
        std::cout << "[Success] Book ID " << id << " returned.\n";
    }
};

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Library lib("library_books.csv");
    int choice = 0;

    while (true) {
        std::cout << "\n====== LIBRARY MANAGEMENT SYSTEM ======\n";
        std::cout << "1. List All Books\n";
        std::cout << "2. Add New Book\n";
        std::cout << "3. Search Book by ID\n";
        std::cout << "4. Issue Book\n";
        std::cout << "5. Return Book\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cout << "[Error] Please enter a valid number.\n";
            clearInput();
            continue;
        }

        try {
            if (choice == 1) {
                lib.listBooks();
            } else if (choice == 2) {
                int id;
                std::string title, author;
                std::cout << "Enter Book ID: ";
                if (!(std::cin >> id)) { clearInput(); throw LibraryException("Invalid ID."); }
                clearInput();
                std::cout << "Enter Title  : ";
                std::getline(std::cin, title);
                std::cout << "Enter Author : ";
                std::getline(std::cin, author);
                lib.addBook(id, title, author);
            } else if (choice == 3) {
                int id;
                std::cout << "Enter Book ID to search: ";
                if (!(std::cin >> id)) { clearInput(); throw LibraryException("Invalid ID."); }
                lib.searchBook(id);
            } else if (choice == 4) {
                int id;
                std::cout << "Enter Book ID to issue: ";
                if (!(std::cin >> id)) { clearInput(); throw LibraryException("Invalid ID."); }
                lib.issueBook(id);
            } else if (choice == 5) {
                int id;
                std::cout << "Enter Book ID to return: ";
                if (!(std::cin >> id)) { clearInput(); throw LibraryException("Invalid ID."); }
                lib.returnBook(id);
            } else if (choice == 6) {
                std::cout << "Goodbye!\n";
                break;
            } else {
                std::cout << "[Error] Invalid menu choice.\n";
            }
        } catch (const LibraryException& e) {
            std::cout << "[Exception] " << e.what() << "\n";
        }
    }

    return 0;
}