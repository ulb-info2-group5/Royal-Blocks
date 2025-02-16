#ifndef MESSAGESING_HPP
#define MESSAGESING_HPP

#include <ftxui/component/screen_interactive.hpp>
#include <vector>
#include <map>
#include "../screen_manager.hpp"

using namespace std;


struct Message {
    int idSender; 
    std::string message; 
};

class Messaging {
    private :  

        ScreenManager *screenManager_;
        std::map<std::string, std::vector<Message>> conversations;
        std::vector<std::string> friends_;
        int selectedFriend = 0;
        std::string newFriend;
        std::string newMessage;

        //just to simulate a user ID 
        int userId = 5;
        void initMessaging();

    public : 
        /*
        * @brief Construct a new Messaging object
        */
        Messaging(ScreenManager *screenManager, const std::vector<std::string>& friends) ; 

        /*
        * @brief Destroy the Messaging object
        */
        ~Messaging() = default;

        /*
        * @brief Render the messaging screen with all the components by asking the screen manager to render the components
        */
        void render();
        
        void addFriends(string friendName);
        
        /*
        * @brief add a message to a discussion
        */
        void addMessage(const string &message);
};

#endif 