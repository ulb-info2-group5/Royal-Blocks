/** 
* @file Messages_manager.hpp
* @brief Messages Manager class definition
**/

#ifndef MESSAGE_MANAGER_HPP
#define MESSAGE_MANAGER_HPP

#include <memory>
#include <sqlite3.h>

#include "../database_manager/database_manager.hpp"

using namespace std;

class MessagesManager{

    private: 
        shared_ptr<DatabaseManager> dbManager_;

    public: 
        /*
        * @brief Construct a new messagesManager object
        * 
        * @param dbPath Path to the database file
        */
        MessagesManager(shared_ptr<DatabaseManager> &db);

        /*
        * @brief Destroy the messages Manager object
        */
        ~MessagesManager() = default;

        /**
        * @brief send a messages 
        *
        * @param senderId Id of the sender user
        * @param recieverId Id of the reciever user
        * 
        **/
        void  sendMessage(const int senderId, const int recieverId, const string &content); 

        

        

        /**
         * @brief read all messages between two users 
         * 
         * @param  user1_id  Id of the first user
         * @param user2_id Id of the second user
         * 
         * @return vector of all messages between user1 and user2
         */
        vector<string> getAllMessage(const int user1_id , const int user2_id); 
        //void MessagesManager::markMessageAsRead(const int& messageId);


}; 

#endif