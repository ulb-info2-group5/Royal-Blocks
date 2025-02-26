#include "messaging.hpp"

#include "../../../controller/controller.hpp"

// ### constructor ###
Messaging::Messaging(std::shared_ptr<ftxui::ScreenInteractive> &screen, Controller *controller) : 
    screen_(screen), controller_(controller)
{
    userState_ = MessagingState::NONE;
    initMessaging();
}

// ### private methods ###
void Messaging::initMessaging(){
    for (const std::string& friend_name : friends_) 
    {
        conversations[friend_name] = {Message{1, friend_name + " : test bonjour "} };
    }
}
// ### protected methods ###

void Messaging::drawButtons()
{
    addFriendButton_ = ftxui::Button("Ajouter un ami", [&] {
        if (!newFriend_.empty()) {
            friends_.push_back(newFriend_);
            conversations[newFriend_] = {}; 
            newFriend_.clear();
        }
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0));

    sendButton_ = ftxui::Button("Envoyer", [&] {
        if (!newMessage_.empty() && !friends_.empty()) { 
            addMessage(newMessage_);
        }
    }) | ftxui::center;

    backButton_ = ftxui::Button("Back", [&] {
        newMessage_.clear();
        newFriend_.clear();
        userState_ = MessagingState::BACK;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0));
}

void Messaging::drawInputUSer()
{
    addFriendInput_ = ftxui::Input(&newFriend_, "Nom de l'ami");
    //attempt to send the result when  user press enter

    // addFriendInput |= CatchEvent([&](ftxui::Event event) {
    //     if ( event == event.Return) {
    //         if (!newFriend.empty()) {
    //         }
             
    //     }
    // });


    messageInput_ = ftxui::Input(&newMessage_, "Écrire un message...") | ftxui::center | ftxui::border;
}

void Messaging::drawMenu()
{
    drawInputUSer();
    drawButtons();

    friendsMenu_ = ftxui::Menu(&friends_, &selectedFriend);

    addMenu_ = ftxui::Container::Vertical({
        addFriendInput_,
        addFriendButton_,
        backButton_,
    });
}

void Messaging::drawDisplay()
{
    drawMenu();

    sidebar_ = ftxui::Container::Vertical({
        friendsMenu_,
    });

    chatDisplay_ = ftxui::Renderer([&] {
        ftxui::Elements chat_elements;
        if (!friends_.empty()) {
            for (const Message &msg : conversations[friends_[static_cast<size_t>(selectedFriend)]]) {
                if (msg.idSender != userId){
                    chat_elements.push_back(ftxui::text(msg.message) | ftxui::bold | ftxui::color(ftxui::Color::Yellow));
                }else {
                    chat_elements.push_back(ftxui::text(msg.message) | ftxui::bold | ftxui::color(ftxui::Color::DarkCyan));
                }
                
            }
        }
        return ftxui::vbox(chat_elements) | ftxui::flex ;
    });
}

void Messaging::drawWindow()
{
    drawDisplay();

    ftxui::Component mainContainer = ftxui::Container::Horizontal({
        sidebar_,
        ftxui::Container::Vertical({
            chatDisplay_,
            messageInput_,
            sendButton_,
        }),
        addMenu_,
    });

    displayWindow_ = ftxui::Renderer(mainContainer, [&] {
        return ftxui::hbox({
            ftxui::vbox({
                ftxui::text(" --- LISTE AMIS --- ") | ftxui::bold | ftxui::color(ftxui::Color::Green) | ftxui::center,
                ftxui::separator(),
                friendsMenu_->Render(),
                
            }) | ftxui::border,

            ftxui::vbox({
                ftxui::text(" --- CONVERSATION --- ") | ftxui::bold | ftxui::color(ftxui::Color::Green) | ftxui::center,
                ftxui::separator(),
                chatDisplay_->Render() | ftxui::flex,
                ftxui::separator(),
                messageInput_->Render(),
                ftxui::separator(),
                sendButton_->Render(),
            }) | ftxui::border | ftxui::flex,

            ftxui::vbox({
              ftxui::text("-- Ajouter un ami --") | ftxui::bold | ftxui::color(ftxui::Color::Green) | ftxui::center,
                ftxui::separator(),
                addFriendInput_->Render(),
                ftxui::separator(),
                addFriendButton_->Render(),
                ftxui::separator(),

                backButton_->Render(),
                ftxui::separator(),
            }) | ftxui::border,

        }) | ftxui::border;
    });
}

// ### public methods ###
MessagingState Messaging::render()
{
    drawWindow();
    screen_->Loop(displayWindow_);
    return userState_;
}

void Messaging::addMessage(const std::string &message)
{
    conversations[friends_[static_cast<size_t>(selectedFriend)]].push_back(Message{userId, message});
    newMessage_.clear();
}