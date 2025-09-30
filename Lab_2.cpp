// Lab 2

// ADD HEADER FILES HERE
#include <iostream>
#include <string>
using namespace std;

// -----------------------------
// Data Model
// -----------------------------
struct User {
    string username;
    string password;
    string role;
    User *next;
    
    User(string u, string p, const string &r = "viewer") {
        username = u;
        password = p;
        role = r;
        next = nullptr;
    }
};

// Function prototypes:
bool insertUser(User *&head, const string &username, const string &password, const string &role = "viewer");
User* findUser(User *head, const string &username);
void printUsers(User* head);
bool authorize(User* head, const string& username, const string& action);

int main() {
  
    // Write code here to test your implementation
    
    return 0;
}

// -----------------------------
// Core API — implement these
// -----------------------------

// Inserts a new (username, password) at the END of the list.
// If username already exists, do NOT insert a duplicate; return false.
// Otherwise insert and return true.
bool insertUser(User *&head, const string &username, const string &password, const string &role = "viewer") {
    // TODO: implement
    
    User *curr = head;

    // Checks for duplicates.
    while (curr != nullptr) {
        if (curr->username == username) {
            return false;
        }
        curr = curr->next;
    }

    // Creates a new user node.
    User *newUser = new User(username, password, role);

    // Places new user node at the front (if list is empty) or at the end (if list already has nodes).
    if (head == nullptr) {
        head = newUser;
    } else {
        curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newUser;
    }

    return true;
}

// Returns pointer to the node with matching username; otherwise nullptr.
User *findUser(User *head, const string &username) {
    // TODO: implement

    User *curr = head;

    while (curr != nullptr) {
        if (curr->username == username) {
            return curr;    // Found the user so we return pointer pointing to node.
        }
        curr = curr->next;
    }
    
    return nullptr;
}

// Prints usernames in order, separated by " -> " then " -> NULL".
// Example: alice -> bob -> charlie -> NULL
void printUsers(User *head) {
    // TODO: implement

    User *curr = head;
    while (curr != nullptr) {
        cout << curr->username << " -> ";
        curr = curr->next;
    }
    
    cout << "NULL" << endl;
}

bool authorize(User* head, const string& username, const string& action) {
    User* user = findUser(head, username);
    if (user == nullptr) {
        return false;
    }

    if (user->role == "admin") {
        return true;
    } 
    else if (user->role == "editor") {
        if (action == "view" || action == "edit" || action == "create") {
            return true;
        } else {
            return false;
        }
    } 
    else if (user->role == "viewer") {
        if (action == "view") {
            return true;
        } else {
            return false;
        }
    } 

    return false;
}