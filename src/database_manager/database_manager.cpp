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


// ### Public methods ###
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


// ### Getters ###
sqlite3* DatabaseManager::getDatabase() const {
    return db_;
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