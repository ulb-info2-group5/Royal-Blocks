/**
 * @file friends_manager.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief FriendsManager class definition file
 * @date 2025-02-24
 * 
 */

#include "friends_manager.hpp"
#include <ftxui/component/component_base.hpp>
#include <vector>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

// ### Public methods ###

FriendsManager::FriendsManager(std::shared_ptr<ftxui::ScreenInteractive> &screen) : screen_{screen}, state_{FriendsManagerState::NONE} {}

FriendsManagerState FriendsManager::render(const std::vector<std::string> &friendsList) {
    std::vector<ftxui::Component> friendsButton = displayFriendButtons(friendsList);

    ftxui::Component friendsContainer = ftxui::Container::Vertical(friendsButton);
    
    for (ftxui::Component &friendButton : friendsButton) {
        friendsContainer->Add(friendButton);
    }

    ftxui::Component buttonAddFriend = ftxui::Button("Add a friend", [&] {
        state_ = FriendsManagerState::ADD_FRIEND;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    ftxui::Component buttonBack = ftxui::Button("Back", [&] {
        state_ = FriendsManagerState::NONE;
        screen_->ExitLoopClosure()();
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    ftxui::Component buttonsContainer = ftxui::Container::Vertical({
        buttonAddFriend,
        buttonBack,
    });

    ftxui::Component render = ftxui::Renderer(ftxui::Container::Vertical({friendsContainer, buttonsContainer}), [&] {
        return ftxui::vbox({
            ftxui::text("Friends List") | ftxui::bold | ftxui::center,
            ftxui::separator(),
            ftxui::text("Your friends") | ftxui::center,
            friendsContainer->Render() | ftxui::border,
            ftxui::separator(),
            buttonAddFriend->Render(),
            ftxui::separator(),
            buttonBack->Render(),
        }) | ftxui::border | ftxui::center;
    });

    screen_->Loop(render);

    return state_;
}

std::string FriendsManager::getName() const {
    return friendName_;
}

bool FriendsManager::addFriendScreen() {
    bool res;

    // TODO: communicate with the server to add the friend to the list
    friendName_.clear(); // Reset the name of the friend
    std::string msg;

    ftxui::Component input = ftxui::Input(&friendName_, "Name of friend") | ftxui::border | ftxui::center;

    ftxui::Component submitButton = ftxui::Button("Add", [&] {
        if (friendName_.empty()) {
            // TODO: add check if name exist with server, etc
            msg = "Please enter a name";
        }
        else {
            res = true;
            screen_->ExitLoopClosure()();
        }
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    ftxui::Component backButton = ftxui::Button("Back", [&] {
        res = false;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    ftxui::Component container = ftxui::Container::Vertical({
        input,
        submitButton,
        backButton,
    });

    ftxui::Component component = ftxui::Renderer(ftxui::Container::Vertical({container}), [&] {
        return ftxui::vbox({
            ftxui::text("Add a friend") | ftxui::bold | ftxui::center,
            ftxui::separator(),
            ftxui::text(""), // Empty line
            input->Render(),
            ftxui::text(msg) | ftxui::center,
            ftxui::separator(),
            submitButton->Render(),
            backButton->Render(),
        }) | ftxui::border | ftxui::center;
    });

    screen_->Loop(component);

    return res;
}

// ### Private methods ###

std::vector<ftxui::Component> FriendsManager::displayFriendButtons(const std::vector<std:: string> &friendsList)
{
    std::vector<ftxui::Component> friendButtons;
    for (const std::string& friendName : friendsList) {
        friendButtons.push_back(ftxui::Button(friendName, [&] {
            manageFriendlistScreen(friendName);
            screen_->ExitLoopClosure()();
        }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)));
    }

    return friendButtons;
}

void FriendsManager::manageFriendlistScreen(const std::string &friendName) {

    ftxui::Component buttonYes = ftxui::Button("Yes", [&] {
        state_ = FriendsManagerState::REMOVE_FRIEND;
        friendName_ = friendName;
        screen_->ExitLoopClosure()();        
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)); // TODO: Implement the function to send to server to remove the friend
    ftxui::Component buttonNo = ftxui::Button("No", [&] {
        state_ = FriendsManagerState::NO;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)); // Like it's a back button

    ftxui::Component container = ftxui::Container::Vertical({
        buttonYes,
        buttonNo,
    });

    ftxui::Component component = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
            ftxui::text("Do you want to remove " + friendName + " from your friends list ?") | ftxui::bold | ftxui::center,
            ftxui::separator(),
            buttonYes->Render(),
            buttonNo->Render(),
        }) | ftxui::border | ftxui::center;
    });

    screen_->Loop(component);    
}
