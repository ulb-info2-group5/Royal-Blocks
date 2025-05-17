/*
 * This file is part of Royal Blocks.
 *
 * Royal Blocks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Royal Blocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Royal Blocks.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

#include <sqlite3.h>
#include <stddef.h>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "../../../common/types/types.hpp"

class DatabaseManager {
  private:
    using MultiType = std::variant<size_t, std::string>;

    sqlite3 *db_;

  public:
    /*
     * @brief Constructor of the DatabaseManager class
     */
    DatabaseManager();

    /*
     * @brief Constructor of the DatabaseManager class
     * @param path Path to the database
     */
    DatabaseManager(const std::string &path);

    /*
     * @brief Destructor of the DatabaseManager class
     */
    ~DatabaseManager();

    /*
     * @brief Create a table in the database with the given SQL query
     */
    bool createTables(const std::string &sql);

    /*
     * @brief Execute a SQL query that m returns data frothe database
     *
     * @param sql SQL query to execute
     * @param params Parameters to bind to the query
     * @param result The result of the query to set in by reference (int)
     * return true if the query was successful
     */
    bool executeSqlRecoveryInt(const std::string &sql,
                               const std::vector<MultiType> &params,
                               int &result) const;

    /*
     * @brief Execute a SQL query that returns data from the database
     *
     * @param sql SQL query to execute
     * @param params Parameters to bind to the query
     * @param result The result of the query to set in by reference (string)
     * return true if the query was successful
     */
    bool executeSqlRecoveryString(const std::string &sql,
                                  const std::vector<MultiType> &params,
                                  std::string &result) const;

    /*
     * @brief Execute a SQL query that returns data from the database
     *
     * @param sql SQL query to execute
     * @param UserID Id to bind to the query
     * @return The result of the query (vector of int)
     */
    std::vector<int> getVectorInfo(const std::string &sql,
                                   const UserID &userID) const;

    /*
     * @brief Execute a SQL query that changes data of the database
     *
     * @param sql SQL query to execute
     * @param params Parameters to bind to the query (vector of MultiType (int
     * or string)) return bool True if it's executing well, false otherwise
     */
    bool executeSqlChangeData(const std::string &sql,
                              const std::vector<MultiType> &params);

    /*
     * @brief Get the database
     *
     * @return The database
     */
    sqlite3 *getDatabase() const;

    /*
     * @brief Add a friend to the database
     *
     * @return a vector of pairs containing the username and score of each user
     */
    std::vector<std::pair<std::string, size_t>> getRanking() const;

    /*
     * @brief Find the user in the table of database
     *
     * @param string table The table where to find the user
     * @param int userID The user id to find
     * @ return bool True if the user is in the table of database, false
     * otherwise
     */
    bool findUserInDatabase(const std::string &table, const UserID &userID);
};

#endif // DATABASE_MANAGER_HPP