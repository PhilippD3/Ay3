#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <windows.h>
#include "Employee.h"

std::mutex mtx;
std::unordered_set<Employee> employees;

void addEmp() {
    std::string position, name;
    double salary;
    std::cout << "Enter position: ";
    std::cin.ignore();
    std::getline(std::cin, position);
    std::cout << "Enter name: ";
    std::getline(std::cin, name);
    std::cout << "Enter salary: ";
    std::cin >> salary;

    std::unique_lock<std::mutex> lock(mtx);
    employees.insert(Employee(position, name, salary));
}
void saveToFile(const std::string& filename) {
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        throw std::runtime_error("Failed to open file for writing");
    }

    for (const auto& employee : employees) {
        ofs << employee.getPosition() << "\t"
            << employee.getName() << "\t"
            << employee.getSalary() << std::endl;
    }
}

void loadFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        throw std::runtime_error("Failed to open file for reading");
    }

    std::string position;
    std::string name;
    double salary;

    while (ifs >> position >> name >> salary) {
        employees.insert(Employee(position, name, salary));
    }
}

void printEmployees() {
    for (const auto& employee : employees) {
        std::cout << employee.getPosition() << "\t"
            << employee.getName() << "\t"
            << employee.getSalary() << std::endl;
    }
}

void removeEmployee(const std::string& name) {
    std::unique_lock<std::mutex> lock(mtx);
    auto it = std::find_if(employees.begin(), employees.end(),
        [&](const Employee& e) { return e.getName() == name; });
    if (it != employees.end()) {
        employees.erase(it);
        std::cout << "Name " << name << " delete." << std::endl;
    }
    else {
        std::cout << "Name " << name << " Don't found" << std::endl;
    }
}


void deleteEmpoyees() {
    std::string name;
    std::cout << "Введите имя сотрудника для удаления: ";
    std::cin >> name;
    removeEmployee(name);
}
void SaveEmpoyees() {
    std::string falename = "text.txt";
    saveToFile(falename);
}
void LoadEmpoyees() {
    std::string falename = "text.txt";
    loadFromFile(falename);

}

int main() {
    setlocale(LC_ALL, "Russian");
    std::string filename = "employees.txt";

    while (true) {
        std::cout << "\033[1;32m" << "1. Добавить сотрудника\n";
        std::cout << "2. Найти сотрудника\n";
        std::cout << "3. Редактировать сотрудника\n";
        std::cout << "4. Вывести список сотрудников\n";
        std::cout << "5. Удалить сотрудника\n";
        std::cout << "6. Сохранить данные\n";
        std::cout << "7. Загрузить данные\n";
        std::cout << "8. Выход\n" << "\033[0m";
        std::cout << "Введите ваш выбор: ";
        int choice;
        std::cin >> choice;
        if (choice == 5) {
            std::thread t1(deleteEmpoyees);
            t1.join();
            continue;
        }
        if (choice == 6) {
            std::thread t2(SaveEmpoyees);
            t2.join();
            continue;
        }
        if (choice == 7) {
            std::thread t3(LoadEmpoyees);
            t3.join();
            continue;
        }

        switch (choice) {
        case 1: {
            addEmp();
            break;
        }
        case 2: {
            std::string name;
            std::cout << "Enter name: ";
            std::cin.ignore();
            std::getline(std::cin, name);

            std::unique_lock<std::mutex> lock(mtx);
            for (const auto& employee : employees) {
                if (employee.getName() == name) {
                    std::cout << employee.getPosition() << "\t"
                        << employee.getName() << "\t"
                        << employee.getSalary() << std::endl;
                }
            }
            break;
        }
                case 3: {
                    std::string name;
                    std::cout << "Enter name: ";
                    std::cin >> name;

                    auto it = std::find_if(employees.begin(), employees.end(),
                        [&name](const Employee& e) { return e.getName() == name; });

                    if (it != employees.end()) {
                        employees.erase(it);
                        std::cout << "Введите новые данные сотрудника:\n";
                        addEmp();
                    }
                    else {
                        std::cout << "Сотрудник не найден.\n";
                    }
                    break;
                }
        case 4: {
            std::unique_lock<std::mutex> lock(mtx);
            printEmployees();
            break;
        }
        case 8: {
            return 0;
        }
        default:
            std::cout << "Invalid choice!\n";
        }

    }
}
