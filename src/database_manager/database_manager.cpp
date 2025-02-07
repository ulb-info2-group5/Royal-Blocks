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
}


// ### Destructor ###
DatabaseManager::~DatabaseManager() {
    sqlite3_close(db_);
}


// ### Private methods ###
bool DatabaseManager::createTables(const string &sql) {  
    return sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, nullptr) == SQLITE_OK;
}


// ### Public methods ###
bool DatabaseManager::executeSqlChangeData(const string &sql, const vector<string> &params) {
    // Prepare the SQL statement
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db_) << endl;
        return false;
    }

    // Bind the parameters
    for (size_t i = 0; i < params.size(); ++i) {
        sqlite3_bind_text(stmt, i + 1, params[i].c_str(), -1, SQLITE_STATIC);
    }

    // Execute the SQL statement
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    if (!success) {
        cerr << "SQL execution error: " << sqlite3_errmsg(db_) << endl;
    }

    // Finalize the statement
    sqlite3_finalize(stmt);
    return success;
}

bool DatabaseManager::executeSqlRecovery(const string &sql, const vector<string> &params, int &result) const {
    // Prepare the SQL statement
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db_) << endl;
        return false;
    }

    // Bind the parameters
    for (size_t i = 0; i < params.size(); ++i) {
        sqlite3_bind_text(stmt, i + 1, params[i].c_str(), -1, SQLITE_STATIC);
    }

    // Execute the SQL statement
    bool success = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = sqlite3_column_int(stmt, 0);
        success = true;
    }

    // Finalize the statement
    sqlite3_finalize(stmt);
    return success;
}


// ### Getters ###
sqlite3* DatabaseManager::getDatabase() const {
    return db_;
}

vector<pair<string, int>> DatabaseManager::getRanking() const {
    // Prepare the SQL statement
    vector<pair<string, int>> ranking;
    string sql = "SELECT username, score FROM users ORDER BY score DESC";
    sqlite3_stmt *stmt;

    // Execute the SQL statement
    if (sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, nullptr)
        == SQLITE_OK) {
        // Get the data from the statement
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