/**
 * @file friends_manager.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Friends Manager class definition
 * @date 05/02/2025
 *
 */

#include "friends_manager.hpp"
#include "../common/execute_sql.hpp"
#include <iostream>
#include <string>
#include <vector>

// TODO: check if in the friend list we have he current user with all the
// friends or just for each line we have the current user with 1 friend


FriendsManager::FriendsManager(const string &dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        cerr << "Error SQLite: " << sqlite3_errmsg(db) << endl;
    } else {
        createTable();
    }
}

FriendsManager::~FriendsManager() { sqlite3_close(db); }

void FriendsManager::createTable() {
    string sql = "CREATE TABLE IF NOT EXISTS friends ("
                      "user1 TEXT NOT NULL, "
                      "user2 TEXT NOT NULL, "
                      "FOREIGN KEY (user1) REFERENCES users(username), "
                      "FOREIGN KEY (user2) REFERENCES users(username), "
                      "PRIMARY KEY (user1, user2))";
    executeSQL(db, sql);
}

bool FriendsManager::addFriend(const string &user, const string &friendUser) {
    if (user == friendUser) {
        cerr << "Error: Cannot add yourself as a friend" << endl;
        return false;
    }

    // Check if the friend exists in the users database
    string checkSQL =
        "SELECT COUNT(*) FROM users WHERE username = '" + friendUser + "'";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, checkSQL.c_str(), -1, &stmt, nullptr)
        == SQLITE_OK) {
        sqlite3_step(stmt);
        int count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);

        if (count == 0) {
            cerr << "Error : The user '" << friendUser
                      << "' doesn't exist !" << endl;
            return false;
        }
    } else {
        cerr << "Error in adding friend while checking if the user exists." << endl;
        return false;
    }

    // Add the friends each other
    string sql1 = "INSERT INTO friends (user1, user2) VALUES ('"
                       + user + "', '" + friendUser + "')";
    string sql2 = "INSERT INTO friends (user1, user2) VALUES ('" + friendUser
                  + "', '" + user + "')";

    return executeSQL(db, sql1) && executeSQL(db, sql2);
}

vector<string> FriendsManager::getFriends(const string &username) {
    vector<string> friends;

    string sql = "SELECT user2 FROM friends WHERE user1 = '" + username
                      + "' "
                        "UNION "
                        "SELECT user1 FROM friends WHERE user2 = '"
                      + username + "'";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr)
        == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            friends.push_back(
                reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
        }
        sqlite3_finalize(stmt);
    } else {
        cerr << "Error in getting friends." << endl;
    }

    return friends;
}
