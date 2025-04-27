#include <iostream>
#include <string>
using namespace std;

// Structure for each node in the tree (book, chapter, section)
struct node {
    string label;    // Name of the book/chapter/section
    int ch_count;    // Number of child nodes (chapters/sections)
    node* child[10]; // Array of child nodes (max 10 children)
} *root;

class GT {  // Class to handle the book hierarchy (tree)
public:
    GT() {
        root = nullptr;  // Initialize root to null
    }
    
    // Function to create the book tree
    void create_tree();
    
    // Function to display the tree structure
    void display(node* r1);
};

// Function to create the tree structure
void GT::create_tree()
{
    int tchapters;
    root = new node;  // Allocate memory for root node

    cout << "Enter name of book: ";
    cin.ignore(); // Clear input buffer before getline
    getline(cin, root->label);  // Get the name of the book

    cout << "Enter number of chapters in book: ";
    cin >> tchapters;  // Get the number of chapters
    root->ch_count = tchapters;

    // Loop to input chapters
    for (int i = 0; i < tchapters; i++)
    {
        root->child[i] = new node;  // Allocate memory for each chapter
        cout << "Enter the name of Chapter " << i + 1 << ": ";
        cin.ignore();  // Clear input buffer
        getline(cin, root->child[i]->label);  // Get the name of the chapter

        cout << "Enter number of sections in Chapter \"" << root->child[i]->label << "\": ";
        cin >> root->child[i]->ch_count;  // Get the number of sections for the chapter

        // Loop to input sections for each chapter
        for (int j = 0; j < root->child[i]->ch_count; j++)
        {
            root->child[i]->child[j] = new node;  // Allocate memory for each section
            cout << "Enter name of Section " << j + 1 << ": ";
            cin.ignore();  // Clear input buffer
            getline(cin, root->child[i]->child[j]->label);  // Get the name of the section
        }
    }
}

// Function to display the book structure (book -> chapters -> sections)
void GT::display(node* r1)
{
    if (r1 != nullptr)  // Ensure the node is not null
    {
        cout << "\n----- Book Hierarchy -----";
        cout << "\nBook Title: " << r1->label;  // Display book title

        // Loop to display chapters
        for (int i = 0; i < r1->ch_count; i++)
        {
            cout << "\n  Chapter " << i + 1 << ": " << r1->child[i]->label;  // Display chapter title
            cout << "\n    Sections:";

            // Loop to display sections under each chapter
            for (int j = 0; j < r1->child[i]->ch_count; j++)
            {
                cout << "\n      " << r1->child[i]->child[j]->label;  // Display section title
            }
        }
        cout << endl;  // Print newline for formatting
    }
}

int main()
{
    int choice;
    GT gt;  // Create an object of the GT class

    while (true)
    {
        cout << "\n-----------------";
        cout << "\n Book Tree Creation";
        cout << "\n-----------------";
        cout << "\n1. Create";  // Option to create a book tree
        cout << "\n2. Display"; // Option to display the book tree
        cout << "\n3. Quit";  // Option to exit the program
        cout << "\nEnter your choice: ";
        cin >> choice;  // Get user input for the menu choice

        switch (choice)
        {
        case 1:  // Create a new book tree
            gt.create_tree();
            break;

        case 2:  // Display the book tree
            gt.display(root);
            break;

        case 3:  // Exit the program
            cout << "Thanks for using this program!" << endl;
            return 0;

        default:  // Invalid input handling
            cout << "Wrong choice! Try again." << endl;
        }
    }

    return 0;
}
