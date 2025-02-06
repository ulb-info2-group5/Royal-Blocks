/**
 * @file execute_sql.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief Execute SQL function definition
 * @date 2025-02-05
 *
 */

#include "sql_functions.hpp"
#include <iostream>

bool executeSQL(sqlite3 *db, const string &sql) {
    char *errMsg;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "Error SQLite: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

bool userExists(sqlite3 *db, const string &username) {
    string query = "SELECT COUNT(*) FROM users WHERE username = ?";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    return count > 0;
}

bool checkFriendshipExists(sqlite3 *db, const string &user, const string &friendUser) {
    // Check if the friendship already exists
    string checkSQL =
        "SELECT COUNT(*) FROM friends WHERE (user1 = '" + user + "' AND user2 = '" + friendUser + "') "
        "OR (user1 = '" + friendUser + "' AND user2 = '" + user + "')";
    sqlite3_stmt *stmt;
    int count = 0;

    if (sqlite3_prepare_v2(db, checkSQL.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
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

bool addFriendshipDatabase(sqlite3 *db, const string &user, const string &friendUser) {
    string sql = "INSERT INTO friends (user1, user2) VALUES ('"
                       + user + "', '" + friendUser + "')";
    return executeSQL(db, sql);
}

bool removeFriendshipDatabase(sqlite3 *db, const string &user, const string &friendUser) {
    string sql = "DELETE FROM friends WHERE user1 = '" + user + "' AND user2 = '" + friendUser + "'";
    return executeSQL(db, sql);
}

void updateScoreDatabase(sqlite3 *db, const string &username, const int newScore) { 
    string sql = "UPDATE users SET score = MAX(score, " + to_string(newScore) + ") WHERE username = '" + username + "'";
    executeSQL(db, sql);
}
