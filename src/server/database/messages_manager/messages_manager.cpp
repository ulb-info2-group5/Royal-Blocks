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
string MessagesManager::generateFileName(const int &idUser1,const int &idUser2 ){
    return "data/chat/user" + std::to_string(idUser1) + "_user" + std::to_string(idUser2) + ".json";
}

bool MessagesManager::createDiscussionFile(const string& filePath) {
    std::ofstream file(filePath);
    if (!file) {
        std::cerr << "file error" << filePath << std::endl;
        return false;
    }
    file.close();
    return true;
}



bool MessagesManager::addDiscussion(const int &idUser1,const  int &idUser2){
    const string filePath = generateFileName(idUser1, idUser2);
    
    if (!this->createDiscussionFile(filePath) ) return false;
    
    const char * sqlRe = "INSERT INTO userMessages (user1_id, user2_id, file_path) VALUES (?, ?, ?);";
    if (!dbManager_->executeSqlChangeData(sqlRe, {idUser1, idUser2, filePath}) ) return false ;

    cout << "a conversation has been created between " << idUser1 << " and "<< idUser2 << endl;
    return true;
}


bool MessagesManager::isThereDiscussion(const int &idUser1, const int &idUser2 ){
    string sql = "SELECT COUNT(*) FROM userMessages WHERE (user1_id = ? AND user2_id = ?) OR (user1_id = ? AND user2_id = ?)";
    int count = 0;
    return dbManager_->executeSqlRecoveryInt(sql, {idUser1, idUser2, idUser2, idUser1}, count)&& count > 0;
}


string MessagesManager::getDiscussion(const int &idUser1, const int &idUser2){
    string sql = "SELECT file_path FROM userMessages WHERE (user1_id = ? AND user2_id = ?) OR (user1_id = ? AND user2_id = ?);";
    string discussionFile;
    dbManager_->executeSqlRecoveryString(sql, {idUser1, idUser2, idUser2, idUser1}, discussionFile );
    return discussionFile;
}



void MessagesManager::writeMessage(const string &pathfile, const Message& message){
    std::ifstream infile(pathfile); 
    string discussion;    
    if (infile) {
        stringstream buffer;
        buffer << infile.rdbuf();
        discussion = buffer.str();
    }
    vector<Message> messages;
    if (!discussion.empty()) {
        glz::error_ctx err = glz::read_json(messages, discussion);
        if (err) {
            std::cerr << "error readJSON : " << glz::format_error(err, discussion) << std::endl;
        }  
    }
    messages.push_back(message);
    auto result = glz::write_json(messages);
    if (!result) {
        std::cerr << "erpror eerr error write JSON : " << glz::format_error(result.error()) << std::endl;
    } else {
        discussion = result.value();  
    }
    std::ofstream outfile(pathfile);
    outfile << discussion;
}



// ==== Public ====

void MessagesManager::sendMessage(const int &senderId, const int &recieverId, const string &content){
    if (!isThereDiscussion(senderId, recieverId)) addDiscussion(senderId, recieverId);
    writeMessage(getDiscussion(senderId, recieverId),{senderId, content});
}


void MessagesManager::showAllMessages(const int &idUser1, const int &idUser2){
    readDiscussion(getDiscussion(idUser1, idUser2));    
}



void MessagesManager::readDiscussion(const string &pathfile){
    ifstream f(pathfile);
    string s;
    while (getline(f, s)) cout << s << endl;
    f.close();
}

