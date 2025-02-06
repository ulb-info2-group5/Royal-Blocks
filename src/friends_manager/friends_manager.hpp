/**
 * @file friends_manager.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief Friends Manager class definition
 * @date 05/02/2025
 *
 */

#ifndef FRIENDS_MANAGER_HPP
#define FRIENDS_MANAGER_HPP

#include <string>
#include <sqlite3.h>
#include <vector>

using namespace std;

class FriendsManager {
  private:
    sqlite3 *db;

    /*
      * @brief Create the friends table in the database
    */
    void createTable();

  public:
    /*
      * @brief Construct a new Friends Manager object
      * 
      * @param dbPath Path to the database file
    */
    FriendsManager(const string &dbPath);

    /*
      * @brief Destroy the Friends Manager object
    */
    ~FriendsManager();

    /*
     * @brief Add a friend to the database
     *
     * @param user Username of the user that wants to add a friend
     * @param friendUser Username of user to add as a friend
     * @return true if the friend was added successfully
     */
    bool addFriend(const string &user, const string &friendUser);

    /*
      * @brief Remove a friend from the database
      * 
      * @param user Username of the user that wants to remove a friend
      * @param friendUser Username of the friend to remove
      * @return true if the friend was removed successfully
    */
    bool removeFriend(const string &user, const string &friendUser);

    /*
      * @brief Get the friends of a user
      * 
      * @param username Username of the user
    */
    vector<string> getFriends(const string &username);
    
};

#endif  // FRIENDS_MANAGER_HPP