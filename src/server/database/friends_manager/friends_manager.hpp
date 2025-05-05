#ifndef FRIENDS_MANAGER_HPP
#define FRIENDS_MANAGER_HPP

#include <memory>
#include <vector>    

#include "/home/ethan/code/group-5/src/common/types/types.hpp"

class DatabaseManager;

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
    bool checkFriendshipExists(const UserID& user1ID, const UserID& user2ID) const;

    /*
    * @brief Check if a user exists in the database
    *
    * @param userId Id of the user
    * @return true if the user exists
    */
    bool checkUserExists(const UserID& userID) const;

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
    bool addFriend(const UserID& userID, const UserID& friendID);


    bool addPendingFriendRequest(const UserID& user1ID, const UserID& user2ID);
    bool isPendingFriendRequestExist(const UserID& user1ID, const UserID& user2ID);

    bool removePendingFriendRequest(const UserID& user1ID, const UserID&  user2ID);
    std::vector<int> getPendingFriendRequest(const UserID& userID);

    /*
    * @brief Remove a friend from the database
    *
    * @param userID ID of the user that wants to remove a friend
    * @param friendID ID of the friend to remove
    * @return true if the friend was removed successfully
    */
    bool removeFriend(const UserID& userID, const UserID& friendID);

    /*
    * @brief Get all the list of friends of a user
    *
    * @param userId Id of the user
    * @return vector<int> List of friends
    */
    std::vector<int> getFriends(const UserID& userID) const;



};

#endif // FRIENDS_MANAGER_HPP
