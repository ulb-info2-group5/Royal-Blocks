/**
 * @file main.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Main program file
 * @date 05/02/2025
 * 
 */

#include "account_manager/account_manager.hpp"
#include "friends_manager/friends_manager.hpp"
#include "config.hpp"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main() {
    // ### Account Manager ###
    AccountManager accountManager(DATABASE_PATH);
    accountManager.launch();
    cout << endl;
    cout << "Users in the database:" << endl;
    accountManager.getUsers();

    cout << endl;

    // ### Friends Manager ###
    FriendsManager friendManager(DATABASE_PATH);
    cout << "Enter the username of the user that ask to add a friend: ";
    string user1;
    cin >> user1;
    cout << "Enter the username of the user to add to the friendlist: ";
    string user2;
    cin >> user2;

    friendManager.addFriend(user1, user2);
    vector<string> vec = friendManager.getFriends(user1);
    cout << "Friends of " << user1 << ":" << endl;
    for (const string &friendUser : vec) {
        cout << "- " << friendUser << endl;
    }

    accountManager.updateScore("ethan", 10);

    vector<pair<string, int>> ranking = accountManager.getRanking();
    cout << endl;
    cout << "Ranking:" << endl;
    for (const pair<string, int> &user : ranking) {
        cout << user.first << " - " << user.second << endl;
    }

    return 0;
}
