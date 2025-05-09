#include "messages_manager.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>

#include "../../../common/bindings/conversation.hpp"
#include "database_manager/database_manager.hpp"

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
std::string MessagesManager::generateFileName(const UserID &user1ID,
                                              const UserID &user2ID) {
    return CHAT_PATH + std::to_string(user1ID) + "_user"
           + std::to_string(user2ID) + ".json";
}

bool MessagesManager::createDiscussionFile(const std::string &filePath) {
    std::ofstream file(filePath);
    if (!file) {
        std::cerr << "file error" << filePath << std::endl;
        return false;
    }
    nlohmann::json discuJson = bindings::Conversation{}.to_json();

    file << discuJson;
    return true;
}

bool MessagesManager::addDiscussion(const UserID &user1ID,
                                    const UserID &user2ID) {
    const std::string filePath = generateFileName(user1ID, user2ID);
    if (!this->createDiscussionFile(filePath)) return false;

    const char *sqlRe = "INSERT INTO userMessages (user1_id, user2_id, "
                        "file_path) VALUES (?, ?, ?);";
    if (!dbManager_->executeSqlChangeData(sqlRe, {user1ID, user2ID, filePath}))
        return false;

    return true;
}

std::string MessagesManager::getPathDiscussion(const UserID &user1ID,
                                               const UserID &user2ID) {
    std::string sql = "SELECT file_path FROM userMessages WHERE (user1_id = ? "
                      "AND user2_id = ?) OR (user1_id = ? AND user2_id = ?);";
    std::string discussionFile;
    dbManager_->executeSqlRecoveryString(
        sql, {user1ID, user2ID, user2ID, user1ID}, discussionFile);
    return discussionFile;
}

void MessagesManager::writeMessage(const std::string &pathfile,
                                   const Message &message) {
    std::ifstream infile(pathfile);
    if (!infile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    nlohmann::json jsondiscu;
    try {
        jsondiscu = nlohmann::json::parse(infile);
    } catch (const std::runtime_error &e) {
        std::cerr << "Received packet is not valid JSON: " << e.what()
                  << std::endl;
        return;
    }

    bindings::Conversation discussion =
        bindings::Conversation::from_json(jsondiscu);
    discussion.senderMessages.push_back(
        SenderMessage{message.senderID, message.content});

    std::ofstream outfile(pathfile);
    outfile << discussion.to_json().dump();
}

// ==== Public ====

void MessagesManager::addMessage(const UserID &senderID,
                                 const UserID &recieverID,
                                 const std::string &content) {
    if (senderID == recieverID) {
        return;
    }

    if (!isThereDiscussion(senderID, recieverID)) {
        addDiscussion(senderID, recieverID);
    }
    writeMessage(getPathDiscussion(senderID, recieverID), {senderID, content});
}

bool MessagesManager::isThereDiscussion(const UserID &user1ID,
                                        const UserID &user2ID) {
    std::string sql = "SELECT COUNT(*) FROM userMessages WHERE (user1_id = ? "
                      "AND user2_id = ?) OR (user1_id = ? AND user2_id = ?)";
    int count = 0;
    // check if the discussion exists on the table

    if (!(dbManager_->executeSqlRecoveryInt(
              sql, {user1ID, user2ID, user2ID, user1ID}, count)
          && count > 0)) {
        return false;
    } else {
        // check if the discussion file exists (json file)
        return std::filesystem::exists(CHAT_PATH + std::to_string(user1ID)
                                       + "_user" + std::to_string(user2ID)
                                       + ".json")
               || std::filesystem::exists(CHAT_PATH + std::to_string(user2ID)
                                          + "_user" + std::to_string(user1ID)
                                          + ".json");
    }
}

std::vector<int> MessagesManager::getAllUser(const UserID &userID) {
    std::string sql = "SELECT user1_id, user2_id FROM userMessages WHERE "
                      "user1_id = ? OR user2_id = ?";
    return dbManager_->getVectorInfo(sql, userID);
}

std::optional<bindings::Conversation>
MessagesManager::getDiscussion(const UserID &user1ID, const UserID &user2ID) {
    std::ifstream infile(getPathDiscussion(user1ID, user2ID));
    if (!infile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return std::nullopt;
    }

    nlohmann::json jsondiscu;
    try {
        jsondiscu = nlohmann::json::parse(infile);
    } catch (const std::runtime_error &e) {
        std::cerr << "Received packet is not valid JSON: " << e.what()
                  << std::endl;
        return std::nullopt;
    }

    bindings::Conversation discussion =
        bindings::Conversation::from_json(jsondiscu);
    return discussion;
}

std::vector<bindings::Conversation>
MessagesManager::getAllDiscusions(const UserID &userID) {
    std::vector<bindings::Conversation> allDiscussions;
    for (auto id : getAllUser(userID)) {
        std::optional<bindings::Conversation> optConversation =
            getDiscussion(userID, id);
        if (optConversation.has_value()) {
            allDiscussions.push_back(optConversation.value());
        }
    }
    return allDiscussions;
}
