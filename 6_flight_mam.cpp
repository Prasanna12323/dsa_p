#include<iostream>
#include<string.h>
using namespace std;

class flight {
public:
    int am[10][10];  // Adjacency matrix for storing distances between cities
    char city_index[10][10];  // Array for storing city names

    flight();  // Constructor declaration
    int create();  // Function to create the flight network (add cities and distances)
    void display(int city_count);  // Function to display the adjacency matrix
};

// Constructor to initialize the city names to "xx" and the adjacency matrix to 0
flight::flight() {
    int i, j;
    for(i = 0; i < 10; i++) {
        strcpy(city_index[i], "xx");  // Initialize city names as "xx"
    }
    for(i = 0; i < 10; i++) {
        for(j = 0; j < 10; j++) {
            am[i][j] = 0;  // Initialize adjacency matrix with 0 (no connections)
        }
    }
}

// Function to create the flight network
int flight::create() {
    int city_count = 0, j, si, di, wt;
    char s[10], d[10], c;
    do {
        cout << "\n\tEnter Source City: ";
        cin >> s;  // Input source city
        cout << "\n\tEnter Destination City: ";
        cin >> d;  // Input destination city

        // Check if source city already exists
        for(j = 0; j < 10; j++) {
            if(strcmp(city_index[j], s) == 0) break;
        }
        if(j == 10) {
            strcpy(city_index[city_count], s);  // Add new city if not found
            city_count++;
        }

        // Check if destination city already exists
        for(j = 0; j < 10; j++) {
            if(strcmp(city_index[j], d) == 0) break;
        }
        if(j == 10) {
            strcpy(city_index[city_count], d);  // Add new city if not found
            city_count++;
        }

        // Input the distance between the source and destination cities
        cout << "\n\tEnter Distance From " << s << " And " << d << ": ";
        cin >> wt;  // Distance between cities

        // Find the indices of the source and destination cities
        for(j = 0; j < 10; j++) {
            if(strcmp(city_index[j], s) == 0) si = j;  // Index of source city
            if(strcmp(city_index[j], d) == 0) di = j;  // Index of destination city
        }

        am[si][di] = wt;  // Set the distance in the adjacency matrix

        // Ask if the user wants to add more cities
        cout << "\n\tDo you want to add more cities.....(y/n): ";
        cin >> c;
    } while(c == 'y' || c == 'Y');  // Repeat if the user wants to add more cities

    return(city_count);  // Return the total number of cities
}

// Function to display the adjacency matrix
void flight::display(int city_count) {
    int i, j;
    cout << "\n\tDisplaying Adjacency Matrix:\n\t";

    // Display city names in the header row
    for(i = 0; i < city_count; i++)
        cout << "\t" << city_index[i];
    cout << "\n";

    // Display the adjacency matrix with distances between cities
    for(i = 0; i < city_count; i++) {
        cout << "\t" << city_index[i];  // Print city name in the first column
        for(j = 0; j < city_count; j++) {
            cout << "\t" << am[i][j];  // Print the distance between cities
        }
        cout << "\n";
    }
}

int main() {
    flight f;  // Create a flight object
    int n, city_count;
    char c;
    
    do {
        cout << "\n\t*** Flight Main Menu *****";
        cout << "\n\t1. Create \n\t2. Adjacency Matrix\n\t3. Exit";
        cout << "\n\t.....Enter your choice: ";
        cin >> n;  // User chooses an option from the menu

        switch(n) {
            case 1:
                city_count = f.create();  // Create the flight network
                break;
            case 2:
                f.display(city_count);  // Display the adjacency matrix
                break;
            case 3:
                return 0;  // Exit the program
        }

        // Ask if the user wants to continue in the main menu
        cout << "\n\tDo you Want to Continue in Main Menu....(y/n): ";
        cin >> c;
    } while(c == 'y' || c == 'Y');  // Repeat if the user wants to continue

    return 0;  // Exit the program
}
