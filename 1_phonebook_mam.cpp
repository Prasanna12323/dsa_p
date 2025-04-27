#include <iostream>
using namespace std;

// Node class to store details: key, name, and telephone number
class node {
private:
    string name;  // Name of the person
    string telephone;  // Telephone number of the person
    int key;  // Key generated based on the name
public:
    node() {
        key = 0;  // Initialize key to 0
    }
    friend class hashing;  // Grant access to private members of node class to hashing class
};

// Hash function that generates a unique key based on the sum of ASCII values of characters in the string
int ascii_generator(string s) {
    int sum = 0;
    for (int i = 0; s[i] != '\0'; i++)
        sum = sum + s[i];  // Add ASCII value of each character
    return sum % 100;  // Return the key as the sum modulo 100
}

// Hashing class that handles the creation, searching, updating, deleting, and displaying records
class hashing {
private:
    node data[100];  // Array of nodes (size of directory is 100)
    string n;  // To store name
    string tele;  // To store telephone number
    int k, index;  // Variables to store the key and index for the hash table
    int size = 100;  // Size of the hash table
public:
    hashing() {
        k = 0;  // Initialize key to 0
    }

    // Function to create a new record
    void create_record(string n, string tele) {
        k = ascii_generator(n);  // Generate key using the ASCII value of the name
        index = k % size;  // Find the index in the hash table
        for (int j = 0; j < size; j++) {
            if (data[index].key == 0) {  // If the position is empty, insert the record
                data[index].key = k;
                data[index].name = n;
                data[index].telephone = tele;
                break;
            }
            else  // If the position is occupied, move to the next index (linear probing)
                index = (index + 1) % size;
        }
    }

    // Function to search for a record by name
    void search_record(string name) {
        int index1, k, flag = 0;
        k = ascii_generator(name);  // Generate the key for the name
        index1 = k % size;  // Find the index in the hash table
        for (int a = 0; a < size; a++) {
            if (data[index1].key == k) {  // Check if the record exists at this index
                flag = 1;
                cout << "\nRecord found\n";
                cout << "Name :: " << data[index1].name << endl;
                cout << "Telephone :: " << data[index1].telephone << endl;
                break;
            }
            else  // If not, move to the next index (linear probing)
                index1 = (index1 + 1) % size;
        }
        if (flag == 0)  // If record is not found, print a message
            cout << "Record not found";
    }

    // Function to delete a record by name
    void delete_record(string name) {
        int index1, key, flag = 0;
        key = ascii_generator(name);  // Generate the key for the name
        index1 = key % size;  // Find the index in the hash table
        for (int a = 0; a < size; a++) {
            if (data[index].key == key) {  // If the record is found, delete it
                flag = 1;
                data[index1].key = 0;
                data[index1].name = " ";
                data[index1].telephone = " ";
                cout << "\nRecord Deleted successfully" << endl;
                break;
            }
            else  // If not, move to the next index (linear probing)
                index1 = (index1 + 1) % size;
        }
        if (flag == 0)  // If record is not found, print a message
            cout << "\nRecord not found";
    }

    // Function to update an existing record's telephone number
    void update_record(string name) {
        int index1, key, flag = 0;
        key = ascii_generator(name);  // Generate the key for the name
        index1 = key % size;  // Find the index in the hash table
        for (int a = 0; a < size; a++) {
            if (data[index1].key == key) {  // If the record is found
                flag = 1;
                break;
            }
            else  // If not, move to the next index (linear probing)
                index1 = (index1 + 1) % size;
        }
        if (flag == 1) {
            cout << "Enter the new telephone number :: ";
            cin >> tele;  // Get the new telephone number
            data[index1].telephone = tele;  // Update the telephone number
            cout << "\nRecord Updated successfully";
        }
    }

    // Function to display all records in the directory
    void display_record() {
        cout << "\t Name \t\t Telephone";
        for (int a = 0; a < size; a++) {
            if (data[a].key != 0) {  // If there is a valid record at this index, display it
                cout << "\n\t" << data[a].name << " \t\t\t " << data[a].telephone;
            }
        }
    }
};

// Main function that drives the menu-driven program for telephone book operations
int main() {
    hashing s;  // Create a hashing object
    string name, telephone;  // Variables to store name and telephone number
    int choice, x;
    bool loop = 1;

    // Menu-driven loop for user input
    while (loop) {
        cout << "\n-------------------------" << endl
             << " Telephone book Database " << endl
             << "-------------------------" << endl
             << "1. Create Record" << endl
             << "2. Display Record" << endl
             << "3. Search Record" << endl
             << "4. Update Record" << endl
             << "5. Delete Record" << endl
             << "6. Exit" << endl
             << "Enter choice :: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nEnter name :: ";
                cin >> name;
                cout << "Enter Telephone number :: ";
                cin >> telephone;
                s.create_record(name, telephone);  // Create a new record
                break;

            case 2:
                s.display_record();  // Display all records
                break;

            case 3:
                cout << "\nEnter the name :: ";
                cin >> name;
                s.search_record(name);  // Search for a record
                break;

            case 4:
                cout << "\nEnter the name :: ";
                cin >> name;
                s.update_record(name);  // Update an existing record
                break;

            case 5:
                cout << "\nEnter name to Delete :: ";
                cin >> name;
                s.delete_record(name);  // Delete a record
                break;

            case 6:
                loop = 0;  // Exit the loop
                break;

            default:
                cout << "\nYou Entered something wrong!";  // Handle invalid choices
                break;
        }
    }
    return 0;
}
