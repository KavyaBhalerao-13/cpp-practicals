#include <iostream>
#include <utility> // for std::move

class IntArray {
private:
    int* data;
    size_t size;

public:
    // 1. Default Constructor
    IntArray() : data(nullptr), size(0) {
        std::cout << "[Default Constructor] Created empty IntArray.\n";
    }

    // 2. Parameterized Constructor
    explicit IntArray(size_t s) : data(s > 0 ? new int[s] : nullptr), size(s) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = static_cast<int>((i + 1) * 10); // Sample values: 10, 20, 30...
        }
        std::cout << "[Parameterized Constructor] Allocated array of size " << size << ".\n";
    }

    // --- RULE OF FIVE MEMBERS ---

    // 1/5: Destructor
    // Releases the dynamically allocated memory when the object goes out of scope.
    ~IntArray() {
        delete[] data;
        std::cout << "[Destructor] Released memory (size was " << size << ").\n";
    }

    // 2/5: Copy Constructor (Deep Copy)
    // Allocates separate memory and copies each element so two objects don't share the same pointer.
    IntArray(const IntArray& other) : data(other.size > 0 ? new int[other.size] : nullptr), size(other.size) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        std::cout << "[Copy Constructor] Deep copied array of size " << size << ".\n";
    }

    // 3/5: Copy Assignment Operator (Deep Copy)
    // Frees existing memory, guards against self-assignment, and deep copies from 'other'.
    IntArray& operator=(const IntArray& other) {
        std::cout << "[Copy Assignment] Called.\n";
        if (this == &other) {
            return *this; // Guard against self-assignment (e.g., a = a)
        }

        delete[] data; // Release old resource

        size = other.size;
        data = (size > 0) ? new int[size] : nullptr;
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }

    // 4/5: Move Constructor (Ownership Transfer)
    // Steals the pointer from a temporary/moved-from object and leaves it in a safe empty state.
    IntArray(IntArray&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "[Move Constructor] Transferred ownership of array (size " << size << ").\n";
    }

    // 5/5: Move Assignment Operator (Ownership Transfer)
    // Frees existing memory, steals the pointer from 'other', and nulls out 'other'.
    IntArray& operator=(IntArray&& other) noexcept {
        std::cout << "[Move Assignment] Called.\n";
        if (this == &other) {
            return *this;
        }

        delete[] data; // Release old resource

        data = other.data;
        size = other.size;

        other.data = nullptr;
        other.size = 0;
        return *this;
    }

    // Helper function to display contents
    void print(const std::string& label) const {
        std::cout << label << " (size=" << size << "): [ ";
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << "]\n";
    }
};

int main() {
    std::cout << "--- 1. Default & Parameterized Constructors ---\n";
    IntArray arr1;          // Calls Default Constructor
    IntArray arr2(3);       // Calls Parameterized Constructor
    arr2.print("arr2");

    std::cout << "\n--- 2. Copy Constructor ---\n";
    IntArray arr3 = arr2;   // Calls Copy Constructor
    arr3.print("arr3");

    std::cout << "\n--- 3. Copy Assignment ---\n";
    arr1 = arr2;            // Calls Copy Assignment Operator
    arr1.print("arr1");

    std::cout << "\n--- 4. Move Constructor ---\n";
    IntArray arr4 = std::move(arr2); // Calls Move Constructor
    arr4.print("arr4");
    arr2.print("arr2 (after move)"); // Should be empty (size=0)

    std::cout << "\n--- 5. Move Assignment ---\n";
    IntArray arr5;
    arr5 = std::move(arr3); // Calls Move Assignment Operator
    arr5.print("arr5");
    arr3.print("arr3 (after move)"); // Should be empty (size=0)

    std::cout << "\n--- 6. Leaving main() (Destructors will run) ---\n";
    return 0;
}