#include "friends_manager.hpp"
#include <iostream>
#include <ostream>
#include <string>

// ### Constructor ###
FriendsManager::FriendsManager(std::shared_ptr<DatabaseManager> &db)
    : dbManager_(db) {
    // Create the table of friends if it doesn't exist
    dbManager_->createTables("CREATE TABLE IF NOT EXISTS friends ("
                            "user1 INTEGER NOT NULL, "
                            "user2 INTEGER NOT NULL, "
                            "FOREIGN KEY (user1) REFERENCES users(id), "
                            "FOREIGN KEY (user2) REFERENCES users(id), "
                            "PRIMARY KEY (user1, user2))");

    dbManager_->createTables("CREATE TABLE IF NOT EXISTS pendingFriendRequests ("
                            "user1 INTEGER NOT NULL, "
                            "user2 INTEGER NOT NULL, "
                            "FOREIGN KEY (user1) REFERENCES users(id), "
                            "FOREIGN KEY (user2) REFERENCES users(id), "
                            "PRIMARY KEY (user1, user2))");
}

// ### Private methods ###
bool FriendsManager::checkFriendshipExists(const int idUser1,
                                        const int idUser2) const {
    std::string checkSQL = "SELECT COUNT(*) FROM friends WHERE (user1 = ? AND "
                        "user2 = ?) OR (user1 = ? AND user2 = ?)";
    int count = 0;
    return dbManager_->executeSqlRecoveryInt(
            checkSQL, {idUser1, idUser2, idUser2, idUser1}, count)
        && count > 0;
}

bool FriendsManager::checkUserExists(const int userId) const {
    std::string query = "SELECT COUNT(*) FROM users WHERE id = ?";
    int count = 0;
    return dbManager_->executeSqlRecoveryInt(query, {userId}, count)
        && count > 0;
}

// ### Public methods ###
bool FriendsManager::addFriend(const int userId, const int friendUserId) {
    if (userId == friendUserId) {
        std::cerr << "Error: Cannot add yourself as a friend" << std::endl;
        return false;
    }

    if (!checkUserExists(friendUserId)) {
        std::cerr << "Error: User with id '" << friendUserId
                << "' does not exist." << std::endl;
        return false;
    }

    if (checkFriendshipExists(userId, friendUserId)) {
        std::cerr << "Error: Friendship between '" << userId << "' and '"
                << friendUserId << "' already exists." << std::endl;
        return false;
    }

    // Add the friends each other
    return dbManager_->executeSqlChangeData(
        "INSERT INTO friends (user1, user2) VALUES (?, ?)",
        {userId, friendUserId});
}

bool FriendsManager::removeFriend(const int userId, const int friendUserId) {
    if (userId == friendUserId) {
        std::cerr << "Error: Cannot remove yourself as a friend" << std::endl;
        return false;
    }

    if (!checkFriendshipExists(userId, friendUserId)) {
        std::cerr << "Error: Friendship between '" << userId << "' and '"
                << friendUserId << "' does not exist." << std::endl;
        return false;
    }

    // Remove the friendship each other
    return dbManager_->executeSqlChangeData(
            "DELETE FROM friends WHERE user1 = ? AND user2 = ?",
            {userId, friendUserId})
        && dbManager_->executeSqlChangeData(
            "DELETE FROM friends WHERE user1 = ? AND user2 = ?",
            {friendUserId, userId});
}

// == pending friend == 


std::vector<int> FriendsManager::getPendingFriendRequest(const int userId){
    std::string sql =
    "SELECT user1, user2 FROM pendingFriendRequests WHERE user1 = ? OR user2 = ?";
    return dbManager_->getVectorInfo(sql, userId);
}


bool FriendsManager::isPendingFriendRequestExist(const int user1Id, const int user2Id){
    std::string checkSQL = "SELECT COUNT(*) FROM pendingFriendRequests WHERE (user1 = ? AND "
    "user2 = ?) OR (user1 = ? AND user2 = ?)";
    int count = 0;
    return dbManager_->executeSqlRecoveryInt(
    checkSQL, {user1Id, user2Id, user2Id, user1Id}, count)
    && count > 0;

}



bool FriendsManager::addPendingFriendRequest(const int user1Id, const int user2Id){
    if (user1Id == user2Id ){
        std::cerr << "Error: user1 = user2 " << std::endl;
        return false;
    }
    if (isPendingFriendRequestExist(user1Id, user2Id)){
        std::cerr << "error pendingFriendRequest already exists" << std::endl;
        return false;
    }
    if (checkFriendshipExists(user1Id, user2Id)){
    std::cerr << "error friendship exist " << std::endl;
    return false;
    }

    return dbManager_->executeSqlChangeData(
        "INSERT INTO pendingFriendRequests (user1, user2) VALUES (?, ?)",
        {user1Id, user2Id});
}


bool FriendsManager::removePendingFriendRequest(const int user1Id, const int user2Id){
    if (!isPendingFriendRequestExist(user1Id, user2Id)) {
        std::cerr << "Error: PendingFriendRequest between '" << user1Id << "' and '"
                << user2Id << "' does not exist." << std::endl;
        return false;
    }

    // Remove the friendship each other
    return dbManager_->executeSqlChangeData(
            "DELETE FROM pendingFriendRequests WHERE user1 = ? AND user2 = ?",
            {user1Id, user2Id})
        && dbManager_->executeSqlChangeData(
            "DELETE FROM pendingFriendRequests WHERE user1 = ? AND user2 = ?",
            {user2Id, user1Id});
}


// ### Getters ###

std::vector<int> FriendsManager::getFriends(const int userId) const {
    // Prepare the SQL statement
    std::string sql =
        "SELECT user1, user2 FROM friends WHERE user1 = ? OR user2 = ?";
    return dbManager_->getVectorInfo(sql, userId);
}
