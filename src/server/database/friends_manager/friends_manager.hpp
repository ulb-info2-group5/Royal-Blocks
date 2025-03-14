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
 #include <sqlite3.h>
 
 #include "../database_manager/database_manager.hpp"
 
 class FriendsManager {
   private:
     std::shared_ptr<DatabaseManager> dbManager_;
 
     /*
      * @brief Check if a friendship exists between two users
      *
      * @param idUser1 Id of the first user
      * @param idUser2 Id of the second user
      * @return true if the friendship exists
      */
     bool checkFriendshipExists(const int idUser1, const int idUser2) const;
 
     /*
      * @brief Check if a user exists in the database
      *
      * @param userId Id of the user
      * @return true if the user exists
      */
     bool checkUserExists(const int userId) const;
 
   public:
     /*
      * @brief Construct a new Friends Manager object
      *
      * @param dbPath Path to the database file
      */
     FriendsManager(std::shared_ptr<DatabaseManager> &db);
 
     /*
      * @brief Destroy the Friends Manager object
      */
     ~FriendsManager() = default;
 
     /*
      * @brief Add a friend to the database
      *
      * @param user Username of the user that wants to add a friend
      * @param friendUser Username of the friend to add
      * @return true if the friend was added successfully
      */
     bool addFriend(const int userId, const int friendUserId);
 
 
     bool addPendingFriendRequest(const int user1Id, const int user2Id);
     bool isPendingFriendRequestExist(const int user1Id, const int user2Id);
 
     bool removePendingFriendRequest(const int user1Id, const int user2Id);
     std::vector<int> getPendingFriendRequest(const int userId);
 
     /*
      * @brief Remove a friend from the database
      *
      * @param user Username of the user that wants to remove a friend
      * @param friendUser Username of the friend to remove
      * @return true if the friend was removed successfully
      */
     bool removeFriend(const int userId, const int friendUserId);
 
     /*
      * @brief Get all the list of friends of a user
      *
      * @param userId Id of the user
      * @return vector<int> List of friends
      */
     std::vector<int> getFriends(const int userId) const;
 
 
 
 };
 
 #endif // FRIENDS_MANAGER_HPP
 