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
    return dbManager_->addFriendshipDatabase(user, friendUser) && dbManager_->addFriendshipDatabase(friendUser, user);
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
    return dbManager_->removeFriendshipDatabase(user, friendUser) && dbManager_->removeFriendshipDatabase(friendUser, user);
}
