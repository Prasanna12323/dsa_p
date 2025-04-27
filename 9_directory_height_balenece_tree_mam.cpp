#include<iostream>
using namespace std;

// Define a node class that represents an individual keyword entry in the AVL tree
class node {
public:
    string key;  // The keyword
    string meaning;  // The meaning of the keyword
    node *left;  // Pointer to left child (keywords smaller than current node)
    node *right;  // Pointer to right child (keywords greater than current node)
};

// Define the AVL class to manage the AVL tree operations
class AVL {
    node *root;  // The root node of the AVL tree
public:
    // Constructor initializes the root as NULL
    AVL() {
        root = NULL;
    }
    // Method to create the AVL tree by inserting new nodes
    void create();
    // Method to insert a new node in the AVL tree
    node* insert(node *cur, node *temp);
    // Method to balance the tree after insertion
    node* balance(node *temp);
    // Method to calculate the balance factor (difference in heights of left and right subtrees)
    int dif(node *temp);
    // Method to calculate the height of a node in the tree
    int height(node *temp);
    // Utility method to return the maximum of two values
    int maximum(int a, int b);
    // Rotations to balance the tree (LL, RR, LR, RL)
    node* LL(node *par);
    node* RR(node *par);
    node* LR(node *par);
    node* RL(node *par);
    // In-order traversal of the tree for ascending order display
    void ascending(node *temp);
    // Method to delete a node by keyword
    node* delete_n(node *root, string key1);
    // Method to delete a keyword from the tree
    void deleten();
    // Method to extract the minimum value node from the tree
    node* extractmin(node *t);
    // Reverse in-order traversal for descending order display
    void descending(node *temp);
    // Method to display the tree in both ascending and descending order
    void display();
    // Method to search a keyword in the AVL tree
    bool search(node *cur, string key1);
    // Method to interactively search for a keyword
    void search_value();
};

// Method to create and populate the AVL tree by repeatedly asking the user to input keywords
void AVL::create() {
    char answer;
    node *temp;
    do {
        temp = new node();  // Create a new node
        cout << "\n Enter the keyword: ";
        cin >> temp->key;  // Input keyword
        cout << " Enter the meaning: ";
        cin >> temp->meaning;  // Input meaning
        temp->left = temp->right = NULL;  // Initialize left and right pointers as NULL
        root = insert(root, temp);  // Insert the new node into the tree
        cout << "\n Do you want to add another word? (y/n): ";
        cin >> answer;  // Ask if the user wants to add another keyword
    } while (answer == 'y' || answer == 'Y');  // Repeat if 'y' or 'Y' is entered
}

// Method to insert a new node into the AVL tree and ensure the tree is balanced
node* AVL::insert(node *cur, node *temp) {
    if (cur == NULL) {
        return temp;  // If the current node is NULL, insert the new node
    }
    if (temp->key < cur->key) {
        cur->left = insert(cur->left, temp);  // Insert in left subtree if key is smaller
        cur = balance(cur);  // Balance the tree after insertion
    } else if (temp->key > cur->key) {
        cur->right = insert(cur->right, temp);  // Insert in right subtree if key is greater
        cur = balance(cur);  // Balance the tree after insertion
    }
    return cur;  // Return the updated current node
}

// Method to balance the tree by checking balance factors and performing rotations
node* AVL::balance(node *temp) {
    int bal = dif(temp);  // Get balance factor of the node
    if (bal >= 2) {
        if (dif(temp->left) < 0)
            temp = LR(temp);  // Perform Left-Right rotation
        else
            temp = LL(temp);  // Perform Left-Left rotation
    } else if (bal <= -2) {
        if (dif(temp->right) > 0)
            temp = RL(temp);  // Perform Right-Left rotation
        else
            temp = RR(temp);  // Perform Right-Right rotation
    }
    return temp;  // Return the balanced node
}

// Method to calculate the balance factor of a node (difference between left and right subtree heights)
int AVL::dif(node *temp) {
    int l = height(temp->left);  // Get the height of left subtree
    int r = height(temp->right);  // Get the height of right subtree
    return (l - r);  // Return the balance factor
}

// Method to calculate the height of a node (maximum depth from that node)
int AVL::height(node *temp) {
    if (temp == NULL)
        return -1;  // Height of NULL node is -1
    else
        return (maximum(height(temp->left), height(temp->right)) + 1);  // Height is 1 + maximum height of left and right subtrees
}

// Utility method to return the maximum of two values
int AVL::maximum(int a, int b) {
    return (a > b) ? a : b;
}

// Left-Left rotation (used when left subtree is taller)
node* AVL::LL(node *par) {
    node *temp = par->left;
    par->left = temp->right;
    temp->right = par;
    return temp;  // Return new root of the subtree
}

// Right-Right rotation (used when right subtree is taller)
node* AVL::RR(node *par) {
    node *temp = par->right;
    par->right = temp->left;
    temp->left = par;
    return temp;  // Return new root of the subtree
}

// Left-Right rotation (used when left subtree is taller and right child is also tall)
node* AVL::LR(node *par) {
    par->left = RR(par->left);  // Perform Right-Right rotation on left child
    return LL(par);  // Perform Left-Left rotation on the parent
}

// Right-Left rotation (used when right subtree is taller and left child is also tall)
node* AVL::RL(node *par) {
    par->right = LL(par->right);  // Perform Left-Left rotation on right child
    return RR(par);  // Perform Right-Right rotation on the parent
}

// In-order traversal for ascending order display
void AVL::ascending(node *temp) {
    if (temp != NULL) {
        ascending(temp->left);  // Traverse the left subtree
        cout << "\n\t" << temp->key << " : " << temp->meaning;  // Display the node
        ascending(temp->right);  // Traverse the right subtree
    }
}

// Reverse in-order traversal for descending order display
void AVL::descending(node *temp) {
    if (temp != NULL) {
        descending(temp->right);  // Traverse the right subtree
        cout << "\n\t" << temp->key << " : " << temp->meaning;  // Display the node
        descending(temp->left);  // Traverse the left subtree
    }
}

// Method to display the AVL tree in both ascending and descending order
void AVL::display() {
    cout << "\n The keywords in ascending order are :\n";
    ascending(root);  // Display keywords in ascending order
    cout << "\n\n The keywords in descending order are :\n";
    descending(root);  // Display keywords in descending order
}

// Method to search for a keyword in the AVL tree
bool AVL::search(node *cur, string key1) {
    if (cur) {
        if (cur->key == key1)
            return true;  // Return true if the keyword is found
        if (key1 < cur->key)
            return search(cur->left, key1);  // Search in the left subtree if key is smaller
        else
            return search(cur->right, key1);  // Search in the right subtree if key is larger
    }
    return false;  // Return false if keyword is not found
}

// Method to interactively search for a keyword
void AVL::search_value() {
    string key2;
    cout << "\n Enter the keyword you wish to search : ";
    cin >> key2;  // Input the keyword to search
    if (search(root, key2))
        cout << "\n The entered keyword is present in the AVL tree";
    else
        cout << "\n The entered keyword is not present in the AVL tree";
}

// Method to delete a keyword from the AVL tree
node* AVL::delete_n(node* cur, string key1) {
    if (!cur)
        return cur;  // If the node is NULL, return NULL
    if (key1 < cur->key)
        cur->left = delete_n(cur->left, key1);  // Recurse to the left if key is smaller
    else if (key1 > cur->key)
        cur->right = delete_n(cur->right, key1);  // Recurse to the right if key is larger
    else {  // If the node is found
        node *l = cur->left;
        node *r = cur->right;
        delete cur;  // Delete the node
        if (!r)
            return l;  // If no right child, return the left child
        node *m = r;
        while (m->left)  // Find the minimum node in the right subtree
            m = m->left;
        m->right = extractmin(r);  // Extract the minimum node and fix right subtree
        m->left = l;  // Attach the left child
        return balance(m);  // Balance the tree after deletion
    }
    return balance(cur);  // Return the balanced current node
}

// Method to extract the minimum value node from the right subtree
node* AVL::extractmin(node *t) {
    if (!t->left)
        return t->right;  // If no left child, return the right child
    t->left = extractmin(t->left);  // Recurse to the left subtree
    return balance(t);  // Balance the node after modification
}

// Method to delete a keyword from the AVL tree interactively
void AVL::deleten() {
    string key;
    cout << "\n Enter the keyword to be deleted : ";
    cin >> key;  // Input the keyword to delete
    root = delete_n(root, key);  // Call the delete function
}

// Main function to interact with the user and manage the AVL tree operations
int main() {
    char c;
    int ch;
    AVL a;  // Create an AVL tree object
    do {
        // Display the menu for the user
        cout << "*********************************";
        cout << "\n 1.Insert a keyword in AVL tree.";
        cout << "\n 2.Display the AVL tree.";
        cout << "\n 3.Search a keyword";
        cout << "\n 4.Delete a keyword.";
        cout << "\n Enter your choice : ";
        cin >> ch;  // Input user's choice
        switch (ch) {
            case 1: a.create();  // Call create method to insert a keyword
                break;
            case 2: a.display();  // Display the AVL tree
                break;
            case 3: a.search_value();  // Search for a keyword
                break;
            case 4: a.deleten();  // Delete a keyword
                break;
            default: cout << "\n Wrong choice ! ";  // Handle invalid input
        }
        cout << "\n Do you want to continue? (y/n): ";
        cin >> c;  // Ask the user if they want to continue
    } while (c == 'y' || c == 'Y');  // Repeat if 'y' or 'Y' is entered
    return 0;
}
