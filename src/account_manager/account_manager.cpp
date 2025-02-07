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
AccountManager::AccountManager(shared_ptr<DatabaseManager> &db) : dbManager_(db) {
    // Create the table of users if it doesn't exist
    dbManager_->createTables("CREATE TABLE IF NOT EXISTS users ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "username TEXT NOT NULL, "
                        "password TEXT NOT NULL, "
                        "score INTEGER DEFAULT 0)");
}

// ### Private methods ###
bool AccountManager::checkUsernameExists(const string &username) const {
    string query = "SELECT COUNT(*) FROM users WHERE username = ?";
    int count = 0;
    return dbManager_->executeSqlRecoveryInt(query, {username}, count) && count > 0;
}

bool AccountManager::checkUserPassword(const string &username, const string &password) const {
    string sql = "SELECT COUNT(*) FROM users WHERE username = ? AND password = ?";
    int count = 0;
    return dbManager_->executeSqlRecoveryInt(sql, {username, password}, count) && count > 0;
}


// ### Public methods ###
bool AccountManager::createAccount(const string &username,
                                   const string &password) {    
    if (checkUsernameExists(username)) {
        cerr << "Error: User '" << username << "' already exist." << endl;
        return false;
    }
    return dbManager_->executeSqlChangeData("INSERT INTO users (username, password) VALUES (?, ?)", {username, password});
}

bool AccountManager::deleteAccount(const int userId) {
    // Delete all the friendships of the user
    if (!dbManager_->executeSqlChangeData("DELETE FROM friends WHERE user1 = ? OR user2 = ?", {userId, userId})) {
        cerr << "Error: Failed to delete friends of user '" << userId << "'." << endl;
        return false;
    }
    return dbManager_->executeSqlChangeData("DELETE FROM users WHERE id = ?", {userId});
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

void AccountManager::updateScore(const int userId, const int newScore) { 
    dbManager_->executeSqlChangeData("UPDATE users SET score = MAX(score, ?) WHERE id = ?", {newScore, userId});
}

int AccountManager::getUserId(const string &username) const {
    string sql = "SELECT id FROM users WHERE username = ?";
    int userId = -1;
    dbManager_->executeSqlRecoveryInt(sql, {username}, userId);
    if (userId == -1) {
        cerr << "Error: User '" << username << "' does not exist." << endl;
    }
    return userId;
}

string AccountManager::getUsername(const int userId) const {
    string sql = "SELECT username FROM users WHERE id = ?";
    string username;
    dbManager_->executeSqlRecoveryString(sql, {userId}, username);
    return username;
}