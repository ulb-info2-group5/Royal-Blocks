/**
 * @file Messages_manager.hpp
 * @brief Messages Manager class definition
 **/

#ifndef MESSAGE_MANAGER_HPP
#define MESSAGE_MANAGER_HPP

#include "../../common/bindings/conversation.hpp"

#include "../database_manager/database_manager.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include <sqlite3.h>

class MessagesManagerTest;

struct Message {
    int senderId;
    std::string content;
    nlohmann::json to_json() const {
        return nlohmann::json{{"senderId", senderId}, {"content", content}};
    }
    static Message from_json(const nlohmann::json &j) {
        return Message{{j.at("senderId").get<int>()},
                       {j.at("content").get<std::string>()}};
    }
};

struct Discussion {
    int idUser1;
    int idUser2;
    std::vector<Message> messages;
    nlohmann::json to_json() const {
        nlohmann::json jsonsms = nlohmann::json::array();
        for (auto &message : messages) {
            jsonsms.push_back(message.to_json());
        }
        return nlohmann::json{
            {"idUser1", idUser1}, {"idUser2", idUser2}, {"messages", jsonsms}};
    }
    static Discussion from_json(const nlohmann::json &j) {
        Discussion d;
        d.idUser1 = j.at("idUser1").get<int>();
        d.idUser2 = j.at("idUser2").get<int>();

        for (const auto &msg_json : j.at("messages")) {
            d.messages.push_back(Message::from_json(msg_json));
        }
        return d;
    }
};

class MessagesManager {

  private:
    std::shared_ptr<DatabaseManager> dbManager_;
    /*
     * @brief generate a file Name, this file will contain the discussion
     * between the two users
     *
     * @param idUser1 Id of the first user
     * @param idUser2 Id of the second user
     *
     * @return a file name
     */
    std::string generateFileName(const int &idUser1, const int &idUser2);
    /*
     * @brief create a file for a discussion
     *
     * @param filePath : the path of the file which will be created
     * @return true if there has been no error
     */
    bool createDiscussionFile(const std::string &filePath);

    /*
     *@brief add and create a new discussion between two users
     * @param idUser1 Id of the first user
     * @param idUser2 Id of the second user
     *
     * @return true if there has been no error
     *
     */

    bool addDiscussion(const int &idUser1, const int &idUser2);
    /*
     *
     *@brief check if there is a discussion between two users managing the case
     *where the discussion exists on the table but the file containing the
     *discussion no longer exists or does not exist
     * @param idUser1 Id of the first user
     * @param idUser2 Id of the second user
     *
     * @return true if there is any discussion and false is not
     *
     */
    bool isThereDiscussion(const int &idUser1, const int &idUser2);

    /*
     *@brief return the discussion pathfile between user 1 and user 2
     *( private because MessagesManager must be the only one to have access to
     *it )
     *
     */
    std::string getPathDiscussion(const int &idUser1, const int &idUser2);

  public:
    /*
     * @brief Construct a new messagesManager object
     *
     * @param dbPath Path to the database file
     */
    MessagesManager(std::shared_ptr<DatabaseManager> &db);

    /*
     * @brief Destroy the messages Manager object
     */
    ~MessagesManager() = default;

    /**
     * @brief send a messages to a user
     *
     * @param senderId Id of the sender user
     * @param recieverId Id of the reciever user
     *
     * @param content the content of the messages
     *
     **/
    void addMessage(const int &senderId, const int &recieverId,
                     const std::string &content);

    void writeMessage(const std::string &pathfile, const Message &message);

    void readDiscussion(const std::string &pathfile);

    void showAllMessages(const int &idUser1, const int &idUser2);

    /**
     * @brief return the discussion between two users
     *
     * @param  user1_id  Id of the first user
     * @param user2_id Id of the second user
     *
     * @return vector of all messages between user1 and user2
     */
    bindings::Conversation getDiscussion(const int &idUser1, const int &idUser2);

    /*
     * @brief finds all users who have a discussion with the user : idUser
     * @param IdUser the user
     *
     * @return vector of all users who have a discussion with idUser
     */
    std::vector<int> getAllUser(const int &idUser);

    std::vector<bindings::Conversation> getAllDiscusions(const int & idUser);


    friend MessagesManagerTest;
};

#endif
