#include "messaging.hpp"

#include <cstdlib>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/mouse.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <map>
#include <memory>
#include <string>
#include <vector>


using namespace ftxui;

Messaging::Messaging(std::shared_ptr<ftxui::ScreenInteractive> &screen, const std::vector<std::string>& friends) : screen_(screen), friends_(friends) {
    initMessaging();
}

void Messaging::initMessaging(){
    for (const string& friend_name : friends_) {
        conversations[friend_name] = {Message{1, friend_name + " : test bonjour "} };
    }
}

MessagingState Messaging::render(){
    MessagingState res = MessagingState::NONE;

    //
    Component friends_menu = Menu(&friends_, &selectedFriend);

    //
    Component addFriendInput = Input(&newFriend, "Nom de l'ami");
    //attempt to send the result when  user press enter

    // addFriendInput |= CatchEvent([&](ftxui::Event event) {
    //     if ( event == event.Return) {
    //         if (!newFriend.empty()) {
    //         }
             
    //     }
    // });

    Component addFriendButton = Button("Ajouter un ami", [&] {
        if (!newFriend.empty()) {
            friends_.push_back(newFriend);
            conversations[newFriend] = {}; 
            newFriend.clear();
        }
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0));



    Component messageInput = Input(&newMessage, "Écrire un message...") | center | border;


    Component sendButton = Button("Envoyer", [&] {
        if (!newMessage.empty() && !friends_.empty()) { 
            addMessage(newMessage);
        }
    }) | center;


    Component buttonBack = ftxui::Button("Back", [&] {
        newMessage.clear();
        newFriend.clear();
        res = MessagingState::BACK;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0));

    Component sidebar = Container::Vertical({
        friends_menu,
    });

    Component addMenue = Container::Vertical({
      addFriendInput,
        addFriendButton,
        buttonBack,
    });

    Component chatDisplay = Renderer([&] {
        Elements chat_elements;
        if (!friends_.empty()) {
            for (const Message &msg : conversations[friends_[static_cast<size_t>(selectedFriend)]]) {
                if (msg.idSender != userId){
                    chat_elements.push_back(text(msg.message) | bold | color(Color::Yellow));
                }else {
                    chat_elements.push_back(text(msg.message) | bold | color(Color::DarkCyan));
                }
                
            }
        }
        return vbox(chat_elements) | flex ;
    });

    Component main_container = Container::Horizontal({
        sidebar,
        Container::Vertical({
            chatDisplay,
            messageInput,
            sendButton,
        }),
        addMenue,
    });

    Component render = Renderer(main_container, [&] {
        return hbox({
            vbox({
                text(" --- LISTE AMIS --- ") | bold | color(Color::Green) | center,
                separator(),
                friends_menu->Render(),
                
            }) | border,


            vbox({
                text(" --- CONVERSATION --- ") | bold | color(Color::Green) | center,
                separator(),
                chatDisplay->Render() | flex,
                separator(),
                messageInput->Render(),
                separator(),
                sendButton->Render(),
            }) | border | flex,
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
        }) | border;
    });

    screen_->Loop(render);
    return res;
}

void Messaging::addMessage(const string &message){
    conversations[friends_[static_cast<size_t>(selectedFriend)]].push_back(Message{userId, message});
    newMessage.clear();
}