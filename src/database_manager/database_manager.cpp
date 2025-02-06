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


DatabaseManager::DatabaseManager() {
    if (sqlite3_open(DATABASE_PATH.c_str(), &db_) != SQLITE_OK) {
        cerr << "Error SQLite: " << sqlite3_errmsg(db_) << endl;
    }
    else {
        createTables();
    }
}

bool DatabaseManager::executeSQL(const string &sql) {
    char *errMsg;
    if (sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "Error SQLite: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

bool DatabaseManager::userExists(const string &username) {
    string query = "SELECT COUNT(*) FROM users WHERE username = ?";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db_, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db_) << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    return count > 0;
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

    executeSQL(sqlUsers);
    executeSQL(sqlFriends);
}

bool DatabaseManager::checkFriendshipExists(const string &user, const string &friendUser) {
    // Check if the friendship already exists
    string checkSQL =
        "SELECT COUNT(*) FROM friends WHERE (user1 = '" + user + "' AND user2 = '" + friendUser + "') "
        "OR (user1 = '" + friendUser + "' AND user2 = '" + user + "')";
    sqlite3_stmt *stmt;
    int count = 0;

    if (sqlite3_prepare_v2(db_, checkSQL.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_step(stmt);
        count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
    }

    if (count > 0) {
        cerr << "Error: Friendship between '" << user << "' and '" << friendUser << "' already exists." << endl;
        return true;
    }
    return false;
}

bool DatabaseManager::addFriendshipDatabase(const string &user, const string &friendUser) {
    string sql = "INSERT INTO friends (user1, user2) VALUES ('"
                       + user + "', '" + friendUser + "')";
    return executeSQL(sql);
}

bool DatabaseManager::removeFriendshipDatabase(const string &user, const string &friendUser) {
    string sql = "DELETE FROM friends WHERE user1 = '" + user + "' AND user2 = '" + friendUser + "'";
    return executeSQL(sql);
}

void DatabaseManager::updateScoreDatabase(const string &username, const int newScore) { 
    string sql = "UPDATE users SET score = MAX(score, " + to_string(newScore) + ") WHERE username = '" + username + "'";
    executeSQL(sql);
}
