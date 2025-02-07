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

// ### Constructor ###
FriendsManager::FriendsManager(shared_ptr<DatabaseManager> &db)
    : dbManager_(db) {
}

// ### Private methods ###
bool FriendsManager::checkFriendshipExists(const string &user, const string &friendUser) {
    string checkSQL = "SELECT COUNT(*) FROM friends WHERE (user1 = ? AND user2 = ?)";
    int count = 0;
    return dbManager_->executeSqlRecovery(checkSQL, {user, friendUser}, count) && count > 0;
}

// ### Public methods ###
bool FriendsManager::addFriend(const string &user, const string &friendUser) {
    
    if (user == friendUser) {
        cerr << "Error: Cannot add yourself as a friend" << endl;
        return false;
    }

    // Check if the friendship already exists
    if (checkFriendshipExists(user, friendUser)) {
        return false;
    }

    // Add the friends each other
    return dbManager_->executeSqlChangeData("INSERT INTO friends (user1, user2) VALUES (?, ?)", {user, friendUser}) && dbManager_->executeSqlChangeData("INSERT INTO friends (user1, user2) VALUES (?, ?)", {friendUser, user});
}

bool FriendsManager::removeFriend(const string &user, const string &friendUser) {
    if (user == friendUser) {
        cerr << "Error: Cannot remove yourself as a friend" << endl;
        return false;
    }

    // Check if the friendship exists
    if (!checkFriendshipExists(user, friendUser)) {
        cerr << "Error: Friendship between '" << user << "' and '" << friendUser << "' does not exist." << endl;
        return false;
    }

    // Remove the friendship each other
    return dbManager_->executeSqlChangeData("DELETE FROM friends WHERE user1 = ? AND user2 = ?", {user, friendUser}) && dbManager_->executeSqlChangeData("DELETE FROM friends WHERE user1 = ? AND user2 = ?", {friendUser, user});

}


// ### Getters ###

vector<string> FriendsManager::getFriends(const string &username) const {
    vector<string> friends;

    string sql = "SELECT user2 FROM friends WHERE user1 = ? UNION SELECT user1 FROM friends WHERE user2 = ?";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(dbManager_->getDatabase(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(dbManager_->getDatabase()) << endl;
        sqlite3_finalize(stmt);
        return friends;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        string friendUser = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        friends.push_back(friendUser);
    }

    sqlite3_finalize(stmt);
    return friends;
}
