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

/*
 * @brief Check if a user exists in the database
 *
 * @param username Username to check
 * @return true if the user exists
 */
bool userExists(sqlite3 *db, const string &username);

/*
 * @brief Check if a friendship exists in the database
 *
 * @param user Username of the first user
 * @param friendUser Username of the second user
 * @return true if the friendship exists
 */
bool checkFriendshipExists(sqlite3 *db, const string &user, const string &friendUser);

/*
 * @brief Add a friendship to the database
 *
 * @param user Username of the first user
 * @param friendUser Username of the second user
 * @return true if the friendship was added successfully
 */
bool addFriendshipDatabase(sqlite3 *db, const string &user, const string &friendUser);

/*
 * @brief Remove a friendship from the database
 *
 * @param user Username of the first user
 * @param friendUser Username of the second user
 * @return true if the friendship was removed successfully
 */
bool removeFriendshipDatabase(sqlite3 *db, const string &user, const string &friendUser);

/*
 * @brief Update the score of a user in the database
 *
 * @param username Username of the user
 * @param newScore New score of the user
 */
void updateScoreDatabase(sqlite3 *db, const string &username, const int newScore);

#endif // EXECUTE_SQL_HPP