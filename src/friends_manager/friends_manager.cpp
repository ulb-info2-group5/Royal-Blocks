/**
 * @file friends_manager.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Friends Manager class definition
 * @date 05/02/2025
 *
 */

#include "friends_manager.hpp"
#include <iostream>
#include <string>
#include <vector>

// TODO: check if in the friend list we have he current user with all the
// friends or just for each line we have the current user with 1 friend

FriendsManager::FriendsManager(shared_ptr<DatabaseManager> &db)
    : dbManager_(db) {
}

bool FriendsManager::addFriend(const string &user, const string &friendUser) {
    if (user == friendUser) {
        cerr << "Error: Cannot add yourself as a friend" << endl;
        return false;
    }

    // Check if the friendUser exists
    if (!dbManager_->userExists(friendUser)) {
        cerr << "Error: User '" << friendUser << "' does not exist." << endl;
        return false;
    }

    // Check if the friendship already exists
    if (dbManager_->checkFriendshipExists(user, friendUser)) {
        return false;
    }

    // Add the friends each other
    return dbManager_->addFriendshipDatabase(user, friendUser) && addFriendshipDatabase(db, friendUser, user);
}

bool FriendsManager::removeFriend(const string &user, const string &friendUser) {
    if (user == friendUser) {
        cerr << "Error: Cannot remove yourself as a friend" << endl;
        return false;
    }

    // Check if the friendship exists
    if (!dbManager_->checkFriendshipExists(user, friendUser)) {
        cerr << "Error: Friendship between '" << user << "' and '" << friendUser << "' does not exist." << endl;
        return false;
    }

    // Remove the friendship each other
    return dbManager_->removeFriendshipDatabase(user, friendUser) && removeFriendshipDatabase(db, friendUser, user);
}


vector<string> FriendsManager::getFriends(const string &username) {
    vector<string> friends;

    string sql = "SELECT user2 FROM friends WHERE user1 = '" + username
                      + "' "
                        "UNION "
                        "SELECT user1 FROM friends WHERE user2 = '"
                      + username + "'";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(sql.c_str(), -1, &stmt, nullptr)
        == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            friends.push_back(
                reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
        }
        sqlite3_finalize(stmt);
    } else {
        cerr << "Error in getting friends." << endl;
    }

    return friends;
}
