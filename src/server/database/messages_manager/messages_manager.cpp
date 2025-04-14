#include "messages_manager.hpp"

#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

#define CHAT_PATH "data/chat/user"

//==== Constructor ====
MessagesManager::MessagesManager(std::shared_ptr<DatabaseManager> &db)
    : dbManager_(db) {

    std::filesystem::path messagePath(CHAT_PATH);
    std::filesystem::path chatPath = messagePath.parent_path();
    if (!std::filesystem::exists(chatPath)) {
        std::filesystem::create_directories(chatPath);
    }

    dbManager_->createTables("CREATE TABLE IF NOT EXISTS userMessages ("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                             "user1_id INTEGER NOT NULL, "
                             "user2_id INTEGER NOT NULL, "
                             "file_path TEXT NOT NULL, "
                             "FOREIGN KEY (user1_id) REFERENCES users(id), "
                             "FOREIGN KEY (user2_id) REFERENCES users(id));");
}

// ==== Private ====
std::string MessagesManager::generateFileName(const int &idUser1,
                                              const int &idUser2) {
    return CHAT_PATH + std::to_string(idUser1) + "_user"
           + std::to_string(idUser2) + ".json";
}

bool MessagesManager::createDiscussionFile(const std::string &filePath) {
    std::ofstream file(filePath);
    if (!file) {
        std::cerr << "file error" << filePath << std::endl;
        return false;
    }
    nlohmann::json discuJson = bindings::Conversation{}.to_json();
    std::cout << "Discussion -> tojson : " << discuJson.dump() << std::endl;
    file << discuJson;
    return true;
}

bool MessagesManager::addDiscussion(const int &idUser1, const int &idUser2) {
    const std::string filePath = generateFileName(idUser1, idUser2);
    if (!this->createDiscussionFile(filePath)) return false;

    const char *sqlRe = "INSERT INTO userMessages (user1_id, user2_id, "
                        "file_path) VALUES (?, ?, ?);";
    if (!dbManager_->executeSqlChangeData(sqlRe, {idUser1, idUser2, filePath}))
        return false;

    std::cout << "a conversation has been created between " << idUser1
              << " and " << idUser2 << std::endl;
    return true;
}



std::string MessagesManager::getPathDiscussion(const int &idUser1,
                                               const int &idUser2) {
    std::string sql = "SELECT file_path FROM userMessages WHERE (user1_id = ? "
                      "AND user2_id = ?) OR (user1_id = ? AND user2_id = ?);";
    std::string discussionFile;
    dbManager_->executeSqlRecoveryString(
        sql, {idUser1, idUser2, idUser2, idUser1}, discussionFile);
    return discussionFile;
}

void MessagesManager::writeMessage(const std::string &pathfile,
                                   const Message &message) {
    
    std::ifstream infile(pathfile);
     

    nlohmann::json jsondiscu = nlohmann::json::parse(infile);
    bindings::Conversation discussion = bindings::Conversation::from_json(jsondiscu);
    discussion.senderMessages.push_back(SenderMessage{message.senderId, message.content});
    std::ofstream outfile(pathfile);
    outfile << discussion.to_json().dump();
}

// ==== Public ====

void MessagesManager::addMessage(const int &senderId, const int &recieverId,
                                  const std::string &content) {
    if (senderId == recieverId ){
        return ;
    }

    if (!isThereDiscussion(senderId, recieverId)){
        addDiscussion(senderId, recieverId);
    }    
    writeMessage(getPathDiscussion(senderId, recieverId), {senderId, content});
}


bool MessagesManager::isThereDiscussion(const int &idUser1,
                                        const int &idUser2) {
    std::string sql = "SELECT COUNT(*) FROM userMessages WHERE (user1_id = ? "
                      "AND user2_id = ?) OR (user1_id = ? AND user2_id = ?)";
    int count = 0;
    // check if the discussion exists on the table
    
    if (!(dbManager_->executeSqlRecoveryInt(sql, {idUser1, idUser2, idUser2, idUser1}, count) && count > 0)) {
        return false;
    } else {
        // check if the discussion file exists (json file)
        return std::filesystem::exists(CHAT_PATH
                                       + std::to_string(idUser1) + "_user"
                                       + std::to_string(idUser2) + ".json")
               || std::filesystem::exists(CHAT_PATH
                                          + std::to_string(idUser2) + "_user"
                                          + std::to_string(idUser1) + ".json");
    }
}

std::vector<int> MessagesManager::getAllUser(const int &idUser){
    std::string sql = "SELECT user1_id, user2_id FROM userMessages WHERE user1_id = ? OR user2_id = ?";
    return dbManager_->getVectorInfo(sql, idUser); 
}

bindings::Conversation MessagesManager::getDiscussion(const int &idUser1 , const int&idUser2){
    std::cout << "get path discussion (debug) => "<< getPathDiscussion(idUser1, idUser2) << std::endl;
    std::ifstream infile(getPathDiscussion(idUser1, idUser2));

    nlohmann::json jsondiscu = nlohmann::json::parse(infile);
    std::cout << "get conversation == " << jsondiscu.dump() << std::endl;
    bindings::Conversation discussion = bindings::Conversation::from_json(jsondiscu);
    return discussion;
}

std::vector<bindings::Conversation> MessagesManager::getAllDiscusions(const int & idUser){
    std::vector<bindings::Conversation> allDiscussions;
    for (auto id : getAllUser(idUser)){
        allDiscussions.push_back(getDiscussion(idUser, id));
    }
    return allDiscussions;
}