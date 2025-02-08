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
#include <variant>
#include <vector>

using namespace std;

class DatabaseManager {
    private:
        using MultiType = variant<int, string>;

        sqlite3* db_;

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
        * @brief Create a table in the database with the given SQL query
        */
        bool createTables(const string &sql);

        /*
        * @brief Execute a SQL query that m returns data frothe database
        *
        * @param sql SQL query to execute
        * @param params Parameters to bind to the query
        * @param result The result of the query to set in by reference (int)
        * return true if the query was successful
        */
        bool executeSqlRecoveryInt(const string &sql, const vector<MultiType> &params, int &result) const;

        /*
        * @brief Execute a SQL query that returns data from the database
        *
        * @param sql SQL query to execute
        * @param params Parameters to bind to the query
        * @param result The result of the query to set in by reference (string)
        * return true if the query was successful
        */
        bool executeSqlRecoveryString(const string &sql, const vector<MultiType> &params, string &result) const;

        /*
        * @brief Execute a SQL query that returns data from the database
        *
        * @param sql SQL query to execute
        * @param id Id to bind to the query
        * @return The result of the query (vector of int)
        */
        vector<int> getVectorInfo(const string &sql, const int id) const;

        /*
        * @brief Execute a SQL query that changes data of the database
        *
        * @param sql SQL query to execute
        * @param params Parameters to bind to the query (vector of MultiType (int or string))
        */
        bool executeSqlChangeData(const string &sql, const vector<MultiType> &params);

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