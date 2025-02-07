/**
 * @file execute_sql.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief Class DatabaseManager definition
 * @date 2025-02-05
 *
 */

#ifndef EXECUTE_SQL_HPP
#define EXECUTE_SQL_HPP

#include <sqlite3.h>
#include <string>
#include <vector>

using namespace std;

class DatabaseManager {
    private:
        sqlite3* db_;

        /*
        * @brief Create the tables in the database (users and friends)
        */
        void createTables();

    public:
        /*
        * @brief Constructor of the DatabaseManager class
        */
        DatabaseManager();

        /*
        * @brief Destructor of the DatabaseManager class
        */
        ~DatabaseManager();

        /*
        * @brief Execute a SQL query that returns a value
        *
        * @param sql SQL query to execute
        * @param params Parameters to bind to the query
        * @return true if the query was successful
        */
        bool executeSqlRecovery(const string &sql, const vector<string> &params, int &result) const;

        /*
        * @brief Execute a SQL query that changes data in the database
        *
        * @param sql SQL query to execute
        * @param params Parameters to bind to the query
        * @return true if the query was successful
        */
        bool executeSqlChangeData(const string &sql, const vector<string> &params);

        /*
        * @brief Get the database
        *
        * @return The database
        */
        sqlite3* getDatabase() const;

        /*
        * @brief Add a friend to the database
        *
        * @return a vector of pairs containing the username and score of each user
        */
        vector<pair<string, int>> getRanking() const;

};

#endif // EXECUTE_SQL_HPP