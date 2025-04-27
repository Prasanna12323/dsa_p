#include <iostream>
using namespace std;

const int MAX = 20;  // Define the maximum number of keys (adjustable as needed)

// Function to calculate the minimum cost of constructing an optimal Binary Search Tree (BST)
void optimalBST(double p[], int n) {
    // Arrays to store the cost and root of the optimal subtree
    double cost[MAX][MAX] = {0};  // cost[i][j] holds the minimum cost for keys i to j
    int root[MAX][MAX] = {0};  // root[i][j] holds the root of the optimal BST for keys i to j

    // Initial cost setup for single key subtrees (diagonal elements of the matrix)
    for (int i = 0; i < n; i++) {
        cost[i][i] = p[i];  // The cost for a single key is its access probability
        root[i][i] = i;  // The root of a single key tree is the key itself
    }

    // l is the chain length of the subtrees (start from 2 keys up to n keys)
    for (int l = 2; l <= n; l++) {  // For each subtree length from 2 to n
        for (int i = 0; i <= n - l; i++) {  // i is the starting index of the subtree
            int j = i + l - 1;  // j is the ending index of the subtree
            cost[i][j] = 999999; // Initialize with a very large number (infinity substitute)

            // Sum of access probabilities for the current subtree (keys i to j)
            double sum = 0;
            for (int s = i; s <= j; s++) {
                sum += p[s];  // Sum all the probabilities from i to j
            }

            // Try all possible roots within the subtree
            for (int r = i; r <= j; r++) {
                double c = 0;

                // Cost for left subtree (if r > i, check the left part of the subtree)
                if (r > i) c += cost[i][r - 1];
                // Cost for right subtree (if r < j, check the right part of the subtree)
                if (r < j) c += cost[r + 1][j];
                c += sum;  // Add the sum of probabilities for the current subtree

                // Update the cost and root if we find a lower cost
                if (c < cost[i][j]) {
                    cost[i][j] = c;  // Update the minimum cost for the current subtree
                    root[i][j] = r;  // Store the root of the optimal BST for keys i to j
                }
            }
        }
    }

    // Print the minimum cost of the optimal BST
    cout << "\nMinimum cost of Optimal BST: " << cost[0][n - 1] << endl;
}

int main() {
    int n;  // Number of keys
    double p[MAX];  // Array to store the access probabilities of the keys

    cout << "Enter number of keys: ";
    cin >> n;  // Input the number of keys

    cout << "Enter access probabilities (sorted keys):\n";
    for (int i = 0; i < n; i++) {
        cout << "p[" << i + 1 << "]: ";
        cin >> p[i];  // Input the access probabilities for each key
    }

    optimalBST(p, n);  // Call the optimalBST function to calculate the minimum cost

    return 0;  // Return 0 to indicate successful execution
}
