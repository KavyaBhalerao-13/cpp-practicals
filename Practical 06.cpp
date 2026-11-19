#include <iostream>
#include <string>
#include <iomanip>

// Abstract Base Class
class Shape {
public:
    // Pure virtual functions make Shape an abstract class
    virtual double area() const = 0;
    virtual std::string name() const = 0;

    // Virtual destructor ensures derived class destructors are called
    // properly when deleting through a base-class pointer
    virtual ~Shape() {
        std::cout << "[Destructor] Shape destroyed.\n";
    }
};

// Derived Class 1: Circle
class Circle : public Shape {
private:
    double radius;

public:
    explicit Circle(double r) : radius(r) {}

    double area() const override {
        const double PI = 3.14159265358979;
        return PI * radius * radius;
    }

    std::string name() const override {
        return "Circle (radius = " + std::to_string(radius) + ")";
    }

    ~Circle() override {
        std::cout << "[Destructor] Circle destroyed.\n";
    }
};

// Derived Class 2: Rectangle
class Rectangle : public Shape {
private:
    double length;
    double width;

public:
    Rectangle(double l, double w) : length(l), width(w) {}

    double area() const override {
        return length * width;
    }

    std::string name() const override {
        return "Rectangle";
    }

    ~Rectangle() override {
        std::cout << "[Destructor] Rectangle destroyed.\n";
    }
};

// Derived Class 3: Triangle
class Triangle : public Shape {
private:
    double base;
    double height;

public:
    Triangle(double b, double h) : base(b), height(h) {}

    double area() const override {
        return 0.5 * base * height;
    }

    std::string name() const override {
        return "Triangle";
    }

    ~Triangle() override {
        std::cout << "[Destructor] Triangle destroyed.\n";
    }
};

int main() {
    // Shape s; // COMPILER ERROR: Cannot instantiate an abstract class!

    // Base-class pointers holding derived-class objects
    Shape* shapes[3];
    shapes[0] = new Circle(5.0);
    shapes[1] = new Rectangle(4.0, 6.0);
    shapes[2] = new Triangle(8.0, 3.0);

    std::cout << "=== Runtime Polymorphism: Calculating Areas ===\n";
    std::cout << std::fixed << std::setprecision(2);

    for (int i = 0; i < 3; ++i) {
        // Calls the correct derived class area() at runtime
        std::cout << shapes[i]->name() << " -> Area = " << shapes[i]->area() << "\n";
    }

    std::cout << "\n=== Cleaning Up (Virtual Destructors) ===\n";
    for (int i = 0; i < 3; ++i) {
        delete shapes[i];
    }

    return 0;
}