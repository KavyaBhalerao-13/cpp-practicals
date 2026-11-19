#include <iostream>

// --- 1. Function Overloading (Compile-Time Polymorphism) ---
// Same function name 'add', different parameter types or counts
int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

int add(int a, int b, int c) {
    return a + b + c;
}

// --- 2. Operator Overloading using ComplexNumber ---
class ComplexNumber {
private:
    double real;
    double imag;

public:
    ComplexNumber(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // Overload the '+' operator to add two ComplexNumber objects
    ComplexNumber operator+(const ComplexNumber& other) const {
        return ComplexNumber(real + other.real, imag + other.imag);
    }

    void display() const {
        std::cout << real;
        if (imag >= 0) {
            std::cout << " + " << imag << "i";
        } else {
            std::cout << " - " << -imag << "i";
        }
    }
};

int main() {
    std::cout << "=== 1. Function Overloading ===\n";
    std::cout << "add(10, 20)         = " << add(10, 20) << "\n";
    std::cout << "add(3.5, 2.25)      = " << add(3.5, 2.25) << "\n";
    std::cout << "add(5, 10, 15)      = " << add(5, 10, 15) << "\n";

    std::cout << "\n=== 2. Operator Overloading (+) on ComplexNumber ===\n";
    ComplexNumber c1(3.5, 2.0);
    ComplexNumber c2(1.5, -4.5);
    ComplexNumber sum = c1 + c2; // Calls c1.operator+(c2)

    std::cout << "Operand 1 : "; c1.display(); std::cout << "\n";
    std::cout << "Operand 2 : "; c2.display(); std::cout << "\n";
    std::cout << "Sum (c1+c2): "; sum.display(); std::cout << "\n";

    return 0;
}