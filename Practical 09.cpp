#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

// Generic Stack class template
template <typename T>
class Stack {
private:
    std::vector<T> elements;

public:
    // Add an item to the top of the stack
    void push(const T& value) {
        elements.push_back(value);
    }

    // Remove the top item safely
    void pop() {
        if (isEmpty()) {
            throw std::underflow_error("Error: Cannot pop from an empty stack!");
        }
        elements.pop_back();
    }

    // Access the top item safely
    T top() const {
        if (isEmpty()) {
            throw std::underflow_error("Error: Stack is empty, no top element!");
        }
        return elements.back();
    }

    bool isEmpty() const {
        return elements.empty();
    }

    size_t size() const {
        return elements.size();
    }
};

int main() {
    // 1. Testing with int
    std::cout << "=== 1. Stack<int> ===\n";
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    std::cout << "Top element : " << intStack.top() << "\n";
    intStack.pop();
    std::cout << "After pop   : " << intStack.top() << " (size = " << intStack.size() << ")\n";

    // 2. Testing with float
    std::cout << "\n=== 2. Stack<float> ===\n";
    Stack<float> floatStack;
    floatStack.push(1.5f);
    floatStack.push(2.75f);
    std::cout << "Top element : " << floatStack.top() << "\n";
    floatStack.pop();
    std::cout << "After pop   : " << floatStack.top() << "\n";

    // 3. Testing with std::string
    std::cout << "\n=== 3. Stack<std::string> ===\n";
    Stack<std::string> strStack;
    strStack.push("C++");
    strStack.push("Templates");
    std::cout << "Top element : " << strStack.top() << "\n";
    strStack.pop();
    std::cout << "After pop   : " << strStack.top() << "\n";

    // 4. Testing Empty-Container Condition (Invalid Operation)
    std::cout << "\n=== 4. Testing Empty Stack Error Handling ===\n";
    strStack.pop(); // Now strStack is empty
    std::cout << "Is strStack empty? " << (strStack.isEmpty() ? "Yes" : "No") << "\n";

    try {
        std::cout << "Attempting to pop from empty stack...\n";
        strStack.pop();
    } catch (const std::underflow_error& e) {
        std::cout << "Caught Exception -> " << e.what() << "\n";
    }

    return 0;
}