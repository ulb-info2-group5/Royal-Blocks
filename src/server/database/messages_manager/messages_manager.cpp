/**
 * @file messages_manager.cpp
 *
 * @brief Friends Manager class definition
 * 
 *
 */

#include "messages_manager.hpp"
#include <iostream>
#include <ostream>
#include <string>




//==== Constructor ===
MessagesManager::MessagesManager(shared_ptr<DatabaseManager> &db) : dbManager_(db) {
    dbManager_->createTables( "CREATE TABLE IF NOT EXISTS userMessages ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "user1_id INTEGER NOT NULL, "
                              "user2_id INTEGER NOT NULL, "
                              "file_path TEXT NOT NULL, "
                              "FOREIGN KEY (user1_id) REFERENCES users(id), "
                              "FOREIGN KEY (user2_id) REFERENCES users(id));");
}

// ==== Private ====
string MessagesManager::generateFileName(int idUser1, int idUser2 ){
    return "../data/chat/user" + std::to_string(idUser1) + "_user" + std::to_string(idUser2) + ".txt";
}

bool createDiscussionFile(const std::string& filePath) {
    std::ofstream file(filePath);
    if (!file) {
        std::cerr << "Erreur : impossible de créer le fichier " << filePath << std::endl;
        return false;
    }
    file.close();
    return true;
}



bool MessagesManager::addDiscussion(int idUser1, int idUser2){
    string filePath = generateFileName(idUser1, idUser2);
    
    if (!createDiscussionFile(filePath) ) return false;
    
    const char * sqlRe = "INSER INTO createDiscussionFile (idUser1, idUser2, filePath) VALEUE (?, ?, ?);";
    if (!dbManager_->executeSqlChangeData(sqlRe, {idUser1, idUser2, filePath}) ) return false ;

    cout << "a conversation has been created between " << idUser1 << "and "<< idUser2 << endl;
    return true;
}


bool MessagesManager::isThereDiscussion(int idUser1, int idUser2 ){
    string checkSQL = "SELECT file_path FROM userMessages WHERE (user1_id = ? AND user2_id = ?) OR (user1_id = ? AND user2_id = ?)";
    int count = 0;
    return dbManager_->executeSqlRecoveryInt(checkSQL, {idUser1, idUser2, idUser2, idUser1}, count) && count > 0;
}

// ==== Public ====


void MessagesManager::sendMessage(const int senderId, const int recieverId, const string &content = "Message"){
    if (!isThereDiscussion(senderId, recieverId)){
        addDiscussion(senderId, recieverId);
    }

}
 

