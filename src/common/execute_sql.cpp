/**
 * @file execute_sql.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief Execute SQL function definition
 * @date 2025-02-05
 *
 */

#include "execute_sql.hpp"
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