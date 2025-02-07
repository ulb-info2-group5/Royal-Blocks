/**
 * @file friends_manager.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Friends Manager class definition
 * @date 05/02/2025
 *
 */

#include "friends_manager.hpp"
#include <iostream>
#include <ostream>
#include <string>


// ### Constructor ###
FriendsManager::FriendsManager(shared_ptr<DatabaseManager> &db)
    : dbManager_(db) {
    // Create the table of friends if it doesn't exist
    dbManager_->createTables("CREATE TABLE IF NOT EXISTS friends ("
                        "user1 INTEGER NOT NULL, "
                         "user2 INTEGER NOT NULL, "
                        "FOREIGN KEY (user1) REFERENCES users(id), "
                        "FOREIGN KEY (user2) REFERENCES users(id), "
                        "PRIMARY KEY (user1, user2))");
}

// ### Private methods ###
bool FriendsManager::checkFriendshipExists(const int idUser1, const int idUser2) const {
    string checkSQL = "SELECT COUNT(*) FROM friends WHERE (user1 = ? AND user2 = ?) OR (user1 = ? AND user2 = ?)";
    int count = 0;
    return dbManager_->executeSqlRecoveryInt(checkSQL, {idUser1, idUser2, idUser2, idUser1}, count) && count > 0;
}

bool FriendsManager::checkUserExists(const int userId) const {
    string query = "SELECT COUNT(*) FROM users WHERE id = ?";
    int count = 0;
    return dbManager_->executeSqlRecoveryInt(query, {userId}, count) && count > 0;    
}

// ### Public methods ###
bool FriendsManager::addFriend(const int userId, const int friendUserId) {
    if (userId == friendUserId) {
        cerr << "Error: Cannot add yourself as a friend" << endl;
        return false;
    }

    if (!checkUserExists(friendUserId)) {
        cerr << "Error: User with id '" << friendUserId << "' does not exist." << endl;
        return false;
    }

    if (checkFriendshipExists(userId, friendUserId)) {
        cerr << "Error: Friendship between '" << userId << "' and '" << friendUserId << "' already exists." << endl;
        return false;
    }

    // Add the friends each other
    return dbManager_->executeSqlChangeData("INSERT INTO friends (user1, user2) VALUES (?, ?)", {userId, friendUserId});
}

bool FriendsManager::removeFriend(const int userId, const int friendUserId) {
    if (userId == friendUserId) {
        cerr << "Error: Cannot remove yourself as a friend" << endl;
        return false;
    }

    if (!checkFriendshipExists(userId, friendUserId)) {
        cerr << "Error: Friendship between '" << userId << "' and '" << friendUserId << "' does not exist." << endl;
        return false;
    }

    // Remove the friendship each other
    return dbManager_->executeSqlChangeData("DELETE FROM friends WHERE user1 = ? AND user2 = ?", {userId, friendUserId}) && dbManager_->executeSqlChangeData("DELETE FROM friends WHERE user1 = ? AND user2 = ?", {friendUserId, userId});

}


// ### Getters ###

vector<int> FriendsManager::getFriends(const int userId) const {
    // Prepare the SQL statement
    string sql = "SELECT user1, user2 FROM friends WHERE user1 = ? OR user2 = ?";
    return dbManager_->getVectorInfo(sql, userId);
}
