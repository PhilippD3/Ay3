#include "Employee.h"
#include <iostream>


Employee::Employee() : position(""), name(""), salary(0.0) {}

Employee::Employee(const std::string& position, const std::string& name, double salary) :
    position(position), name(name), salary(salary) {
    if (salary < 0) {
        throw std::invalid_argument("Salary cannot be negative.");
    }
}

Employee::~Employee() {}

std::string Employee::getPosition() const { return position; }
std::string Employee::getName() const { return name; }
double Employee::getSalary() const { return salary; }

void Employee::setPosition(const std::string& newPosition) { position = newPosition; }
void Employee::setName(const std::string& newName) { name = newName; }
void Employee::setSalary(double newSalary) {
    if (newSalary < 0) {
        throw std::invalid_argument("Salary cannot be negative.");
    }
    salary = newSalary;
}

void Employee::printInfo() const {
    std::cout << "Position: " << position << "\tName: " << name << "\tSalary: " << salary << std::endl;
}

Employee Employee::operator+(const Employee& other) const {
    return Employee(position, name, salary + other.salary);
}

bool Employee::operator==(const Employee& other) const {
    return position == other.position && name == other.name && salary == other.salary;
}
