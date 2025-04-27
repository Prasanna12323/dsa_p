#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

class tel {
public:
    int rollNo;
    char name[10];
    char div;
    char address[20];

    // Accept student data
    void accept() {
        cout << "\tEnter Roll Number: ";
        cin >> rollNo;
        cout << "\tEnter the Name: ";
        cin >> name;
        cout << "\tEnter the Division: ";
        cin >> div;
        cout << "\tEnter the Address: ";
        cin >> address;
    }

    // Accept roll number to modify a record
    void accept2() {
        cout << "\n\tEnter the Roll No. to modify: ";
        cin >> rollNo;
    }

    // Accept name to modify a record
    void accept3() {
        cout << "\n\tEnter the name to modify: ";
        cin >> name;
    }

    // Get roll number for comparison
    int getRollNo() {
        return rollNo;
    }

    // Show student details
    void show() {
        cout << "\n\t" << rollNo << "\t\t" << name << "\t\t" << div << "\t\t" << address;
    }
};

int main() {
    int ch, ch1, rec, add, n1, n2, n3, n4, on;
    char name[20], name2[20];
    tel t1;
    fstream f, g;

    do {
        cout << "\n>>>>>>>>>>>>>>>>>>>>>>MENU<<<<<<<<<<<<<<<<<<<<";
        cout << "\n1. Insert and overwrite";
        cout << "\n2. Show";
        cout << "\n3. Search & Edit (number)";
        cout << "\n4. Search & Edit (name)";
        cout << "\n5. Search & Edit (only number)";
        cout << "\n6. Search & Edit (only name)";
        cout << "\n7. Delete a Student Record";
        cout << "\n8. Exit";
        cout << "\n\tEnter the Choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                f.open("StuRecord.txt", ios::out);  // Open file for writing
                do {
                    t1.accept();  // Accept student data
                    f.write((char*)&t1, sizeof(t1));  // Write data to file
                    cout << "\nDo you want to enter more records?\n1. Yes\n2. No: ";
                    cin >> ch1;
                } while (ch1 == 1);
                f.close();
                break;

            case 2:
                f.open("StuRecord.txt", ios::in);  // Open file for reading
                while (f.read((char*)&t1, sizeof(t1))) {
                    t1.show();  // Show student record
                }
                f.close();
                break;

            case 3:
                cout << "\nEnter the roll number you want to find: ";
                cin >> rec;
                f.open("StuRecord.txt", ios::in | ios::out);  // Open file for input/output
                while (f.read((char*)&t1, sizeof(t1))) {
                    if (rec == t1.rollNo) {  // Record found
                        cout << "\nRecord found";
                        add = f.tellg();  // Get the current position in file
                        f.seekg(0, ios::beg);  // Move to beginning
                        n1 = (add - f.tellg()) / sizeof(t1);  // Calculate record position
                        f.seekp(n1 * sizeof(t1), ios::beg);  // Seek to the record
                        t1.accept();  // Accept new data
                        f.write((char*)&t1, sizeof(t1));  // Overwrite record
                        f.close();
                        break;
                    }
                }
                if (f.eof()) {
                    cout << "\nRecord not found";
                }
                f.close();
                break;

            case 4:
                cout << "\nEnter the name you want to find and edit: ";
                cin >> name;
                f.open("StuRecord.txt", ios::in | ios::out);
                while (f.read((char*)&t1, sizeof(t1))) {
                    if (strcmp(name, t1.name) == 0) {  // Name found
                        cout << "\nName found";
                        add = f.tellg();
                        f.seekg(0, ios::beg);
                        n2 = (add - f.tellg()) / sizeof(t1);
                        f.seekp(n2 * sizeof(t1), ios::beg);
                        t1.accept();  // Accept new data
                        f.write((char*)&t1, sizeof(t1));  // Overwrite record
                        f.close();
                        break;
                    }
                }
                f.close();
                break;

            case 5:
                cout << "\n\tEnter the roll number you want to modify: ";
                cin >> on;
                f.open("StuRecord.txt", ios::in | ios::out);
                while (f.read((char*)&t1, sizeof(t1))) {
                    if (on == t1.rollNo) {  // Roll number found
                        cout << "\n\tNumber found";
                        add = f.tellg();
                        f.seekg(0, ios::beg);
                        n3 = (add - f.tellg()) / sizeof(t1);
                        f.seekp(n3 * sizeof(t1), ios::beg);
                        t1.accept2();  // Accept roll number to modify
                        f.write((char*)&t1, sizeof(t1));
                        f.close();
                        break;
                    }
                }
                f.close();
                break;

            case 6:
                cout << "\nEnter the name you want to find and edit: ";
                cin >> name2;
                f.open("StuRecord.txt", ios::in | ios::out);
                while (f.read((char*)&t1, sizeof(t1))) {
                    if (strcmp(name2, t1.name) == 0) {  // Name found
                        cout << "\nName found";
                        add = f.tellg();
                        f.seekg(0, ios::beg);
                        n4 = (add - f.tellg()) / sizeof(t1);
                        f.seekp(n4 * sizeof(t1), ios::beg);
                        t1.accept3();  // Accept name to modify
                        f.write((char*)&t1, sizeof(t1));
                        f.close();
                        break;
                    }
                }
                f.close();
                break;

            case 7:
                int roll;
                cout << "Please Enter the Roll No. of Student Whose Info You Want to Delete: ";
                cin >> roll;
                f.open("StuRecord.txt", ios::in);
                g.open("temp.txt", ios::out);
                while (f.read((char*)&t1, sizeof(t1))) {
                    if (t1.getRollNo() != roll) {  // Skip record if roll number doesn't match
                        g.write((char*)&t1, sizeof(t1));
                    }
                }
                cout << "The record with the roll no. " << roll << " has been deleted." << endl;
                f.close();
                g.close();
                remove("StuRecord.txt");  // Remove original file
                rename("temp.txt", "StuRecord.txt");  // Rename temp file to original file name
                break;

            case 8:
                cout << "\n\tThank you!";
                break;

            default:
                cout << "\nInvalid choice! Please try again.";
        }

    } while (ch != 8);  // Continue loop until exit choice is selected

    return 0;
}
