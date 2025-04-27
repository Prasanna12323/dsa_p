#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

// Structure to represent each dictionary entry
struct Node {
    string key, meaning;  // Key and meaning for each dictionary entry
    Node *left, *right;   // Pointers for left and right children
    Node(string k, string m) : key(k), meaning(m), left(nullptr), right(nullptr) {}  // Constructor
};

class Dictionary {
    Node* root = nullptr;  // Root of the binary search tree (BST)

    // Helper function to insert a new node into the BST
    Node* insert(Node* n, string k, string m) {
        if (!n) return new Node(k, m);  // If the current node is null, create a new node
        if (k < n->key) n->left = insert(n->left, k, m);  // Insert to the left if key is smaller
        else if (k > n->key) n->right = insert(n->right, k, m);  // Insert to the right if key is larger
        else cout << "Keyword exists. Use update.\n";  // If key already exists, prompt for update
        return n;
    }

    // Helper function to find the node with the minimum value (leftmost node)
    Node* findMin(Node* n) { return n->left ? findMin(n->left) : n; }

    // Helper function to delete a node from the BST
    Node* del(Node* n, string k) {
        if (!n) return nullptr;  // If the node is null, return null
        if (k < n->key) n->left = del(n->left, k);  // Recursively search in left subtree
        else if (k > n->key) n->right = del(n->right, k);  // Recursively search in right subtree
        else {
            if (!n->left) return exchange(n, n->right), delete n, n;  // If no left child, replace with right child
            if (!n->right) return exchange(n, n->left), delete n, n;  // If no right child, replace with left child
            Node* t = findMin(n->right);  // Find the smallest node in the right subtree
            n->key = t->key; n->meaning = t->meaning;  // Replace current node's data with smallest node's data
            n->right = del(n->right, t->key);  // Delete the smallest node from the right subtree
        }
        return n;
    }

    // Helper function for in-order traversal (for displaying the dictionary)
    void inOrder(Node* n, bool rev) {
        if (!n) return;  // If node is null, return
        inOrder(rev ? n->right : n->left, rev);  // Traverse the right or left subtree based on reverse flag
        cout << n->key << " : " << n->meaning << endl;  // Print the key and meaning
        inOrder(rev ? n->left : n->right, rev);  // Traverse the left or right subtree
    }

    // Helper function to search for a key in the dictionary
    bool search(Node* n, string k, int& cmp) {
        while (n) {
            cmp++;  // Increment comparisons
            if (k == n->key) return cout << "Found: " << n->key << " = " << n->meaning << endl, true;
            n = k < n->key ? n->left : n->right;  // Move left or right depending on the key comparison
        }
        return cout << "Not found.\n", false;  // If key is not found
    }

    // Helper function to update the meaning of an existing key
    bool update(Node* n, string k, string m) {
        while (n) {
            if (k == n->key) return n->meaning = m, true;  // Update the meaning if key matches
            n = k < n->key ? n->left : n->right;  // Move left or right depending on the key comparison
        }
        return false;  // If key is not found
    }

    // Helper function to calculate the height of the tree
    int height(Node* n) {
        return n ? 1 + max(height(n->left), height(n->right)) : 0;  // Return 0 for null, otherwise 1 + max of left/right height
    }

public:
    // Public methods for dictionary operations
    void add(string k, string m) { root = insert(root, k, m); }  // Add a new key-meaning pair
    void remove(string k) { root = del(root, k); }  // Remove a key-meaning pair
    void update(string k, string m) { cout << (update(root, k, m) ? "Updated.\n" : "Not found.\n"); }  // Update the meaning of a key
    void find(string k) {
        int cmp = 0;
        search(root, k, cmp);  // Search for a key and count comparisons
        cout << "Comparisons: " << cmp << endl;  // Display the number of comparisons made
    }
    void display(bool asc) { inOrder(root, !asc); }  // Display the dictionary in ascending or descending order
    void maxComp() { cout << "Max comparisons (height): " << height(root) << endl; }  // Display the maximum number of comparisons (tree height)
};

int main() {
    Dictionary d;  // Create a dictionary object
    int c; string k, m;
    do {
        cout << "\n1.Add 2.Delete 3.Update 4.Display Asc 5.Display Desc 6.Find 7.MaxComp 8.Exit\nChoice: ";
        cin >> c; cin.ignore();  // Menu to choose the operation
        switch (c) {
            case 1: cout << "Keyword: "; getline(cin, k); cout << "Meaning: "; getline(cin, m); d.add(k, m); break;
            case 2: cout << "Delete: "; getline(cin, k); d.remove(k); break;
            case 3: cout << "Update key: "; getline(cin, k); cout << "New meaning: "; getline(cin, m); d.update(k, m); break;
            case 4: d.display(true); break;  // Display dictionary in ascending order
            case 5: d.display(false); break;  // Display dictionary in descending order
            case 6: cout << "Find: "; getline(cin, k); d.find(k); break;  // Find a key
            case 7: d.maxComp(); break;  // Display maximum comparisons (tree height)
        }
    } while (c != 8);  // Exit if choice is 8
}
