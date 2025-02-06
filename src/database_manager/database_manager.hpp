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
        * @brief Execute an SQL statement
        *
        * @param sql SQL statement to execute
        * @return true if the statement was executed successfully
        */
        bool executeSQL(const string &sql);

        /*
        * @brief Check if a user exists in the database
        *
        * @param username Username to check
        * @return true if the user exists
        */
        bool userExists(const string &username);

        /*
        * @brief Add a user to the database
        */
        bool addUser(const string &username, const string &password);

        /*
        * @brief Check if the user and password match
        */
        bool checkUserPassword(const string &username, const string &password);

        /*
        * @brief Check if a friendship exists in the database
        *
        * @param user Username of the first user
        * @param friendUser Username of the second user
        * @return true if the friendship exists
        */
        bool checkFriendshipExists(const string &user, const string &friendUser);

        /*
        * @brief Add a friendship to the database
        *
        * @param user Username of the first user
        * @param friendUser Username of the second user
        * @return true if the friendship was added successfully
        */
        bool addFriendshipDatabase(const string &user, const string &friendUser);

        /*
        * @brief Remove a friendship from the database
        *
        * @param user Username of the first user
        * @param friendUser Username of the second user
        * @return true if the friendship was removed successfully
        */
        bool removeFriendshipDatabase(const string &user, const string &friendUser);

        /*
        * @brief Update the score of a user in the database
        *
        * @param username Username of the user
        * @param newScore New score of the user
        */
        void updateScoreDatabase(const string &username, const int newScore);

        /*
        * @brief Get the ranking of all the users
        */
        vector<pair<string, int>> getRanking() const;

        /*
        * @brief Get the friends of a user
        */
        vector<string> getFriends(const string &username) const;
};

#endif // EXECUTE_SQL_HPP