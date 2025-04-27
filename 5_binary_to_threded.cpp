#include<iostream>
#include<stdlib.h>
using namespace std;

struct node {
    int data;
    node *left, *right;
    int lbit, rbit; // lbit and rbit to differentiate between pointers and threads
};

class tbt {
    node *temp = NULL, *t1 = NULL, *s = NULL, *head = NULL, *t = NULL;

public:
    node* create();                     // To create a new node
    void insert();                      // To insert a new node in the tree
    node* insuc(node*);                 // To find the inorder successor of a node
    node* inpre(node*);                 // To find the inorder predecessor of a node
    void dis();                         // To display all nodes in the tree
    void display(node*);                // Recursive function to display the tree
    void thr();                         // To display all the threaded nodes
    void thread(node*);                 // To recursively display threaded nodes
};

// Function to create a new node with data
node* tbt::create() {
    node *p = new(struct node);
    p->left = NULL;
    p->right = NULL;
    p->lbit = 0;
    p->rbit = 0;
    cout << "\nEnter the data: ";
    cin >> p->data;
    return p;
}

// Function to insert a new node into the threaded binary tree
void tbt::insert() {
    temp = create(); // Create a new node

    if (head == NULL) {  // If the tree is empty, create a root node
        node *p = new(struct node);
        head = p;
        head->left = temp;
        head->right = head;
        head->lbit = 1;
        head->rbit = 0;
        temp->left = head;
        temp->right = head;
        temp->lbit = 0;
        temp->rbit = 0;
    } else {
        t1 = head;
        t1 = t1->left;

        while (t1 != NULL) {  // Traverse the tree to find the right place for the new node
            s = t1;
            if ((temp->data) > (t1->data) && t1->rbit == 1) {
                t1 = t1->right;
            } else if ((temp->data) < (t1->data) && t1->lbit == 1) {
                t1 = t1->left;
            } else {
                break;
            }
        }

        // Insert the node at the correct position
        if (temp->data > s->data) {
            s->right = temp;
            s->rbit = 1;
            temp->left = inpre(head->left);  // Set left thread to inorder predecessor
            temp->right = insuc(head->left); // Set right thread to inorder successor
        } else {
            s->left = temp;
            s->lbit = 1;
            temp->left = inpre(head->left);  // Set left thread to inorder predecessor
            temp->right = insuc(head->left); // Set right thread to inorder successor
        }
    }
}

// Function to find the inorder predecessor of a node
node* tbt::inpre(node* m) {
    if (m->lbit == 1) {
        return inpre(m->left);  // Recursively find the inorder predecessor if left bit is 1
    }
    if (m->data == temp->data && t == NULL) {
        return head;  // Return head if predecessor is found
    }
    if (m->data == temp->data) {
        return t;  // Return the predecessor if found
    }
    t = m;
    if (m->rbit == 1) {
        return inpre(m->right);  // Continue finding the predecessor from right subtree if right bit is 1
    }
    return nullptr;  // Return nullptr if no predecessor found
}

// Function to find the inorder successor of a node
node* tbt::insuc(node* m) {
    if (m->lbit == 1) {
        t = m;
        return insuc(m->left);  // Recursively find the inorder successor if left bit is 1
    }
    if (m->data == temp->data && t == NULL) {
        return head;  // Return head if successor is found
    }
    if (m->data == temp->data) {
        return t;  // Return the successor if found
    }
    if (m->rbit == 1) {
        return insuc(m->right);  // Continue finding the successor from right subtree if right bit is 1
    }
    return nullptr;  // Return nullptr if no successor found
}

// Function to display all nodes in the tree
void tbt::dis() {
    display(head->left);  // Display starting from the left child of the head
}

// Recursive function to display the tree in an inorder manner
void tbt::display(node* m) {
    if (m->lbit == 1) {
        display(m->left);  // Recursively display the left subtree if left bit is 1
    }
    cout << "\n" << m->data;  // Print the current node's data
    if (m->rbit == 1) {
        display(m->right);  // Recursively display the right subtree if right bit is 1
    }
}

// Function to display all the threaded nodes in the tree
void tbt::thr() {
    cout << "\nThreads are:";
    thread(head->left);  // Display threaded nodes starting from the left child of the head
}

// Recursive function to display threaded nodes
void tbt::thread(node* m) {
    if (m->lbit == 1) {
        thread(m->left);  // Recursively traverse the left subtree if left bit is 1
    }
    if (m->lbit == 0 || m->rbit == 0) {
        cout << "\n" << m->data;  // Print the node if it is a threaded node (left or right bit is 0)
    }
    if (m->rbit == 1) {
        thread(m->right);  // Recursively traverse the right subtree if right bit is 1
    }
}

// Main function to test the threaded binary tree operations
int main() {
    tbt t; 
    int ch;
    
    while (1) {
        cout << "\nEnter the choice";
        cout << "\n1. Insert data";
        cout << "\n2. Display all data";
        cout << "\n3. Display threaded nodes";
        cout << "\n4. Exit";
        cin >> ch;
        
        switch(ch) {
            case 1:
                t.insert();  // Insert data into the tree
                break;
            case 2:
                t.dis();  // Display all data in the tree
                break;
            case 3:
                t.thr();  // Display all threaded nodes
                break;
            case 4:
                exit(0);  // Exit the program
            default:
                cout << "\nInvalid entry";  // Handle invalid choices
        }
    }
    return 0;
}
