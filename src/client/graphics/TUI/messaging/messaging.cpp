#include "messaging.hpp"

#include "../main_tui.hpp"
#include "../ftxui_config/ftxui_config.hpp"
#include "../../../core/controller/controller.hpp"

// TODO: add verification of information when adding a friend, sending a
// message, etc. with the server.

// ### constructor ###
Messaging::Messaging(MainTui &mainTui, Controller &controller)
    : mainTui_(mainTui), controller_(controller) {
    userState_ = MessagingState::NONE;
    createButtons();
}

// ### protected methods ###

void Messaging::createButtons() {
    addFriendButton_ = ftxui::Button(
        std::string(STR_ADD_A_FRIEND),
        [&] {
            controller_.sendFriendRequest(newFriendBuffer_);
            newFriendBuffer_.clear();
        },
        GlobalButtonStyle());

    sendButton_ =
        ftxui::Button(
            std::string(STR_SEND),
            [&] {
                if (!newMessageBuffer_.empty()
                    // && TODO: lulu check valid friend (at least one)
                ) {
                    getSelectedFriendId().and_then([&](UserID userID) {
                        controller_.sendMessage(userID, newMessageBuffer_);
                        return std::optional<UserID>{};
                    });
                    newMessageBuffer_.clear();
                }
            },
            GlobalButtonStyle())
        | ftxui::center;

    backButton_ = ftxui::Button(
        std::string(STR_BACK),
        [&] {
            newMessageBuffer_.clear();
            newFriendBuffer_.clear();
            userState_ = MessagingState::BACK;
            mainTui_.stopRender();
        },
        GlobalButtonStyle());
}

void Messaging::drawInputUser() {
    newFriendBuffer_.clear();

    addFriendInput_ =
        ftxui::Input(&newFriendBuffer_, std::string(STR_NAME_OF_FRIEND))
        | ftxui::center | ftxui::borderHeavy;
    // attempt to send the result when  user press enter

    // addFriendInput |= CatchEvent([&](ftxui::Event event) {
    //     if ( event == event.Return) {
    //         if (!newFriend.empty()) {
    //         }

    //     }
    // });

    messageInput_ =
        ftxui::Input(&newMessageBuffer_, std::string(STR_WRITE_MESSAGE))
        | ftxui::center | ftxui::borderHeavy | ftxui::CatchEvent([&](ftxui::Event event) {
            if (event == ftxui::Event::Return) {
                if (!newMessageBuffer_.empty()) {
                    getSelectedFriendId().and_then([&](UserID userID) {
                        controller_.sendMessage(userID, newMessageBuffer_);
                        return std::optional<UserID>{};
                    });
                    newMessageBuffer_.clear();
                }
                return true;
            }
            return false;
        });;
}

void Messaging::drawMenu() {
    drawInputUser();

    auto &friendsList = controller_.getFriendsList();

    friendNames_.clear();
    // NOTE: if we do not resize first, it will push_back out of the vector ->
    // memory problems
    friendNames_.resize(friendsList.size());
    std::transform(friendsList.begin(), friendsList.end(), friendNames_.begin(),
                   [](const bindings::User &user) -> std::string {
                       return user.username;
                   });

    friendsMenu_ = ftxui::Menu(&friendNames_, &selectedFriend_);

    addMenu_ = ftxui::Container::Vertical({
        addFriendInput_,
        addFriendButton_,
        backButton_,
    });
}

void Messaging::drawDisplay() {
    drawMenu();

    sidebar_ = ftxui::Container::Vertical({
        friendsMenu_,
    });

    chatDisplay_ = ftxui::Renderer([&] {
        return getSelectedFriendId()
            .and_then([this](auto id) -> std::optional<ftxui::Element> {
                ftxui::Elements chat_elements;

                auto &[name, conversation] =
                    controller_.getConversationWith(id);

                if (conversation.senderMessages.empty()) {
                    chat_elements.push_back(
                        ftxui::text(std::string("No messages yet")));
                }

                else {
                    for (auto &[senderId, message] :
                         conversation.senderMessages) {
                        chat_elements.push_back(
                            ftxui::text(message) | ftxui::bold
                            | ftxui::color(ftxui::Color::Yellow));
                    }
                }

                return ftxui::vbox(chat_elements) | ftxui::flex;
            })
            .value_or(ftxui::text(std::string(STR_NO_CONVERSATION)));
    });
}

void Messaging::drawWindow() {
    drawDisplay();

    displayWindow_ = ftxui::Renderer(
        ftxui::Container::Horizontal({
            sidebar_,
            ftxui::Container::Vertical({
                chatDisplay_,
                messageInput_,
                sendButton_,
            }),
            addMenu_,
        }),
        [&] {
            return ftxui::hbox({
                       ftxui::vbox({
                           ftxui::text(std::string(STR_FRIENDS_LIST_TITLE))
                               | ftxui::bold | ftxui::color(ftxui::Color::Green)
                               | ftxui::center,
                           ftxui::separator(),
                           friendsMenu_->Render(),

                       }) | ftxui::borderHeavy,

                       ftxui::vbox({
                           ftxui::text(std::string(STR_CONVERSATION_TITLE))
                               | ftxui::bold | ftxui::color(ftxui::Color::Green)
                               | ftxui::center,
                           ftxui::separator(),
                           chatDisplay_->Render() | ftxui::flex,
                           ftxui::separator(),
                           messageInput_->Render(),
                           ftxui::separator(),
                           sendButton_->Render(),
                       }) | ftxui::borderHeavy
                           | ftxui::flex,

                       ftxui::vbox({
                           ftxui::text(std::string(STR_ADD_FRIEND_TITLE))
                               | ftxui::bold | ftxui::color(ftxui::Color::Green)
                               | ftxui::center,
                           ftxui::separator(),
                           addFriendInput_->Render(),
                           ftxui::separator(),
                           addFriendButton_->Render(),
                           ftxui::separator(),

                           backButton_->Render(),
                           ftxui::separator(),
                       }) | ftxui::borderHeavy,

                   })
                   | ftxui::borderHeavy;
        });
}

std::optional<UserID> Messaging::getSelectedFriendId() {
    const std::vector<bindings::User> &friendsList =
        controller_.getFriendsList();

    return (friendsList.empty())
               ? std::nullopt
               : std::make_optional(friendsList.at(selectedFriend_).userID);
}

// ### public methods ###
void Messaging::render() {
    drawWindow();
    mainTui_.render(displayWindow_);
}
