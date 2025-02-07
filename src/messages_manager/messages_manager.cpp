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

    //for the moment I store messages in columns which leads to a limit on the size of messages (which is large).
    // to see if this way won't cause performance problems. 
    //https://www.quora.com/What-is-the-maximum-allowed-number-of-bytes-in-one-SQLite-column

    //Do I have to give the date for each message?
    dbManager_->createTables("CREATE TABLE IF NOT EXISTS messages ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "senderId INTEGER NOT NULL, "
                        "receiverId INTEGER NOT NULL, "
                        "content TEXT NOT NULL, "
                        "isRead BOOLEAN DEFAULT 0, "
                        "FOREIGN KEY (senderId) REFERENCES users(id), "
                        "FOREIGN KEY (receiverId) REFERENCES users(id)) ");
}



void MessagesManager::sendMessage(const int senderId, const int recieverId,  const string &content){
    //Todo : have to check if recieverId exist and return a bool if the message has been received or not  
    dbManager_->executeSqlChangeData("INSERT INTO messages (senderId, receiverId, content) VALUES (?, ?, ?);", {senderId, recieverId, content});
}
 

