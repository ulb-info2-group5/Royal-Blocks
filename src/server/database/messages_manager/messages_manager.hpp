#ifndef MESSAGE_MANAGER_HPP
#define MESSAGE_MANAGER_HPP

#include "../../common/bindings/conversation.hpp"

#include "../database_manager/database_manager.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include <sqlite3.h>

class MessagesManagerTest;

struct Message {
    UserID senderID;
    std::string content;
    nlohmann::json to_json() const {
        return nlohmann::json{{"senderId", senderID}, {"content", content}};
    }
    static Message from_json(const nlohmann::json &j) {
        return Message{(j.at("senderID").get<UserID>()),
                       (j.at("content").get<std::string>())};
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
    std::string generateFileName(const UserID& user1ID, const UserID& user2ID);
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

    bool addDiscussion(const UserID& user1ID, const UserID& user2ID);
    

    /*
     *@brief return the discussion pathfile between user 1 and user 2
     *( private because MessagesManager must be the only one to have access to
     *it )
     *
     */
    std::string getPathDiscussion(const UserID& user1ID, const UserID& user2ID);

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

    void addMessage(const UserID &senderID, const UserID &recieverID,
                     const std::string &content);
    
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
    bool isThereDiscussion(const UserID& user1ID, const UserID& user2ID);

    void writeMessage(const std::string &pathfile, const Message &message);

    void readDiscussion(const std::string &pathfile);

    void showAllMessages(const UserID& user1ID, const UserID& user2ID);

    /**
     * @brief return the discussion between two users
     *
     * @param  user1ID  Id of the first user
     * @param user2ID Id of the second user
     *
     * @return an optional conversation binding.
     */
    std::optional<bindings::Conversation> getDiscussion(const UserID& user1ID, const UserID& user2ID);

    /*
     * @brief finds all users who have a discussion with the user : idUser
     * @param IdUser the user
     *
     * @return vector of all users who have a discussion with idUser
     */
    std::vector<int> getAllUser(const UserID& userID);

    std::vector<bindings::Conversation> getAllDiscusions(const UserID& userID);


    friend MessagesManagerTest;
};

#endif
