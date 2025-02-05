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
    friendManager.getFriends(user1);

    return 0;
}
