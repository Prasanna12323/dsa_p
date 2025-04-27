#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int MAX_NAME_LENGTH = 50;
const int MAX_DESIGNATION_LENGTH = 50;

// Structure to represent an employee
struct Employee {
    int employeeID;
    char name[MAX_NAME_LENGTH];
    char designation[MAX_DESIGNATION_LENGTH];
    double salary;
};

// Function to add an employee to the file
void addEmployee(fstream& file) {
    Employee employee;
    cout << "Enter employee ID: ";
    cin >> employee.employeeID;
    cout << "Enter employee name: ";
    cin.ignore();  // Clear the input buffer
    cin.getline(employee.name, MAX_NAME_LENGTH);

    cout << "Enter employee designation: ";
    cin.getline(employee.designation, MAX_DESIGNATION_LENGTH);

    cout << "Enter employee salary: ";
    cin >> employee.salary;

    // Move the file pointer to the end before writing
    file.seekp(0, ios::end);
    file.write(reinterpret_cast<char*>(&employee), sizeof(Employee));
    cout << "Employee added successfully!" << endl;
}

// Function to delete an employee from the file
void deleteEmployee(fstream& file) {
    int employeeID;
    bool found = false;
    Employee employee;

    cout << "Enter employee ID to delete: ";
    cin >> employeeID;

    // Create a temporary file to store all records except the one to delete
    fstream tempfile("temp.dat", ios::out | ios::binary);
    file.seekg(0, ios::beg);  // Move the file pointer to the beginning

    // Read each employee record and write to temporary file except the one to delete
    while (file.read(reinterpret_cast<char*>(&employee), sizeof(Employee))) {
        if (employee.employeeID != employeeID) {
            tempfile.write(reinterpret_cast<char*>(&employee), sizeof(Employee));
        } else {
            found = true;  // Mark the employee as found
        }
    }

    file.close();  // Close the original file
    tempfile.close();  // Close the temporary file

    // Delete the original file and rename the temporary file
    if (found) {
        remove("employee_data.dat");
        rename("temp.dat", "employee_data.dat");
        cout << "Employee deleted successfully!" << endl;
    } else {
        cout << "Employee not found!" << endl;
    }

    // Reopen the file for further operations
    file.open("employee_data.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "Error reopening the file!" << endl;
        return;
    }
}

// Function to display an employee's details
void displayEmployee(fstream& file) {
    int employeeID;
    bool found = false;
    Employee employee;

    cout << "Enter employee ID to display: ";
    cin >> employeeID;

    file.seekg(0, ios::beg);  // Move the file pointer to the beginning

    // Search for the employee by ID
    while (file.read(reinterpret_cast<char*>(&employee), sizeof(Employee))) {
        if (employee.employeeID == employeeID) {
            found = true;
            break;  // Employee found, exit loop
        }
    }

    // Display employee details if found
    if (found) {
        cout << "Employee ID: " << employee.employeeID << endl;
        cout << "Name: " << employee.name << endl;
        cout << "Designation: " << employee.designation << endl;
        cout << "Salary: " << employee.salary << endl;
    } else {
        cout << "Employee not found!" << endl;
    }
}

// Main function to interact with the system
int main() {
    // Attempt to open the file, and if it doesn't exist, create it
    fstream file("employee_data.dat", ios::in | ios::out | ios::binary);

    // Check if the file exists and open it in read-write mode, otherwise, create it
    if (!file) {
        // File doesn't exist, create a new one
        cout << "File not found. Creating a new file..." << endl;
        file.open("employee_data.dat", ios::out | ios::binary);  // Open in write mode to create it
        if (!file) {
            cout << "Error opening file for creation!" << endl;
            return 1;
        }
    }

    // Close and reopen the file in read-write mode
    file.close();
    file.open("employee_data.dat", ios::in | ios::out | ios::binary);

    while (true) {
        // Display menu options
        cout << "\nEmployee Information System" << endl;
        cout << "1. Add Employee" << endl;
        cout << "2. Delete Employee" << endl;
        cout << "3. Display Employee" << endl;
        cout << "4. Quit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        // Switch statement to perform actions based on the user's choice
        switch (choice) {
            case 1:
                addEmployee(file);  // Add a new employee
                break;

            case 2:
                deleteEmployee(file);  // Delete an employee
                break;

            case 3:
                displayEmployee(file);  // Display an employee's details
                break;

            case 4:
                file.close();  // Close the file before quitting
                return 0;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
