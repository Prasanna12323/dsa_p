#include<iostream>
using namespace std;

class tree {
    int a[20][20], l, u, w, i, j, v, e, visited[20];  // Declare variables for the adjacency matrix, visited array, and graph properties
public:
    void input();   // Function to input graph details
    void display(); // Function to display the adjacency matrix
    void minimum(); // Function to find the minimum spanning tree using Prim's Algorithm
};

void tree::input() {
    // Input the number of branches (vertices)
    cout << "Enter the no. of branches: ";
    cin >> v;

    // Initialize visited array and adjacency matrix
    for(i = 0; i < v; i++) {
        visited[i] = 0;  // Mark all nodes as unvisited
        for(j = 0; j < v; j++) {
            a[i][j] = 999; // Set initial value to a large number (infinity) to indicate no connection
        }
    }

    // Input the number of connections (edges)
    cout << "\nEnter the no. of connections: ";
    cin >> e;

    // Input the details of each connection (edges with weights)
    for(i = 0; i < e; i++) {
        cout << "Enter the end branches of connections: " << endl;
        cin >> l >> u;  // Input the connected vertices
        cout << "Enter the phone company charges for this connection: ";
        cin >> w;  // Input the weight (cost) of the connection
        a[l-1][u-1] = a[u-1][l-1] = w;  // Set the weight for both directions (undirected graph)
    }
}

void tree::display() {
    // Display the adjacency matrix
    cout << "\nAdjacency matrix:";
    for(i = 0; i < v; i++) {
        cout << endl;
        for(j = 0; j < v; j++) {
            cout << a[i][j] << " ";  // Print the weight of each connection
        }
        cout << endl;
    }
}

void tree::minimum() {
    int p = 0, q = 0, total = 0, min;

    // Mark the first vertex as visited
    visited[0] = 1;

    // Apply Prim's algorithm to find the minimum spanning tree
    for(int count = 0; count < (v - 1); count++) {
        min = 999;  // Set initial minimum cost to a large value

        // Loop through all vertices to find the minimum edge
        for(i = 0; i < v; i++) {
            if(visited[i] == 1) {  // Check if vertex is already visited
                for(j = 0; j < v; j++) {
                    if(visited[j] != 1 && min > a[i][j]) {  // Find the smallest edge connecting visited and unvisited vertices
                        min = a[i][j];
                        p = i;
                        q = j;
                    }
                }
            }
        }

        // Mark the selected vertices as visited
        visited[p] = 1;
        visited[q] = 1;

        // Add the minimum cost to the total cost
        total = total + min;

        // Output the selected connection with the cost
        cout << "Minimum cost connection is " << (p + 1) << " -> " << (q + 1) << " with charge: " << min << endl;
    }

    // Output the total minimum cost for the spanning tree
    cout << "The minimum total cost of connections of all branches is: " << total << endl;
}

int main() {
    int ch;
    tree t;

    // Menu-driven interface
    do {
        cout << "==========PRIM'S ALGORITHM=================" << endl;
        cout << "\n1.INPUT\n \n2.DISPLAY\n \n3.MINIMUM\n" << endl;
        cout << "Enter your choice: " << endl;
        cin >> ch;

        // Switch case for user input
        switch(ch) {
            case 1:
                cout << "*******INPUT YOUR VALUES*******" << endl;
                t.input();  // Input the graph details
                break;

            case 2:
                cout << "*******DISPLAY THE CONTENTS********" << endl;
                t.display();  // Display the adjacency matrix
                break;

            case 3:
                cout << "*********MINIMUM************" << endl;
                t.minimum();  // Find and display the minimum spanning tree
                break;
        }
    } while(ch != 4);  // Exit the loop if the user chooses option 4
    return 0;
}
