/** 
* @file Messages_manager.hpp
* @brief Messages Manager class definition
**/

#ifndef MESSAGE_MANAGER_HPP
#define MESSAGE_MANAGER_HPP

#include <memory>
#include <iostream>
#include <fstream> 
#include <sqlite3.h>

#include "../database_manager/database_manager.hpp"

using namespace std;

class MessagesManager{

    private: 
        shared_ptr<DatabaseManager> dbManager_;
        /*
        * @brief generate a file Name, this file will contain the discussion between the two users 
        * 
        * @param idUser1 Id of the first user
        * @param idUser2 Id of the second user
        * 
        * @return a file name 
        */
        string generateFileName(int idUser1, int idUser2 );
        /*
        * @brief create a file for a discussion  
        * 
        * @param filePath : the path of the file which will be created
        * @return true if there has been no error
        */
        bool createDiscussionFile(const string& filePath);

        /*
        *@brief add and create a new discussion between two users
        * @param idUser1 Id of the first user
        * @param idUser2 Id of the second user
        * 
        * @return true if there has been no error
        *  
        */

        bool addDiscussion(int idUser1, int idUser2); 
        /*
        *
        *@brief check if there is a discussion between two users 
        * @param idUser1 Id of the first user
        * @param idUser2 Id of the second user
        * 
        * @return true if there is any discussion and false is not  
        *  
        */
        bool isThereDiscussion(int idUser1, int idUser2 );  

        /*
        *@brief return the discussion pathfile between user 1 and user 2 
        *( private because MessagesManager must be the only one to have access to it )
        *
        */
        string getDiscussion(int idUser1, int idUser2);

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
        * @param content the content of the messages 
        * 
        **/
        void  sendMessage(const int senderId, const int recieverId, const string &content); 
        
        void writeMessage(const string &pathfile, const string &content, const int senderId);

        void readDiscussion(const string &pathfile);

        void showAllMessages(const int & idUser1, const int & idUser2);

        /**
         * @brief read all messages between two users 
         * 
         * @param  user1_id  Id of the first user
         * @param user2_id Id of the second user
         * 
         * @return vector of all messages between user1 and user2
         */
        vector<string> getAllMessage(const int user1_id , const int user2_id); 

        void markMessageAsRead(const int& messageId);


}; 

#endif