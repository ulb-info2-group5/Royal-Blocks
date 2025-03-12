#include "messaging.hpp"

#include "../../../core/controller/controller.hpp"
#include "../ftxui_config/ftxui_config.hpp"
#include "core/in_game/player_state/player_state_external.hpp"

#include "../../../../common/bindings/message.hpp"
#include <ftxui/dom/elements.hpp>
#include <optional>

// TODO: add verification of information when adding a friend, sending a
// message, etc. with the server.

// ### constructor ###
Messaging::Messaging(ftxui::ScreenInteractive &screen, Controller &controller)
    : screen_(screen), controller_(controller) {
    userState_ = MessagingState::NONE;
    createButtons();
}

// ### protected methods ###

void Messaging::createButtons() {
    addFriendButton_ = ftxui::Button(
        "Add a friend",
        [&] {
            controller_.sendFriendRequest(newFriendBuffer_);

            // TODO: lulu Controller -> add Friend (done)
            controller_.sendFriendRequest(newFriendBuffer_);

            newFriendBuffer_.clear();
        },
        GlobalButtonStyle());

    sendButton_ =
        ftxui::Button(
            "Send",
            [&] {
                if (!newMessageBuffer_.empty()
                    // && TODO: lulu check valid friend (at least one)
                ) {
                    getSelectedFriendId().and_then([&](PlayerID playerId) {
                        controller_.sendMessage(playerId, newMessageBuffer_);
                        return std::optional<PlayerID>{};
                    });

                    // TODO: lulu controller -> sendMessage (done)
                    // Old code:
                    // (selectedFriend) controller_.sendMessage(
                    //     friends_[static_cast<size_t>(selectedFriend)],
                    //     newMessageBuffer_);

                    newMessageBuffer_.clear();
                }
            },
            GlobalButtonStyle())
        | ftxui::center;

    backButton_ = ftxui::Button(
        "Back",
        [&] {
            newMessageBuffer_.clear();
            newFriendBuffer_.clear();
            userState_ = MessagingState::BACK;
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());
}

void Messaging::drawInputUser() {
    newFriendBuffer_.clear();

    addFriendInput_ = ftxui::Input(&newFriendBuffer_, "Name of the friend")
                      | ftxui::center | ftxui::borderHeavy;
    // attempt to send the result when  user press enter

    // addFriendInput |= CatchEvent([&](ftxui::Event event) {
    //     if ( event == event.Return) {
    //         if (!newFriend.empty()) {
    //         }

    //     }
    // });

    messageInput_ = ftxui::Input(&newMessageBuffer_, "Write a message...")
                    | ftxui::center | ftxui::borderHeavy;
}

void Messaging::drawMenu() {
    drawInputUser();

    // TODO: lulu ask controller for the friendsList, extract the names and pass
    // them to the Menu. (done)

    friendNames_.clear();

    auto &friendsList = controller_.getFriendsList();

    // NOTE: if we do not resize first, it will insert out of the vector ->
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

                       for (auto &[senderId, message] :
                            conversation.senderMessages) {

                           // TODO: display our own messages with a different
                           // color
                           chat_elements.push_back(
                               ftxui::text(message) | ftxui::bold
                               | ftxui::color(ftxui::Color::Yellow));
                       }

                       return ftxui::vbox(chat_elements) | ftxui::flex;
                   })
                   .value_or(ftxui::text("No conversation"))
               | ftxui::bold | ftxui::center;
    });
}

void Messaging::drawWindow() {
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
                       ftxui::text(" --- FRIENDS LIST --- ") | ftxui::bold
                           | ftxui::color(ftxui::Color::Green) | ftxui::center,
                       ftxui::separator(),
                       friendsMenu_->Render(),

                   }) | ftxui::borderHeavy,

                   ftxui::vbox({
                       ftxui::text(" --- CONVERSATION --- ") | ftxui::bold
                           | ftxui::color(ftxui::Color::Green) | ftxui::center,
                       ftxui::separator(),
                       chatDisplay_->Render() | ftxui::flex,
                       ftxui::separator(),
                       messageInput_->Render(),
                       ftxui::separator(),
                       sendButton_->Render(),
                   }) | ftxui::borderHeavy
                       | ftxui::flex,

                   ftxui::vbox({
                       ftxui::text("-- Add a friend --") | ftxui::bold
                           | ftxui::color(ftxui::Color::Green) | ftxui::center,
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

std::optional<PlayerID> Messaging::getSelectedFriendId() {
    const std::vector<bindings::User> &friendsList =
        controller_.getFriendsList();

    return (friendsList.empty())
               ? std::nullopt
               : std::make_optional(friendsList.at(selectedFriend_).playerId);
}

// ### public methods ###
void Messaging::render() {
    drawWindow();
    screen_.Loop(handleCtrl(displayWindow_));
}
