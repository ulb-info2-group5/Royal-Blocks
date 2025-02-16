#include "messaging.hpp"

#include <cstdlib>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/mouse.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>

using namespace ftxui;

Messaging::Messaging(ScreenManager *screenManager, const std::vector<std::string>& friends) : screenManager_(screenManager), friends_(friends) {
    initMessaging();
}

void Messaging::initMessaging(){
    for (const auto& friend_name : friends_) {
        conversations[friend_name] = {friend_name + ": Salut !", "Comment ça va ?"};
    }
}

void Messaging::render(){
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
    });



    auto messageInput = Input(&newMessage, "Écrire un message...");
    auto sendButton = Button("Envoyer", [&] {
        if (!newMessage.empty() && !friends_.empty()) {
            conversations[friends_[static_cast<size_t>(selectedFriend)]].push_back(newMessage);
            newMessage.clear();
        }
    });


    auto sidebar = Container::Vertical({
        friends_menu,
    });

    auto addMenue = Container::Vertical({
      addFriendInput,
        addFriendButton,
    });

    auto chatDisplay = Renderer([&] {
        Elements chat_elements;
        if (!friends_.empty()) {
            for (const auto& msg : conversations[friends_[static_cast<size_t>(selectedFriend)]]) {
                chat_elements.push_back(text(msg) | bold | color(Color::Yellow));
            }
        }
        return vbox(chat_elements) | flex;
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
                text(" --- LISTE AMIS --- ") | bold | color(Color::Cyan) | center,
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
                sendButton->Render(),
            }) | border | flex,
            separator(),
            vbox({
              text("Ajouter un ami") | bold | color(Color::Green) | center,
                separator(),
                addFriendInput->Render(),
                separator(),
                addFriendButton->Render(),
            }) | border,

        });
    });

    screenManager_->renderComponent(render);
}