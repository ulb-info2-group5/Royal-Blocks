#ifndef MESSAGESING_HPP
#define MESSAGESING_HPP

#include <ftxui/component/screen_interactive.hpp>
#include <memory>
#include <vector>
#include <map>

using namespace std;

/**
 * @brief Enum class to represent the state of the messaging
 * 
 */
enum class MessagingState {
    BACK,
    NONE,
};

struct Message {
    int idSender; 
    std::string message; 
};

class Messaging {
    private :  
        /*
        * @brief The screen to use to render the components
        */
        std::shared_ptr<ftxui::ScreenInteractive> screen_;

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
        *
        * @param screen The screen to use to render the components
        * @param friends The list of friends to display in the messaging screen
        */
        Messaging(std::shared_ptr<ftxui::ScreenInteractive> &screen, const std::vector<std::string>& friends) ; 

        /*
        * @brief Destroy the Messaging object
        */
        ~Messaging() = default;

        /*
        * @brief Render the messaging screen with all the components
        *
        * @return MessagingState The state of the messaging screen
        */
        MessagingState render();
        
        void addFriends(string friendName);
        
        /*
        * @brief add a message to a discussion
        */
        void addMessage(const string &message);
};

#endif 