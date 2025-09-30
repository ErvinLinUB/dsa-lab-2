// Lab 1: Singly Linked List for Username/Password storage

// Goal: Implement a simple credential store using a singly linked list

// Instructions:
// 1) Search for "TODO" and implement each function.
// 2) Build & run:   g++ -std=c++17 -O2 -Wall linked_lists.cpp -o lab && ./lab
// 3) Do not change function signatures

// NOTE: In the real world, NEVER store plaintext passwords.


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
    User* next;
    
    User(string u, string p) {
        username = u;
        password = p;
        next = nullptr;
    }
};

// Function prototypes:
bool insertUser(User *&head, const string &username, const string &password);
User* findUser(User *head, const string &username);
bool authenticate(User *head, const string &username, const string &password);
bool removeFront(User *&head);
bool removeByUsername(User *&head, const string& username);
void clearList(User*& head);
size_t size(User* head);
void printUsers(User* head);

int main() {
  
    // Write code here to test your implementation
    
    User* head = nullptr; // start with empty list

    cout << "Inerting users:" << endl;
    cout << (insertUser(head, "Alice", "123") ? "Inserted Alice" : "Failed to insert Alice") << endl;
    cout << (insertUser(head, "John", "123") ? "Inserted John" : "Failed to insert John") << endl;
    cout << (insertUser(head, "Charles", "123") ? "Inserted Charles" : "Failed to insert Charles") << endl;
    cout << (insertUser(head, "Alice", "123") ? "Inserted Alice duplicate" : "Duplicate rejected") << endl;

    cout << endl;

    cout << "Print users:" << endl;
    printUsers(head);
    cout << "Number of nodes: " << size(head) << endl;

    cout << endl;

    cout << "Finding users:" << endl;
    User* u1 = findUser(head, "Alice");
    if (u1) cout << "Found user: " << u1->username << endl;
    User* u2 = findUser(head, "David");
    if (!u2) cout << "The user 'David' was not found." << endl;

    cout << endl;

    cout << "Authentication:" << endl;
    cout << "Login Alice - Password: 123: " 
         << (authenticate(head, "Alice", "123") ? "Success" : "Fail") << endl;
    cout << "Login Alice - Password: 321: " 
         << (authenticate(head, "Alice", "321") ? "Success" : "Fail") << endl;

    cout << endl;

    cout << "Remove front:" << endl;
    if (removeFront(head)) cout << "Front user removed." << endl;
    printUsers(head);
    cout << "Number of nodes: " << size(head) << endl;

    cout << endl;

    cout << "Remove by username:" << endl;
    if (removeByUsername(head, "Charles")) 
        cout << "Removed 'Charles' successfully." << endl;
    else 
        cout << "Could not remove 'Charles'." << endl;
    printUsers(head);
    cout << "Number of nodes: " << size(head) << endl;

    cout << endl;

    cout << "Clear list:" << endl;
    clearList(head);
    printUsers(head); // should just show NULL
    cout << "Number of nodes: " << size(head) << endl;
    
    return 0;
}

// -----------------------------
// Core API — implement these
// -----------------------------

// Inserts a new (username, password) at the END of the list.
// If username already exists, do NOT insert a duplicate; return false.
// Otherwise insert and return true.
bool insertUser(User*& head, const string& username, const string& password) {
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
    User *newUser = new User(username, password);

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
User* findUser(User* head, const string& username) {
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

// Returns true if (username, password) matches an existing node; false otherwise.
bool authenticate(User* head, const string& username, const string& password) {
    // TODO: implement
   
    User *curr = head;

    while (curr != nullptr) {
        if (curr->username == username && curr->password == password) {
            return true;
        }
        curr = curr->next;
    }

    return false;
}

// Deletes the FIRST node (head) and updates head. No-op if list is empty.
// Return true if a node was deleted, false otherwise.
bool removeFront(User*& head) {
    // TODO: implement
    
    if (head == nullptr) {
        return false;
    }

    // Removes the first node.
    User *temp = head;
    head = head->next;
    delete temp;
    return true;
}

// Deletes the node with matching username (first match only).
// Return true if a node was found & deleted; false if not found.
bool removeByUsername(User*& head, const string& username) {
    // TODO: implement
    
    if (head == nullptr) {
        return false;
    }

    // If the head node matches the username, delete.
    if (head->username == username) {
        User *temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    // Searching for the node to remove
    User *curr = head;

    while (curr->next != nullptr) {
        if (curr->next->username == username) {
            User *temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
            return true;
        }
        curr = curr->next;
    }

    return false;
}

// Deletes ALL nodes and sets head=nullptr. 
void clearList(User*& head) {
    // TODO: implement
    
    while (head != nullptr) {
        User *temp= head;
        head = head->next;
        delete temp;
    }
}

// Returns number of nodes.
size_t size(User* head) {
    // TODO: implement

    size_t count = 0;

    User *curr = head;
    while (curr != nullptr) {
        count++;
        curr = curr->next;
    }
    
    return count;
}

// Prints usernames in order, separated by " -> " then " -> NULL".
// Example: alice -> bob -> charlie -> NULL
void printUsers(User* head) {
    // TODO: implement
    
    User *curr = head;
    while (curr != nullptr) {
        cout << curr->username << " -> ";
        curr = curr->next;
    }
    
    cout << "NULL" << endl;
}


