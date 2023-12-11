#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Struct to represent an item
struct Item {
    string name;
    int price;
    int quantity;
};

// Function to split a string based on a delimiter and return a vector of tokens
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    stringstream ss(s);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to join a vector of strings into a single string using a delimiter
string join(const vector<string>& tokens, char delimiter) {
    string result;
    for (size_t i = 0; i < tokens.size(); ++i) {
        result += tokens[i];
        if (i < tokens.size() - 1) {
            result += delimiter;
        }
    }
    return result;
}

// Function to create the data file
void createDataFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    // Add some sample data
    Item item1 = {"Apple", 100, 5};
    Item item2 = {"Banana", 50, 10};
    Item item3 = {"Orange", 75, 7};

    file << item1.name << ',' << item1.price << ',' << item1.quantity << endl;
    file << item2.name << ',' << item2.price << ',' << item2.quantity << endl;
    file << item3.name << ',' << item3.price << ',' << item3.quantity << endl;

    file.close();
    cout << "Data file created successfully!" << endl;
}

// Function to search for a specific item
void searchItem(const string& filename, const string& itemName) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        vector<string> data = split(line, ',');
        if (data[0] == itemName) {
            found = true;
            cout << "Item found!" << endl;
            cout << "Name: " << data[0] << endl;
            cout << "Price: " << data[1] << endl;
            cout << "Quantity: " << data[2] << endl;
            break;
        }
    }

    if (!found) {
        cout << "Item not found!" << endl;
    }

    file.close();
}

// Function to display all items
void displayItems(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    cout << "Items in the data file:" << endl;
    while (getline(file, line)) {
        vector<string> data = split(line, ',');
        cout << "Name: " << data[0] << endl;
        cout << "Price: " << data[1] << endl;
        cout << "Quantity: " << data[2] << endl << endl;
    }

    file.close();
}

// Function to update an item
void updateItem(const string& filename, const string& itemName) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    vector<string> items;
    while (getline(file, line)) {
        items.push_back(line);
    }

    file.close();

    bool found = false;
    for (size_t i = 0; i < items.size(); ++i) {
        vector<string> data = split(items[i], ',');
        if (data[0] == itemName) {
            found = true;

            // Get updated information
            cout << "Enter new name: ";
            cin >> data[0];
            cout << "Enter new price: ";
            cin >> data[1];
            cout << "Enter new quantity: ";
            cin >> data[2];

            items[i] = join(data, ',');
            break;
        }
    }

    if (!found) {
        cout << "Item not found!" << endl;
        return;
    }

    // Write updated data to the file
    ofstream outfile(filename);
    for (const string& item : items) {
        outfile << item << endl;
    }

    outfile.close();
    cout << "Item updated successfully" << endl;
}

int main() {
    const string filename = "items.txt";

    createDataFile(filename);

    int choice;
    string itemName;

    do {
        cout << "\nMenu:\n";
        cout << "1. Search for an item\n";
        cout << "2. Display all items\n";
        cout << "3. Update an item\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter item name to search: ";
                cin >> itemName;
                searchItem(filename, itemName);
                break;
            case 2:
                displayItems(filename);
                break;
            case 3:
                cout << "Enter item name to update: ";
                cin >> itemName;
                updateItem(filename, itemName);
                break;
            case 4:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 4);

    return 0;
}
