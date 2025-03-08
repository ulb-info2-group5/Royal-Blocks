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
AccountManager::AccountManager(std::shared_ptr<DatabaseManager> &db)
    : dbManager_(db) {
    // Create the table of users if it doesn't exist
    dbManager_->createTables("CREATE TABLE IF NOT EXISTS users ("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                             "username TEXT NOT NULL, "
                             "password TEXT NOT NULL, "
                             "score INTEGER DEFAULT 0)");
}

// ### Private methods ###

// ### Public methods ###
CreateAccountStatus AccountManager::createAccount(const std::string &username,
                                                  const std::string &password) {
    CreateAccountStatus res = CreateAccountStatus::SUCCESS;

    if (checkUsernameExists(username)) {
        std::cerr << "Error: User '" << username << "' already exist."
                  << std::endl;
        res = CreateAccountStatus::USERNAME_EXISTS;
        return res;
    }

    if (!dbManager_->executeSqlChangeData(
            "INSERT INTO users (username, password) VALUES (?, ?)",
            {username, password})) { // if the query fails
        res = CreateAccountStatus::FAILED;
        return res;
    };

    return res;
}

bool AccountManager::deleteAccount(const int userId) {
    if (dbManager_->findUserInDatabase("friends", userId)) {
        // Delete all the friendships of the user
        if (!dbManager_->executeSqlChangeData(
                "DELETE FROM friends WHERE user1 = ? OR user2 = ?",
                {userId, userId})) {
            std::cerr << "Error: Failed to delete friends of user '" << userId
                      << "'." << std::endl;
            return false;
        }
    }

    return dbManager_->executeSqlChangeData("DELETE FROM users WHERE id = ?",
                                            {userId});
}

bool AccountManager::checkUserPassword(const std::string &username,
                                       const std::string &password) const {
    std::string sql =
        "SELECT COUNT(*) FROM users WHERE username = ? AND password = ?";
    int count = 0;
    return dbManager_->executeSqlRecoveryInt(sql, {username, password}, count)
           && count > 0;
}

bool AccountManager::checkUsernameExists(const std::string &username) const {
    std::string query = "SELECT COUNT(*) FROM users WHERE username = ?";
    int count = 0;
    return dbManager_->executeSqlRecoveryInt(query, {username}, count)
           && count > 0;
}

bool AccountManager::login(const std::string &username,
                           const std::string &password) const {
    return checkUserPassword(username, password);
}

void AccountManager::launch() {
    using namespace std;

    // ### Part 1: Create an account ###
    std::cout << "Do you want to create an account? (y/n): ";
    char choice;
    cin >> choice;
    choice = tolower(choice);

    while (choice != 'y' && choice != 'n') {
        cout << "Invalid choice! Please enter 'y' or 'n': ";
        cin >> choice;
        choice = tolower(choice);
    }

    std::string username, password;

    if (choice == 'y') {
        cout << "An account will be created." << endl;
        cout << "Enter a username: ";
        cin >> username;
        cout << "Enter a password: ";
        cin >> password;

        while (createAccount(username, password)
               != CreateAccountStatus::SUCCESS) {
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
    dbManager_->executeSqlChangeData(
        "UPDATE users SET score = MAX(score, ?) WHERE id = ?",
        {newScore, userId});
}

int AccountManager::getUserId(const std::string &username) const {
    std::string sql = "SELECT id FROM users WHERE username = ?";
    int userId = -1;
    dbManager_->executeSqlRecoveryInt(sql, {username}, userId);
    if (userId == -1) {
        std::cerr << "Error: User '" << username << "' does not exist."
                  << std::endl;
    }
    return userId;
}

std::string AccountManager::getUsername(const int userId) const {
    std::string sql = "SELECT username FROM users WHERE id = ?";
    std::string username;
    dbManager_->executeSqlRecoveryString(sql, {userId}, username);
    return username;
}
