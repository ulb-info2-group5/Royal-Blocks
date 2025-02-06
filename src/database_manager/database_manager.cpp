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

DatabaseManager::DatabaseManager() {
    if (sqlite3_open(DATABASE_PATH.c_str(), &db_) != SQLITE_OK) {
        cerr << "Error SQLite: " << sqlite3_errmsg(db_) << endl;
    }
    else {
        createTables();
    }
}

DatabaseManager::~DatabaseManager() {
    sqlite3_close(db_);
}

bool DatabaseManager::userExists(const string &username) {
    string query = "SELECT COUNT(*) FROM users WHERE username = ?";
    sqlite3_stmt *stmt;
    bool exists = false;

    if (sqlite3_prepare_v2(db_, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db_) << endl;
        sqlite3_finalize(stmt);
        return false;
    }
        
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0); // Récupérer le COUNT(*)
        exists = (count > 0);
    }

    sqlite3_finalize(stmt);
    return exists;
} 


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

bool DatabaseManager::checkFriendshipExists(const string &user, const string &friendUser) {
    // Check if the friendship already exists
    string checkSQL =
        "SELECT COUNT(*) FROM friends WHERE (user1 = ? AND user2 = ?) ";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db_, checkSQL.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db_) << endl;
        sqlite3_finalize(stmt);
        return false;
    }
    
    sqlite3_bind_text(stmt, 1, user.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, friendUser.c_str(), -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return true;
    }
    
    sqlite3_finalize(stmt);
    return false;
}

bool DatabaseManager::addFriendshipDatabase(const string &user, const string &friendUser) {
    string sql = "INSERT INTO friends (user1, user2) VALUES (?, ?)";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db_) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_bind_text(stmt, 1, user.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, friendUser.c_str(), -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "SQL error: " << sqlite3_errmsg(db_) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool DatabaseManager::removeFriendshipDatabase(const string &user, const string &friendUser) {
    string sql = "DELETE FROM friends WHERE user1 = ? AND user2 = ?";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db_) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_bind_text(stmt, 1, user.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, friendUser.c_str(), -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "SQL error: " << sqlite3_errmsg(db_) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

void DatabaseManager::updateScoreDatabase(const string &username, const int newScore) { 
    string sql = "UPDATE users SET score = MAX(score, ?) WHERE username = ?";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db_) << endl;
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_bind_int(stmt, 1, newScore);
    sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "SQL error: " << sqlite3_errmsg(db_) << endl;
    }

    sqlite3_finalize(stmt);
}

bool DatabaseManager::addUser(const string &username, const string &password) {
    string sql = "INSERT INTO users (username, password) VALUES (?, ?)";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db_) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "SQL error: " << sqlite3_errmsg(db_) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool DatabaseManager::checkUserPassword(const string &username, const string &password) {
    string sql = "SELECT * FROM users WHERE username = ? AND password = ?";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db_) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return true;
    }

    sqlite3_finalize(stmt);
    return false;
}

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