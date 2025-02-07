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


// ### Constructor ###
AccountManager::AccountManager(shared_ptr<DatabaseManager> &db) : dbManager_(db) {}

// ### Private methods ###
bool AccountManager::checkUserExists(const string &username) const {
    string query = "SELECT COUNT(*) FROM users WHERE username = ?";
    int count = 0;
    return dbManager_->executeSqlRecovery(query, {username}, count) && count > 0;
}

bool AccountManager::checkUserPassword(const string &username, const string &password) const {
    string sql = "SELECT COUNT(*) FROM users WHERE username = ? AND password = ?";
    int count = 0;
    return dbManager_->executeSqlRecovery(sql, {username, password}, count) && count > 0;
}


// ### Public methods ###
bool AccountManager::createAccount(const string &username,
                                   const string &password) {    
    if (checkUserExists(username)) {
        cerr << "Error: User '" << username << "' already exist." << endl;
        return false;
    }
    return dbManager_->executeSqlChangeData("INSERT INTO users (username, password) VALUES (?, ?)", {username, password});
}

bool AccountManager::deleteAccount(const string &username) {
    if (!checkUserExists(username)) {
        cerr << "Error: User '" << username << "' does not exist." << endl;
        return false;
    }
    // Delete all the friendships of the user
    if (!dbManager_->executeSqlChangeData("DELETE FROM friends WHERE user1 = ? OR user2 = ?", {username, username})) {
        cerr << "Error: Failed to delete friends of user '" << username << "'." << endl;
        return false;
    }
    return dbManager_->executeSqlChangeData("DELETE FROM users WHERE username = ?", {username});
}

bool AccountManager::login(const string &username, const string &password) const {
    return checkUserPassword(username, password);
}

void AccountManager::launch() {
    // ### Part 1: Create an account ###
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

    // ### Part 2: Login ###
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

void AccountManager::updateScore(const string &username, const int newScore) { 
    dbManager_->executeSqlChangeData("UPDATE users SET score = MAX(score, ?) WHERE username = ?", {to_string(newScore), username});
}
