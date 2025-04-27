#include<iostream>
using namespace std;

#define MAX 20   // Define the maximum size of the heap

class stud {
    int mks[MAX]; // Array to store student marks
public:
    stud() {
        // Initialize all marks to 0
        for (int i = 0; i < MAX; i++)
            mks[i] = 0;
    }
    void insertheap(int tot);   // Function to insert marks into heap
    void displayheap(int tot);  // Function to display the heap
    void showmax(int tot);      // Function to find and display max marks
    void showmin();             // Function to display the min mark
};

// Function to insert marks into the min heap
void stud::insertheap(int tot) {
    for (int i = 1; i <= tot; i++) {
        cout << "Enter marks: ";   // Ask user to input marks
        cin >> mks[i];            // Store input in the heap array
        int j = i;
        int par = j / 2;
        // Maintain heap property by comparing with parent node
        while (j > 1 && mks[j] < mks[par]) {  // Check if current node is smaller than parent
            // Swap current node with its parent
            int tmp = mks[j];
            mks[j] = mks[par];
            mks[par] = tmp;
            j = par;  // Move upwards in the tree
            par = j / 2;  // Update parent
        }
    }
}

// Function to display the heap in a tree-like structure
void stud::displayheap(int tot) {
    int i = 1, space = 6;
    cout << endl;
    while (i <= tot) {
        // For each level of the tree, adjust spacing for proper tree format
        if (i == 1 || i == 2 || i == 4 || i == 8 || i == 16) {
            cout << endl << endl;
            for (int j = 0; j < space; j++) // Add space to visualize tree structure
                cout << " ";
            space -= 2; // Decrease space as tree grows
        }
        cout << " " << mks[i]; // Print the current node
        i++;  // Move to the next node in the heap
    }
}

// Function to find and display the maximum marks
void stud::showmax(int tot) {
    int max1 = mks[1];  // Initialize max as the root node
    for (int i = 2; i <= tot; i++) {
        if (max1 < mks[i])   // Update max if a larger value is found
            max1 = mks[i];
    }
    cout << "\nMax marks: " << max1;  // Output the maximum marks
}

// Function to display the minimum marks (always the root of the min heap)
void stud::showmin() {
    cout << "\nMin marks: " << mks[1];  // The root always has the smallest value in a min heap
}

int main() {
    int ch, cont, total;
    stud s1;  // Create an object of the 'stud' class to manage the heap
    do {
        // Display the menu to the user
        cout << endl << "Menu";
        cout << endl << "1. Read marks of the students";
        cout << endl << "2. Display Min Heap";
        cout << endl << "3. Find Max Marks";
        cout << endl << "4. Find Min Marks";
        cout << endl << "Enter Choice: ";
        cin >> ch;  // Get the user's choice
        switch (ch) {
            case 1:
                cout << "How many students: ";  // Ask the user for the number of students
                cin >> total;
                s1.insertheap(total);  // Insert student marks into the heap
                break;
            case 2:
                s1.displayheap(total);  // Display the heap structure
                break;
            case 3:
                s1.showmax(total);  // Find and display the maximum marks
                break;
            case 4:
                s1.showmin();  // Display the minimum marks
                break;
            default:
                cout << "\nInvalid choice!";  // Handle invalid choices
        }
        cout << endl << "\nDo you want to continue? (1 for continue): ";  // Ask if user wants to continue
        cin >> cont;
    } while (cont == 1);  // Continue if the user enters 1
    return 0;
}
