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

#include "friends_manager.hpp"

#include <iostream>
#include <string>

#include "../database_manager/database_manager.hpp"

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

    dbManager_->createTables(
        "CREATE TABLE IF NOT EXISTS pendingFriendRequests ("
        "user1 INTEGER NOT NULL, "
        "user2 INTEGER NOT NULL, "
        "FOREIGN KEY (user1) REFERENCES users(id), "
        "FOREIGN KEY (user2) REFERENCES users(id), "
        "PRIMARY KEY (user1, user2))");
}

// ### Private methods ###
bool FriendsManager::checkFriendshipExists(const UserID &user1ID,
                                           const UserID &user2ID) const {
    std::string checkSQL = "SELECT COUNT(*) FROM friends WHERE (user1 = ? AND "
                           "user2 = ?) OR (user1 = ? AND user2 = ?)";
    int count = 0;
    return dbManager_->executeSqlRecoveryInt(
               checkSQL, {user1ID, user2ID, user2ID, user1ID}, count)
           && count > 0;
}

bool FriendsManager::checkUserExists(const UserID &userID) const {
    std::string query = "SELECT COUNT(*) FROM users WHERE id = ?";
    int count = 0;
    return dbManager_->executeSqlRecoveryInt(query, {userID}, count)
           && count > 0;
}

// ### Public methods ###
bool FriendsManager::addFriend(const UserID &userID, const UserID &friendID) {
    if (userID == friendID) {
        std::cerr << "Error: Cannot add yourself as a friend" << std::endl;
        return false;
    }

    if (!checkUserExists(friendID)) {
        std::cerr << "Error: User with id '" << friendID << "' does not exist."
                  << std::endl;
        return false;
    }

    if (checkFriendshipExists(userID, friendID)) {
        std::cerr << "Error: Friendship between '" << userID << "' and '"
                  << friendID << "' already exists." << std::endl;
        return false;
    }

    // Add the friends each other
    return dbManager_->executeSqlChangeData(
        "INSERT INTO friends (user1, user2) VALUES (?, ?)", {userID, friendID});
}

bool FriendsManager::removeFriend(const UserID &userID,
                                  const UserID &friendID) {
    if (userID == friendID) {
        std::cerr << "Error: Cannot remove yourself as a friend" << std::endl;
        return false;
    }

    if (!checkFriendshipExists(userID, friendID)) {
        std::cerr << "Error: Friendship between '" << userID << "' and '"
                  << friendID << "' does not exist." << std::endl;
        return false;
    }

    // Remove the friendship each other
    return dbManager_->executeSqlChangeData(
               "DELETE FROM friends WHERE user1 = ? AND user2 = ?",
               {userID, friendID})
           && dbManager_->executeSqlChangeData(
               "DELETE FROM friends WHERE user1 = ? AND user2 = ?",
               {friendID, userID});
}

// == pending friend ==

std::vector<int> FriendsManager::getPendingFriendRequest(const UserID &userID) {
    std::string sql = "SELECT user1, user2 FROM pendingFriendRequests WHERE "
                      "user1 = ? OR user2 = ?";
    return dbManager_->getVectorInfo(sql, userID);
}

bool FriendsManager::isPendingFriendRequestExist(const UserID &user1ID,
                                                 const UserID &user2ID) {
    std::string checkSQL =
        "SELECT COUNT(*) FROM pendingFriendRequests WHERE (user1 = ? AND "
        "user2 = ?) OR (user1 = ? AND user2 = ?)";
    int count = 0;
    return dbManager_->executeSqlRecoveryInt(
               checkSQL, {user1ID, user2ID, user2ID, user1ID}, count)
           && count > 0;
}

bool FriendsManager::addPendingFriendRequest(const UserID &user1ID,
                                             const UserID &user2ID) {
    if (user1ID == user2ID) {
        std::cerr << "Error: user1 = user2 " << std::endl;
        return false;
    }
    if (isPendingFriendRequestExist(user1ID, user2ID)) {
        std::cerr << "error pendingFriendRequest already exists" << std::endl;
        return false;
    }
    if (checkFriendshipExists(user1ID, user2ID)) {
        std::cerr << "error friendship exist " << std::endl;
        return false;
    }

    return dbManager_->executeSqlChangeData(
        "INSERT INTO pendingFriendRequests (user1, user2) VALUES (?, ?)",
        {user1ID, user2ID});
}

bool FriendsManager::removePendingFriendRequest(const UserID &user1ID,
                                                const UserID &user2ID) {
    if (!isPendingFriendRequestExist(user1ID, user2ID)) {
        std::cerr << "Error: PendingFriendRequest between '" << user1ID
                  << "' and '" << user2ID << "' does not exist." << std::endl;
        return false;
    }

    // Remove the friendship each other
    return dbManager_->executeSqlChangeData("DELETE FROM pendingFriendRequests "
                                            "WHERE user1 = ? AND user2 = ?",
                                            {user1ID, user2ID})
           && dbManager_->executeSqlChangeData(
               "DELETE FROM pendingFriendRequests WHERE user1 = ? AND user2 = "
               "?",
               {user2ID, user1ID});
}

// ### Getters ###

std::vector<int> FriendsManager::getFriends(const UserID &userID) const {
    // Prepare the SQL statement
    std::string sql =
        "SELECT user1, user2 FROM friends WHERE user1 = ? OR user2 = ?";
    return dbManager_->getVectorInfo(sql, userID);
}
