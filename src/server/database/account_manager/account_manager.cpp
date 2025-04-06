#include "account_manager.hpp"
#include <iostream>
#include <memory>
#include <string>

const std::string invalidChars = "!@#$%^&*()+=[]{}|\\\"'<>?/°;,~:²³§_£";

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
    if (username.length() < 4 || username.length() > 20) {
        std::cerr << "AccountManager error: Username must be between 4 and 20 characters."
                  << std::endl;
        return CreateAccountStatus::FAILED;
    }

    if (password.empty()) {
        std::cerr << "AccountManager error: Password cannot be empty." << std::endl;
        return CreateAccountStatus::FAILED;
    }


    for (const char c : username) {
        if (invalidChars.find(c) != std::string::npos || isspace(c)) {
            std::cerr << "AccountManager error: Username contains an invalid character" << std::endl;
            return CreateAccountStatus::FAILED;
        }
    }
    
    CreateAccountStatus res = CreateAccountStatus::SUCCESS;

    if (checkUsernameExists(username)) {
        std::cerr << "AccountManager error: User '" << username << "' already exist."
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

void AccountManager::updateScore(const int userId, const int newScore) {
    dbManager_->executeSqlChangeData(
        "UPDATE users SET score = MAX(score, ?) WHERE id = ?",
        {newScore, userId});
}

bool AccountManager::updateUsername(const int userID , std::string &newUsername){
    if (checkUsernameExists(newUsername)){
        std::cout << "a user already has this nickname" << std::endl;
        return false;
    }else {
        dbManager_->executeSqlChangeData(
            "UPDATE users SET username = ? WHERE id = ? ", {newUsername, userID});
        return true;
    }
}

void AccountManager::updatePassword(const int userID , std::string &newPassword){
    dbManager_->executeSqlChangeData(
        "UPDATE users SET password = ? WHERE id = ? ", {newPassword, userID});
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

std::vector<std::pair<std::string, size_t>> AccountManager::getRanking() const {
    return dbManager_->getRanking();
}

std::string AccountManager::getUserPasswordHash(const std::string &nickname) const {
    std::string sql = "SELECT password FROM users WHERE username = ?";
    std::string password;
    dbManager_->executeSqlRecoveryString(sql, {nickname}, password);
    return password;
}