/**
 * @file friends_manager.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief FriendsManager class definition file
 * @date 2025-02-24
 * 
 */

#include "friends_manager.hpp"

#include "../../../controller/controller.hpp"

#include <ftxui/component/component_base.hpp>
#include <vector>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

// TODO: add screens for valid or invalid when adding or removing a friend
// TODO: check that the vector of friends is correctly updated when adding or removing a friend

// ### Public methods ###

FriendsManager::FriendsManager(std::shared_ptr<ftxui::ScreenInteractive> screen, Controller *controller) : screen_{screen}, controller_(controller) {
    buttonBack_ = ftxui::Button("Back", [&] {
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;
}

void FriendsManager::render() {
    bool res = true;

    while (res) {
    
        std::vector<std::string> friendsList = controller_->getFriendsList();

        std::vector<ftxui::Component> friendsButton = displayFriendButtons(friendsList);

        ftxui::Component buttonBack = ftxui::Button("Back", [&] {
            res = false; // Exit the loop
            screen_->ExitLoopClosure()();
        }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

        ftxui::Component friendsContainer = ftxui::Container::Vertical(friendsButton);
        
        for (ftxui::Component &friendButton : friendsButton) {
            friendsContainer->Add(friendButton);
        }

        ftxui::Component buttonAddFriend = ftxui::Button("Add a friend", [&] {
            addFriendScreen();
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
    }
}


// ### Private methods ###

void FriendsManager::addFriendScreen() {
    friendName_.clear(); // Reset the name of the friend
    std::string msg;

    ftxui::Component input = ftxui::Input(&friendName_, "Name of friend") | ftxui::border | ftxui::center;

    ftxui::Component submitButton = ftxui::Button("Add", [&] {
        if (!controller_->addFriend(friendName_)) {
            msg = "Please enter a valid name";
        }
        else {
            screen_->ExitLoopClosure()();
        }
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    ftxui::Component container = ftxui::Container::Vertical({
        input,
        submitButton,
        buttonBack_,
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
            buttonBack_->Render(),
        }) | ftxui::border | ftxui::center;
    });

    screen_->Loop(component);
}

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
        if (controller_->removeFriend(friendName)) {
            screen_->ExitLoopClosure()(); 
        }       
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0));
    ftxui::Component buttonNo = ftxui::Button("No", [&] {
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
