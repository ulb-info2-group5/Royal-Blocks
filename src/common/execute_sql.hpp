/**
 * @file execute_sql.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief Execute SQL function definition
 * @date 2025-02-05
 *
 */

#ifndef EXECUTE_SQL_HPP
#define EXECUTE_SQL_HPP

#include <sqlite3.h>
#include <string>

using namespace std;

/*
 * @brief Execute an SQL statement
 *
 * @param sql SQL statement to execute
 * @return true if the statement was executed successfully
 */
bool executeSQL(sqlite3 *db, const string &sql);

#endif // EXECUTE_SQL_HPP