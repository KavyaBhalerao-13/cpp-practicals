#include <iostream>
#include <string>

// Base Class
class Person {
protected:
    // Protected so derived classes (Student, GraduateStudent) can access them directly
    std::string name;
    int age;

public:
    Person(const std::string& n, int a) : name(n), age(a) {}

    void displayPerson() const {
        std::cout << "Name            : " << name << "\n";
        std::cout << "Age             : " << age << "\n";
    }
};

// Derived Class 1: Single Inheritance (Person -> Student)
class Student : public Person {
protected:
    int studentId;
    std::string course;

public:
    // Calls Person constructor to initialize inherited members
    Student(const std::string& n, int a, int id, const std::string& c)
        : Person(n, a), studentId(id), course(c) {}

    void displayStudent() const {
        displayPerson(); // Reusing base class function
        std::cout << "Student ID      : " << studentId << "\n";
        std::cout << "Course          : " << course << "\n";
    }
};

// Derived Class 2: Multilevel Inheritance (Person -> Student -> GraduateStudent)
class GraduateStudent : public Student {
private:
    std::string researchTopic;
    std::string supervisorName;

public:
    // Calls Student constructor, which in turn calls Person constructor
    GraduateStudent(const std::string& n, int a, int id, const std::string& c,
                    const std::string& topic, const std::string& supervisor)
        : Student(n, a, id, c), researchTopic(topic), supervisorName(supervisor) {}

    void displayGraduateStudent() const {
        displayStudent(); // Reusing Student (and indirectly Person) display
        std::cout << "Research Topic  : " << researchTopic << "\n";
        std::cout << "Supervisor      : " << supervisorName << "\n";
    }
};

int main() {
    std::cout << "=== 1. Single Inheritance (Person -> Student) ===\n";
    Student s1("Aarav Sharma", 20, 101, "B.Tech Computer Science");
    s1.displayStudent();

    std::cout << "\n=== 2. Multilevel Inheritance (Person -> Student -> GraduateStudent) ===\n";
    GraduateStudent g1("Priya Deshmukh", 24, 205, "M.Tech AI & Data Science",
                       "Explainable Machine Learning", "Dr. R. Kulkarni");
    g1.displayGraduateStudent();

    return 0;
}