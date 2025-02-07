/**
 * @file friends_manager.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief Friends Manager class definition
 * @date 05/02/2025
 *
 */

#ifndef FRIENDS_MANAGER_HPP
#define FRIENDS_MANAGER_HPP

#include <memory>
#include <string>
#include <sqlite3.h>

#include "../database_manager/database_manager.hpp"

using namespace std;

class FriendsManager {
  private:
    shared_ptr<DatabaseManager> dbManager_;

    /*
    * @brief Check if a friendship exists between two users
    *
    * @param user Username of the first user
    * @param friendUser Username of the second user
    * @return true if the friendship exists
    */
    bool checkFriendshipExists(const string &user, const string &friendUser);
    
  public:
    /*
    * @brief Construct a new Friends Manager object
    * 
    * @param dbPath Path to the database file
    */
    FriendsManager(shared_ptr<DatabaseManager> &db);

    /*
      * @brief Destroy the Friends Manager object
    */
    ~FriendsManager() = default;

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
    * @brief Get all the list of friends of a user
    *
    * @param username Username of the user to get the friends
    * @return vector of friends of the user
    */
    vector<string> getFriends(const string &username) const;
};

#endif  // FRIENDS_MANAGER_HPP