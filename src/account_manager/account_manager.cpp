/**
 * @file account_manager.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Account Manager class definition
 * @date 05/02/2025
 *
 */

#include "account_manager.hpp"
#include <iostream>
#include <memory>
#include <string>

// TODO: create class for DatabaseManager to have just the dateBase to do there

AccountManager::AccountManager(shared_ptr<DatabaseManager> &db) : dbManager_(db) {}

bool AccountManager::createAccount(const string &username,
                                   const string &password) {    
    // Check if the username already exist
    if (dbManager_->userExists(username)) {
        cerr << "Error: User '" << username << "' already exist." << endl;
        return false;
    }
  
    return dbManager_->addUser(username, password);
}

bool AccountManager::login(const string &username, const string &password) {
    return dbManager_->checkUserPassword(username, password);
}

void AccountManager::launch() {
    cout << "Do you want to create an account? (y/n): ";
    char choice;
    cin >> choice;
    choice = tolower(choice);

    while (choice != 'y' && choice != 'n') {
        cout << "Invalid choice! Please enter 'y' or 'n': ";
        cin >> choice;
        choice = tolower(choice);
    }

    string username, password;

    if (choice == 'y') {
        cout << "An account will be created." << endl;
        cout << "Enter a username: ";
        cin >> username;
        cout << "Enter a password: ";
        cin >> password;

        while (!createAccount(username, password)) {
            cout << "Enter a username: ";
            cin >> username;
            cout << "Enter a password: ";
            cin >> password;
        }
            
        cout << "Account created!" << endl;
    }


    cout << "You will have to login." << endl;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    while (!login(username, password)) {
        cout << "Login failed! Please try again." << endl;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
    }

    cout << "Login successful!" << endl;
}