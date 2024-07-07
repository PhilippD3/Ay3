#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

class Employee {
private:
    std::string position;
    std::string name;
    double salary;

public:
    Employee();
    Employee(const std::string& position, const std::string& name, double salary);

    ~Employee();

    std::string getPosition() const;
    std::string getName() const;
    double getSalary() const;

    void setPosition(const std::string& newPosition);
    void setName(const std::string& newName);
    void setSalary(double newSalary);

    void printInfo() const;

    Employee operator+(const Employee& other) const;

    bool operator==(const Employee& other) const;
};

namespace std {
    template <>
    struct hash<Employee> {
        size_t operator()(const Employee& employee) const {
            size_t h1 = std::hash<std::string>()(employee.getPosition());
            size_t h2 = std::hash<std::string>()(employee.getName());
            size_t h3 = std::hash<double>()(employee.getSalary());
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };
}

#endif 
