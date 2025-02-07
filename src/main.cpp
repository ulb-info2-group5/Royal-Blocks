/**
 * @file main.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Main program file
 * @date 05/02/2025
 * 
 */

#include "account_manager/account_manager.hpp"
#include "database_manager/database_manager.hpp"
#include "friends_manager/friends_manager.hpp"
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

int main() {
    // ### Account Manager ###
    shared_ptr<DatabaseManager> dbManager = make_shared<DatabaseManager>();
    AccountManager accountManager = AccountManager(dbManager);
    accountManager.launch();
    cout << endl;

    // ### Friends Manager ###
    FriendsManager friendManager(dbManager);
    cout << "Enter the username of the user that ask to add a friend: ";
    string user1;
    cin >> user1;
    cout << "Enter the username of the user to add to the friendlist: ";
    string user2;
    cin >> user2;

    friendManager.addFriend(user1, user2);
    cout << endl;
    cout << "Friends of " << user1 << ":" << endl;
    vector<string> vec = friendManager.getFriends(user1);
    for (const string &user : vec) {
        cout << user << endl;
    }

    cout << endl;
    cout << "Enter the username of the user that ask to remove a friend: ";
    cin >> user1;
    cout << "Enter the username of the user to remove from the friendlist: ";
    cin >> user2;

    friendManager.removeFriend(user1, user2);

    cout << endl;
    cout << "Friends of " << user1 << ":" << endl;
    vec = friendManager.getFriends(user1);
    for (const string &user : vec) {
        cout << user << endl;
    }

    vector<pair<string, int>> ranking = dbManager->getRanking();
    cout << endl;
    cout << "Ranking:" << endl;
    for (const pair<string, int> &user : ranking) {
        cout << user.first << " - " << user.second << endl;
    }

    cout << "Enter name of user to delete : ";
    cin >> user1;
    accountManager.deleteAccount(user1);

    return 0;
}
