// Lab 2

// ADD HEADER FILES HERE
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// -----------------------------
// Data Model
// -----------------------------
struct User {
    string username;
    string password;
    vector<string> permissions;
    User *next;
    
    User(string u, string p, const vector<string> &perms = {"view"}) {
        username = u;
        password = p;
        permissions = perms;
        next = nullptr;
    }
};

// Function prototypes:
bool insertUser(User *&head, const string &username, const string &password, const vector<string> &permissions = {"view"});
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
bool insertUser(User *&head, const string &username, const string &password, const vector<string> &permissions) {
    User *curr = head;

    // Checks for duplicates
    while (curr != nullptr) {
        if (curr->username == username) {
            return false;
        }
        curr = curr->next;
    }

    // Create new user with permissions
    User *newUser = new User(username, password, permissions);

    // Insert at head if empty, else append at end
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

    for (const string& perm : user->permissions) {
        if (perm == action) {
            return true;
        }
    }

    return false;
}