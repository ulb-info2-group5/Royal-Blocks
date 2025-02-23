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


// ### Constructor ###
DatabaseManager::DatabaseManager() {
    if (sqlite3_open(DATABASE_PATH.c_str(), &db_) != SQLITE_OK) {
        cerr << "Error SQLite: " << sqlite3_errmsg(db_) << endl;
    }
}

// ### Constructor With Database Path ###
DatabaseManager::DatabaseManager(const string &path) {
    if (sqlite3_open(path.c_str(), &db_) != SQLITE_OK) {
        cerr << "Error SQLite: " << sqlite3_errmsg(db_) << endl;
    }
}


// ### Destructor ###
DatabaseManager::~DatabaseManager() {
    sqlite3_close(db_);
}


// ### Private methods ###
bool DatabaseManager::createTables(const string &sql) {  
    char* errorMess = nullptr;
    if ( sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &errorMess) == SQLITE_OK) {
        return true;
    }else {
        std::cerr << "error (create Table): " << errorMess << std::endl;
        sqlite3_free(errorMess);
        return false;
    }
}


// ### Public methods ###
bool DatabaseManager::executeSqlChangeData(const string &sql, const vector<MultiType> &params) {
    // Prepare the SQL statement
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db_) << endl;
        return false;
    }

    // Bind the parameters
    for (size_t i = 0; i < params.size(); ++i) {
        if (holds_alternative<int>(params[i])) {
            sqlite3_bind_int(stmt, i + 1, get<int>(params[i]));
        } else {
            sqlite3_bind_text(stmt, i + 1, get<string>(params[i]).c_str(), -1, SQLITE_STATIC);
        }
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

bool DatabaseManager::executeSqlRecoveryInt(const string &sql, const vector<MultiType> &params, int &result) const {
    // Prepare the SQL statement
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db_) << endl;
        return false;
    }

    // Bind the parameters
    for (size_t i = 0; i < params.size(); ++i) {
        if (holds_alternative<int>(params[i])) {
            sqlite3_bind_int(stmt, i + 1, get<int>(params[i]));
        } else {
            sqlite3_bind_text(stmt, i + 1, get<string>(params[i]).c_str(), -1, SQLITE_STATIC);
        }
    }

    // Execute the SQL statement
    bool success = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = sqlite3_column_int(stmt, 0);
        success = true;
    } else {
        cerr << "SQL execution error: " << sqlite3_errmsg(db_) << endl;
    }

    // Finalize the statement
    sqlite3_finalize(stmt);
    return success;
}


bool DatabaseManager::executeSqlRecoveryString(const string &sql, const vector<MultiType> &params, string &result) const {
    // Prepare the SQL statement
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db_) << endl;
        return false;
    }

    // Bind the parameters
    for (size_t i = 0; i < params.size(); ++i) {
        if (holds_alternative<int>(params[i])) {
            sqlite3_bind_int(stmt, i + 1, get<int>(params[i]));
        } else {
            sqlite3_bind_text(stmt, i + 1, get<string>(params[i]).c_str(), -1, SQLITE_STATIC);
        }
    }

    // Execute the SQL statement
    bool success = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        success = true;
    } else {
        cerr << "SQL execution error: " << sqlite3_errmsg(db_) << endl;
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

vector<int> DatabaseManager::getVectorInfo(const string &sql, int id) const {
    vector<int> result;
    sqlite3_stmt* stmt;

    // Prepare the SQL statement
    int rc = sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Erreur lors de la préparation de la requête : " << sqlite3_errmsg(db_) << endl;
        return result;
    }
    
    // Bind the parameters
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_bind_int(stmt, 2, id);
    
    // Execute the SQL statement
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int colUser1 = sqlite3_column_int(stmt, 0);
        int colUser2 = sqlite3_column_int(stmt, 1);
        
        int friendId = (colUser1 == id) ? colUser2 : colUser1;
        result.push_back(friendId);
    }
    
    // Verify that the loop exited because the statement was finished
    if (rc != SQLITE_DONE) {
        cerr << "Erreur lors de l'exécution de la requête : " << sqlite3_errmsg(db_) << endl;
    }
    
    // Finalize the statement
    sqlite3_finalize(stmt);
    return result;
}