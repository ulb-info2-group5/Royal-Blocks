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

#include "../../../../lib/glaze/include/glaze/glaze.hpp"
#include "../database_manager/database_manager.hpp"


using namespace std;



struct Message {
    int senderId; 
    string content;
    // reflect is used to read a json, because Glaze cannot automatically guess where to put the Json values 
    template <typename T>
    void reflect(T& t) {
        t("senderId", senderId, "content", content);
    }
};

struct Discution{
    int idUser1;  
    int idUser2;
    std::vector<Message> messages;

    template <typename T>
    void reflect(T& t) {
        t("idUser1", idUser1, "idUser2", idUser2, "messages", messages);
    }
};


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
        string generateFileName(const int &idUser1, const int &idUser2 );
        /*
        * @brief create a file for a discussion  
        * 
        * @param filePath : the path of the file which will be created
        * @return true if there has been no error
        */
        bool createDiscussionFile(const string& filePath, Discution discussion);

        /*
        *@brief add and create a new discussion between two users
        * @param idUser1 Id of the first user
        * @param idUser2 Id of the second user
        * 
        * @return true if there has been no error
        *  
        */

        bool addDiscussion(const int &idUser1,const  int &idUser2); 
        /*
        *
        *@brief check if there is a discussion between two users managing the case where the discussion exists on the table but the file containing 
        * the discussion no longer exists or does not exist
        * @param idUser1 Id of the first user
        * @param idUser2 Id of the second user
        * 
        * @return true if there is any discussion and false is not  
        *  
        */
        bool isThereDiscussion(const int &idUser1,const int &idUser2 );  

        /*
        *@brief return the discussion pathfile between user 1 and user 2 
        *( private because MessagesManager must be the only one to have access to it )
        *
        */
        string getPathDiscussion(const int &idUser1,const int &idUser2);

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
        * @brief send a messages to a user
        *
        * @param senderId Id of the sender user
        * @param recieverId Id of the reciever user
        * 
        * @param content the content of the messages 
        * 
        **/
        void  sendMessage(const int &senderId, const int &recieverId, const string &content); 
        
        void writeMessage(const string &pathfile, const Message& message);

        void readDiscussion(const string &pathfile);

        void showAllMessages(const int & idUser1, const int & idUser2);

        /**
         * @brief return the discussion between two users  
         * 
         * @param  user1_id  Id of the first user
         * @param user2_id Id of the second user
         * 
         * @return vector of all messages between user1 and user2
         */
        Discution getDiscussion(const int &idUser1 , const int &idUser2); 

        /*
        * @brief finds all users who have a discussion with the user : idUser
        * @param IdUser the user 
        *
        * @return vector of all users who have a discussion with idUser  
        */
        vector<int> getAllUser(const int& idUser);


}; 




#endif