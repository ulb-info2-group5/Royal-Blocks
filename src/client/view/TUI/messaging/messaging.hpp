#ifndef MESSAGESING_HPP
#define MESSAGESING_HPP

#include <ftxui/component/screen_interactive.hpp>
#include <memory>
#include <vector>
#include <tuple>
#include <map>

using namespace std;

class Messaging {
    private :  

        std::shared_ptr<ftxui::ScreenInteractive> screen_;
        std::map<std::string, std::vector<std::string>> conversations;
        std::vector<std::string> friends_;
        int selectedFriend = 0;
        std::string newFriend;
        std::string newMessage;

        void initMessaging();

    public : 
        Messaging(std::shared_ptr<ftxui::ScreenInteractive>& screen, std::vector<std::string>& friends) ; 
        void render();
        void addFriends(string friendName);
        void addMessage(string message);




};

#endif 