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




//==== Constructor ====
MessagesManager::MessagesManager(std::shared_ptr<DatabaseManager> &db) : dbManager_(db) {
    dbManager_->createTables( "CREATE TABLE IF NOT EXISTS userMessages ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "user1_id INTEGER NOT NULL, "
                              "user2_id INTEGER NOT NULL, "
                              "file_path TEXT NOT NULL, "
                              "FOREIGN KEY (user1_id) REFERENCES users(id), "
                              "FOREIGN KEY (user2_id) REFERENCES users(id));");
}

// ==== Private ====
std::string MessagesManager::generateFileName(const int &idUser1,const int &idUser2 ){
    return "data/chat/user" + std::to_string(idUser1) + "_user" + std::to_string(idUser2) + ".json";
}

bool MessagesManager::createDiscussionFile(const std::string& filePath, Discution discussion) {
    std::ofstream file(filePath);
    if (!file) {
        std::cerr << "file error" << filePath << std::endl;
        return false;
    }
    nlohmann::json discuJson = discussion.to_json();
    std::cout << "discution -> tojson : " << discuJson.dump() << std::endl; 
    file << discuJson;  
    return true;
}



bool MessagesManager::addDiscussion(const int &idUser1,const  int &idUser2){
    const std::string filePath = generateFileName(idUser1, idUser2);
    Discution discussion;
    discussion.idUser1 = idUser1; 
    discussion.idUser2 = idUser2;
    discussion.messages = {};
    if (!this->createDiscussionFile(filePath, discussion) ) return false;
    
    const char * sqlRe = "INSERT INTO userMessages (user1_id, user2_id, file_path) VALUES (?, ?, ?);";
    if (!dbManager_->executeSqlChangeData(sqlRe, {idUser1, idUser2, filePath}) ) return false ;

    std::cout << "a conversation has been created between " << idUser1 << " and "<< idUser2 << std::endl;
    return true;
}


bool MessagesManager::isThereDiscussion(const int &idUser1, const int &idUser2 ){
    std::string sql = "SELECT COUNT(*) FROM userMessages WHERE (user1_id = ? AND user2_id = ?) OR (user1_id = ? AND user2_id = ?)";
    int count = 0;
    //check if the discussion exists on the table 
     if (!dbManager_->executeSqlRecoveryInt(sql, {idUser1, idUser2, idUser2, idUser1}, count)&& count > 0) {
        return false ; 
     }else{
        //check if the discussion file exists (json file)
        return std::filesystem::exists("data/chat/user" + std::to_string(idUser1) + "_user" + std::to_string(idUser2) + ".json")
         || std::filesystem::exists("data/chat/user" + std::to_string(idUser2) + "_user" + std::to_string(idUser1) + ".json");
     }
}


std::string MessagesManager::getPathDiscussion(const int &idUser1, const int &idUser2){
    std::string sql = "SELECT file_path FROM userMessages WHERE (user1_id = ? AND user2_id = ?) OR (user1_id = ? AND user2_id = ?);";
    std::string discussionFile;
    dbManager_->executeSqlRecoveryString(sql, {idUser1, idUser2, idUser2, idUser1}, discussionFile );
    return discussionFile;
}



void MessagesManager::writeMessage(const std::string &pathfile, const Message& message){
    
    std::ifstream infile(pathfile); 
   
   
    nlohmann::json jsondiscu = nlohmann::json::parse(infile);    
    std::cout << jsondiscu.dump()<< std::endl; 
    Discution discussion = Discution::from_json(jsondiscu);
    discussion.messages.push_back(message);
    std::ofstream outfile(pathfile);
    outfile << discussion.to_json().dump();


}



// ==== Public ====

void MessagesManager::sendMessage(const int &senderId, const int &recieverId, const std::string &content){
    if (!isThereDiscussion(senderId, recieverId)) addDiscussion(senderId, recieverId);
    
    writeMessage(getPathDiscussion(senderId, recieverId),{senderId, content});
}

// Discution MessagesManager::getDiscussion(const int &idUser1 , const int &idUser2){
//     std::ifstream infile(getPathDiscussion(idUser1, idUser2));
//     if (!infile) {
//         std::cerr << "error open json file (ifstream) !" << std::endl;
//     }
//     //https://app.studyraid.com/en/read/12316/397451/secure-json-parsing-practices
//     const std::string content((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
//     Discution discussion;
//     auto result = glz::read_json(discussion, content);

//     // if (!result) {
//     //     throw std::runtime_error("error glz read_json ");
//     // }
//     return discussion;
// }