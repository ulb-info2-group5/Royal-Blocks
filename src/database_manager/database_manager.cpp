/**
 * @file execute_sql.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief Class DatabaseManager definition
 * @date 2025-02-05
 *
 */

#include "database_manager.hpp"
#include "../config.hpp"
#include <iostream>
#include <sqlite3.h>
#include <vector>

// TODO: Add documentation
// TODO: Add tests

// ### Constructor ###
DatabaseManager::DatabaseManager() {
    if (sqlite3_open(DATABASE_PATH.c_str(), &db_) != SQLITE_OK) {
        cerr << "Error SQLite: " << sqlite3_errmsg(db_) << endl;
    }
    else {
        createTables();
    }
}

// ### Destructor ###
DatabaseManager::~DatabaseManager() {
    sqlite3_close(db_);
}


// ### Private methods ###
void DatabaseManager::createTables() {
    string sqlUsers = "CREATE TABLE IF NOT EXISTS users ("
                        "username TEXT PRIMARY KEY NOT NULL, "
                        "password TEXT NOT NULL, "
                        "score INTEGER DEFAULT 0);";

    string sqlFriends = "CREATE TABLE IF NOT EXISTS friends ("
                        "user1 TEXT NOT NULL, "
                        "user2 TEXT NOT NULL, "
                        "FOREIGN KEY (user1) REFERENCES users(username), "
                        "FOREIGN KEY (user2) REFERENCES users(username), "
                        "PRIMARY KEY (user1, user2));";
    
    sqlite3_exec(db_, sqlUsers.c_str(), nullptr, nullptr, nullptr);
    sqlite3_exec(db_, sqlFriends.c_str(), nullptr, nullptr, nullptr);
}

bool DatabaseManager::executeSqlChangeData(const string &sql, const vector<string> &params) {
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db_) << endl;
        return false;
    }

    for (size_t i = 0; i < params.size(); ++i) {
        sqlite3_bind_text(stmt, i + 1, params[i].c_str(), -1, SQLITE_STATIC);
    }

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    if (!success) {
        cerr << "SQL execution error: " << sqlite3_errmsg(db_) << endl;
    }

    sqlite3_finalize(stmt);
    return success;
}

bool DatabaseManager::executeSqlRecovery(const string &sql, const vector<string> &params, int &result) const {
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db_) << endl;
        return false;
    }

    for (size_t i = 0; i < params.size(); ++i) {
        sqlite3_bind_text(stmt, i + 1, params[i].c_str(), -1, SQLITE_STATIC);
    }

    bool success = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = sqlite3_column_int(stmt, 0);
        success = true;
    }

    sqlite3_finalize(stmt);
    return success;
}


// ### Public methods ###
bool DatabaseManager::checkUserExists(const string &username) {
    string query = "SELECT COUNT(*) FROM users WHERE username = ?";
    int count = 0;
    return executeSqlRecovery(query, {username}, count) && count > 0;
}


bool DatabaseManager::checkFriendshipExists(const string &user, const string &friendUser) {
    string checkSQL = "SELECT COUNT(*) FROM friends WHERE (user1 = ? AND user2 = ?)";
    int count = 0;
    return executeSqlRecovery(checkSQL, {user, friendUser}, count) && count > 0;
}

bool DatabaseManager::addFriendshipDatabase(const string &user, const string &friendUser) {
    return executeSqlChangeData("INSERT INTO friends (user1, user2) VALUES (?, ?)", {user, friendUser});
}

bool DatabaseManager::removeFriendshipDatabase(const string &user, const string &friendUser) {
    return executeSqlChangeData("DELETE FROM friends WHERE user1 = ? AND user2 = ?", {user, friendUser});
}

void DatabaseManager::updateScoreDatabase(const string &username, const int newScore) { 
    executeSqlChangeData("UPDATE users SET score = MAX(score, ?) WHERE username = ?", {to_string(newScore), username});
}

bool DatabaseManager::addUser(const string &username, const string &password) {
    return executeSqlChangeData("INSERT INTO users (username, password) VALUES (?, ?)", {username, password});
}

bool DatabaseManager::deleteUser(const string &username) {
    return executeSqlChangeData("DELETE FROM users WHERE username = ?", {username});
}

bool DatabaseManager::checkUserPassword(const string &username, const string &password) {
    string sql = "SELECT COUNT(*) FROM users WHERE username = ? AND password = ?";
    int count = 0;
    return executeSqlRecovery(sql, {username, password}, count) && count > 0;
}


// ### Getters ###
vector<pair<string, int>> DatabaseManager::getRanking() const {
    vector<pair<string, int>> ranking;

    string sql = "SELECT username, score FROM users ORDER BY score DESC";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, nullptr)
        == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            string username =
                reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            int score = sqlite3_column_int(stmt, 1);

            ranking.push_back({username, score});
        }
        sqlite3_finalize(stmt);
    } else {
        cerr << "Error in getting ranking." << endl;
    }

    return ranking;
}

vector<string> DatabaseManager::getFriends(const string &username) const {
    vector<string> friends;

    string sql = "SELECT user2 FROM friends WHERE user1 = ? UNION SELECT user1 FROM friends WHERE user2 = ?";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db_) << endl;
        sqlite3_finalize(stmt);
        return friends;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        string friendUser = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        friends.push_back(friendUser);
    }

    sqlite3_finalize(stmt);
    return friends;
}
