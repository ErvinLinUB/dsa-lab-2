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
    User* head = nullptr;

    // Insert users with role-based permissions
    insertUser(head, "Alice", "123"); // default viewer: {"view"}
    insertUser(head, "John", "123", {"view", "edit", "create"}); // editor
    insertUser(head, "Charles", "123", {"view", "edit", "create", "delete"}); // admin

    // Print all users
    cout << "Users in list:" << endl;
    printUsers(head);
    cout << endl;

    // Authorization tests
    cout << boolalpha; // print true/false instead of 1/0

    cout << "Alice (viewer)" << endl;
    cout << "Alice can view? " << authorize(head, "Alice", "view") << endl;
    cout << "Alice can edit? " << authorize(head, "Alice", "edit") << endl;

    cout << endl;

    cout << "John (editor)" << endl;
    cout << "John can create? " << authorize(head, "John", "create") << endl;
    cout << "John can delete? " << authorize(head, "John", "delete") << endl;

    cout << endl;

    cout << "Charles (admin)" << endl;
    cout << "Charles can edit? " << authorize(head, "Charles", "edit") << endl;
    cout << "Charles can delete? " << authorize(head, "Charles", "delete") << endl;

    cout << endl;

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