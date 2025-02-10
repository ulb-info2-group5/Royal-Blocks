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
#include "messages_manager/messages_manager.hpp"
#include <iostream>
#include <ostream>
#include <vector>
#include <memory>

using namespace std;

/*
*@brief just for show a discussion between two users 
*/
void printDiscussion(Discution discussion, AccountManager &accountmanager){
    std::cout << "====="<< std::endl;
    for (const auto& message : discussion.messages) {
        std::cout << "User " << accountmanager.getUsername(message.senderId) << ": " << message.content << std::endl;
    }
}


int main() {
    shared_ptr<DatabaseManager> dbManager = make_shared<DatabaseManager>();

    AccountManager accountManager(dbManager);
    FriendsManager friendsManager(dbManager);
    MessagesManager messagesManager(dbManager);


    cout << "=== Test du module AccountManager ===" << endl;
    accountManager.launch();

    string username;
    cout << "Entrez votre nom d'utilisateur : ";
    cin >> username;
    int userId = accountManager.getUserId(username);

    if (userId == -1) {
        cerr << "Erreur : Impossible de récupérer l'ID de l'utilisateur." << endl;
        return 1;
    }
    cout << "ID de l'utilisateur " << username << " : " << userId << endl;

    cout << endl;
    cout << "=== Test du module MessagesManager ===" << endl;
    string reciever;
    cout << "who receives the message ?" << endl;
    cin >> reciever;
    cout << endl;
    messagesManager.sendMessage(userId, accountManager.getUserId(reciever), "message de test de " + username + " pour " + reciever );
    cout << "this is all your discussion : " << endl;
    printDiscussion(messagesManager.getDiscussion(userId, accountManager.getUserId(reciever)), accountManager);

    cout << "=== Test du module FriendsManager ===" << endl;
    string friendName;
    cout << "Entrez un nom d'utilisateur pour ajouter un ami : ";
    cin >> friendName;
    int friendId = accountManager.getUserId(friendName);

    if (friendId == -1) {
        cout << "L'utilisateur " << friendName << " n'existe pas" << endl;
    }

    if (friendsManager.addFriend(userId, friendId)) {
        cout << "Amitié ajoutée Test messages  messages avec succès entre " << username << " et " << friendName << "." << endl;
    } else {
        cout << "Erreur lors de l'ajout de l'ami." << endl;
    }

    cout << "Liste des amis de " << username << " :" << endl;
    vector<int> friends = friendsManager.getFriends(userId);
    for (int friendId : friends) {
        cout << accountManager.getUsername(friendId) << endl;
    }

    cout << endl;
    cout << "=== Test de mise à jour du score ===" << endl;
    int newScore;
    cout << "Entrez un score pour mettre à jour : ";
    cin >> newScore;
    accountManager.updateScore(userId, newScore);
    cout << "Score mis à jour !" << endl;

    return 0;
}
