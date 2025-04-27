#include <iostream>
#include <list>
#include <cstdlib>
using namespace std;

class set {
private:
    int num, flag = 1;
public:
    list<int> l, l1, u, I, d;  // Lists to represent the sets A, B, Union, Intersection, and Difference
    list<int>::iterator t, t1, t2, t3, t4;  // Iterators for list traversal
    
    // Function declarations
    void add();          // Function to add an element to a set
    void delete1(int);   // Function to delete an element from both sets
    void search(int);    // Function to search for an element in sets
    void searchB(int);   // Function to search for an element in set B (unused)
    void display();      // Function to display elements of both sets
    void union1();       // Function to perform the union of sets A and B
    void Intersection(); // Function to find the intersection of sets A and B
    void insert();       // Function to insert elements into sets A and B
    void Differerence(); // Function to find the difference between sets A and B
};

// Function to insert elements into sets A and B
void set::insert() {
    int n, m;
    cout << "\nSET A:\n";
    cout << "How many Elements You want Add in Set A:\n";
    cin >> n;
    cout << "Enter Elements\n";
    for (int i = 0; i < n; i++) {
        cin >> num;
        l.push_back(num);  // Add elements to set A
    }

    cout << "\nSET B:\n";
    cout << "How many Elements You want Add in Set B:\n";
    cin >> m;
    cout << "Enter Elements\n";
    for (int i = 0; i < m; i++) {
        cin >> num;
        l1.push_back(num);  // Add elements to set B
    }
}

// Function to add an element to a set (A or B)
void set::add() {
    char c;
    cout << "In Which Set do you want Add Element (A/B)\n";
    cin >> c;
    if (c == 'A' || c == 'a') {
        cout << "Enter Elements\n";
        cin >> num;
        l.push_back(num);  // Add to set A
        cout << "\nElement Inserted\n";
    }
    else if (c == 'B' || c == 'b') {
        cout << "Enter Elements\n";
        cin >> num;
        l1.push_back(num);  // Add to set B
        cout << "\nElement Inserted\n";
    }
    else {
        cout << "Invalid Set!!!";
    }
}

// Function to display the elements of both sets
void set::display() {
    cout << "The Elements for Set A:\n{\t";
    for (t = l.begin(); t != l.end(); t++) {
        cout << *t << "\t";  // Display elements of set A
    }
    cout << "}\n\n";
    
    cout << "The Elements for Set B:\n{\t";
    for (t1 = l1.begin(); t1 != l1.end(); t1++) {
        cout << *t1 << "\t";  // Display elements of set B
    }
    cout << "}\n";
}

// Function to search for an element in both sets
void set::search(int key) {
    for (t = l.begin(), t1 = l1.begin(); t != l.end(); t++, t1++) {
        if (*t == key || *t1 == key) {
            cout << "The Element is Present\n";
            flag = 1;
            break;
        }
        else
            flag = 0;
    }
    if (flag == 0) {
        cout << "The Element is not Present\n";
    }
}

// Function to delete an element from both sets
void set::delete1(int key) {
    if (l.empty() && l1.empty()) {
        cout << "The Set A & Set B is Empty\n";
    }
    else {
        search(key);  // Search for the element
        if (flag == 1) {
            l.remove(key);  // Remove from set A
            l1.remove(key);  // Remove from set B
            cout << "Element Deleted\n";
        }
        else {
            cout << "Element not Deleted\n";
        }
    }
}

// Function to perform the union of sets A and B
void set::union1() {
    int flag = 0;
    for (t = l.begin(); t != l.end(); t++) {
        u.push_back(*t);  // Add all elements of set A to the union set
    }
    for (t1 = l1.begin(); t1 != l1.end(); t1++) {
        for (t2 = u.begin(); t2 != u.end(); t2++) {
            if (*t1 == *t2) {
                flag = 0;
                break;
            }
            else {
                flag = 1;
            }
        }
        if (flag == 1) {
            u.push_back(*t1);  // Add unique elements from set B to the union set
        }
    }
    
    cout << "The Union Set of A & B is : {\t";
    for (t2 = u.begin(); t2 != u.end(); t2++) {
        cout << *t2 << "\t";  // Display the union set
    }
    cout << "}\n";
}

// Function to perform the intersection of sets A and B
void set::Intersection() {
    for (t = l.begin(); t != l.end(); t++) {
        for (t1 = l1.begin(); t1 != l1.end(); t1++) {
            if (*t == *t1) {
                I.push_back(*t);  // Add common elements to the intersection set
                break;
            }
        }
    }
    if (I.empty()) {
        cout << "There is no Common element in Set A & Set B\n";
    }
    else {
        cout << "The Intersection Set of A & B is : {\t";
        for (t3 = I.begin(); t3 != I.end(); t3++) {
            cout << *t3 << "\t";  // Display the intersection set
        }
        cout << "}\n";
    }
}

// Function to perform the difference between sets A and B
void set::Differerence() {
    int flag = 0;
    for (t = l.begin(); t != l.end(); t++) {
        for (t1 = l1.begin(); t1 != l1.end(); t1++) {
            if (*t == *t1) {
                flag = 0;
                break;
            }
            else {
                flag = 1;
            }
        }
        if (flag == 1) {
            d.push_back(*t);  // Add elements unique to set A to the difference set
        }
    }
    if (d.empty()) {
        cout << "The Set A & Set B are Equal\n";
    }
    else {
        cout << "The Difference Set of A & B is : {\t";
        for (t4 = d.begin(); t4 != d.end(); t4++) {
            cout << *t4 << "\t";  // Display the difference set
        }
        cout << "}\n";
    }
}

int main() {
    set s;
    int ch, key;
    s.insert();  // Initial insertion of sets A and B
    while (1) {
        cout << "\n\n-----------------------------\n";
        cout << "\nSet Theory\n";
        cout << "\n-----------------------------\n";
        cout << "1.Add Element\n";
        cout << "2.Delete Element\n";
        cout << "3.Search Element\n";
        cout << "4.Display\n";
        cout << "5.Union\n";
        cout << "6.Intersection\n";
        cout << "7.Difference\n";
        cout << "8.Exit\n";
        cout << "Enter Your Choice: ";
        cin >> ch;
        switch (ch) {
            case 1: s.add(); break;  // Add an element to a set
            case 2: 
                cout << "Enter which Element to Delete: ";
                cin >> key;
                s.delete1(key); break;  // Delete an element from sets
            case 3: 
                cout << "Enter the Element to be Searched: ";
                cin >> key;
                s.search(key); break;  // Search for an element in sets
            case 4: 
                cout << endl; 
                s.display(); break;  // Display sets A and B
            case 5: s.union1(); break;  // Perform union of sets A and B
            case 6: s.Intersection(); break;  // Perform intersection of sets A and B
            case 7: s.Differerence(); break;  // Perform difference between sets A and B
            case 8: 
                cout << "Exiting..."; 
                exit(1); break;  // Exit the program
            default: 
                cout << "Invalid Choice";  // Handle invalid choice
        }
    }
    return 0;
}
