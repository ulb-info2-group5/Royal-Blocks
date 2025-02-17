#include "messaging.hpp"

#include <cstdlib>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/mouse.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <memory>
#include <string>
#include <vector>

using namespace ftxui;

Messaging::Messaging(std::shared_ptr<ftxui::ScreenInteractive> &screen, const std::vector<std::string>& friends) : screen_(screen), friends_(friends) {
    initMessaging();
}

void Messaging::initMessaging(){
    for (const auto& friend_name : friends_) {
        conversations[friend_name] = {Message{1, friend_name + " : test bonjour "} };
    }
}

MessagingState Messaging::render(){
    MessagingState res = MessagingState::NONE;

    //
    auto friends_menu = Menu(&friends_, &selectedFriend);

    //
    auto addFriendInput = Input(&newFriend, "Nom de l'ami");
    auto addFriendButton = Button("Ajouter un ami", [&] {
        if (!newFriend.empty()) {
            friends_.push_back(newFriend);
            conversations[newFriend] = {}; 
            newFriend.clear();
        }
    }, ftxui::ButtonOption::Animated());



    auto messageInput = Input(&newMessage, "Écrire un message...") | center;
    auto sendButton = Button("Envoyer", [&] {
        if (!newMessage.empty() && !friends_.empty()) { 
            addMessage(newMessage);
        }
    }) | center;


    auto buttonBack = ftxui::Button("Back", [&] {
        newMessage.clear();
        newFriend.clear();
        res = MessagingState::BACK;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated());

    auto sidebar = Container::Vertical({
        friends_menu,
    });

    auto addMenue = Container::Vertical({
      addFriendInput,
        addFriendButton,
        buttonBack,
    });

    auto chatDisplay = Renderer([&] {
        Elements chat_elements;
        if (!friends_.empty()) {
            for (const auto& msg : conversations[friends_[static_cast<size_t>(selectedFriend)]]) {
                if (msg.idSender != userId){
                    chat_elements.push_back(text(msg.message) | bold | color(Color::Yellow));
                }else {
                    chat_elements.push_back(text(msg.message) | bold | color(Color::DarkCyan));
                }
                
            }
        }
        return vbox(chat_elements) | flex ;
    });

    auto main_container = Container::Horizontal({
        sidebar,
        Container::Vertical({
            chatDisplay,
            messageInput,
            sendButton,
        }),
        addMenue,
    });

    auto render = Renderer(main_container, [&] {
        return hbox({
            vbox({
                text(" --- LISTE AMIS --- ") | bold | color(Color::Green) | center,
                separator(),
                friends_menu->Render(),
                
            }) | border,

            separator(),

            vbox({
                text(" --- CONVERSATION --- ") | bold | color(Color::Green) | center,
                separator(),
                chatDisplay->Render() | flex,
                separator(),
                messageInput->Render(),
                separator(),
                sendButton->Render(),
            }) | border | flex,
            separator(),
            vbox({
              text("-- Ajouter un ami --") | bold | color(Color::Green) | center,
                separator(),
                addFriendInput->Render(),
                separator(),
                addFriendButton->Render(),
                separator(),

                buttonBack->Render(),
                separator(),
            }) | border,

        });
    });

    screen_->Loop(render);

    return res;
}

void Messaging::addMessage(const string &message){
    conversations[friends_[static_cast<size_t>(selectedFriend)]].push_back(Message{userId, message});
    newMessage.clear();
}