
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int age;
    float marks;
    char grade;
    string name;

    const float bonus = 5.0;

    // Taking input
    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter your age: ";
    cin >> age;

    cout << "Enter your marks: ";
    cin >> marks;

    cout << "Enter your grade: ";
    cin >> grade;

    // Arithmetic operator
    float total = marks + bonus;

    // Relational operator
    bool isAdult = (age >= 18);

    // Logical operator
    bool isEligible = (age >= 18 && marks >= 35);

    // Display output
    cout << "\n----- STUDENT DETAILS -----" << endl;

    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Marks: " << marks << endl;
    cout << "Grade: " << grade << endl;
    cout << "Bonus Marks: " << bonus << endl;
    cout << "Total Marks: " << total << endl;

    cout << "Adult: " << isAdult << endl;
    cout << "Eligible: " << isEligible << endl;

    return 0;
}
