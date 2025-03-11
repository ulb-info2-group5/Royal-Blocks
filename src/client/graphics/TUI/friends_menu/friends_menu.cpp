/**
 * @file friends_menu.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief FriendsMenu class definition file
 * @date 2025-02-24
 *
 */

#include "friends_menu.hpp"

#include "../../../core/controller/controller.hpp"
#include "../ftxui_config/ftxui_config.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <vector>

// TODO: add screens for valid or invalid when adding or removing a friend
// TODO: check that the vector of friends is correctly updated when adding or
// removing a friend

// ### Public methods ###

FriendsMenu::FriendsMenu(ftxui::ScreenInteractive &screen,
                         Controller &controller)
    : screen_{screen}, controller_(controller), exit_(false) {
    createButtons();
}

void FriendsMenu::render() {
    while (!exit_) {
        const std::vector<bindings::User> &friendsList =
            controller_.getFriendsList().friendsList;

        std::vector<ftxui::Component> friendsButton = displayFriendButtons(
            friendsList); // Display the friends list as buttons

        ftxui::Component friendsContainer =
            ftxui::Container::Vertical(friendsButton);

        for (ftxui::Component &friendButton : friendsButton) {
            friendsContainer->Add(friendButton);
        }

        ftxui::Component buttonsContainer = ftxui::Container::Vertical({
            buttonAddFriend_,
            buttonBackToMainMenu_,
        });

        ftxui::Component render = ftxui::Renderer(
            ftxui::Container::Vertical({friendsContainer, buttonsContainer}),
            [&] {
                return ftxui::vbox({
                           ftxui::text("Friends List") | ftxui::bold
                               | ftxui::center,
                           ftxui::separator(),
                           ftxui::text("Your friends") | ftxui::center,
                           friendsContainer->Render() | ftxui::borderHeavy,
                           ftxui::separator(),
                           buttonAddFriend_->Render(),
                           ftxui::separator(),
                           buttonBackToMainMenu_->Render(),
                       })
                       | ftxui::borderHeavy | ftxui::center;
            });

        screen_.Loop(handleCtrl(render));
    }
    exit_ = false; // Reset the exit_ variable for the next time we open the
                   // screen
}

// ### Private methods ###

void FriendsMenu::addFriendScreen() {
    friendNameBuffer_.clear();

    ftxui::Component container = ftxui::Container::Vertical({
        input_,
        submitButton_,
        buttonBack_,
    });

    ftxui::Component component =
        ftxui::Renderer(ftxui::Container::Vertical({container}), [&] {
            return ftxui::vbox({
                       ftxui::text("Add a friend") | ftxui::bold
                           | ftxui::center,
                       ftxui::separator(),
                       ftxui::text(""), // Empty line
                       input_->Render(),
                       ftxui::separator(),
                       submitButton_->Render(),
                       buttonBack_->Render(),
                   })
                   | ftxui::borderHeavy | ftxui::center;
        });

    screen_.Loop(handleCtrl(component));
}

std::vector<ftxui::Component> FriendsMenu::displayFriendButtons(
    const std::vector<bindings::User> &friendsList) {
    std::vector<ftxui::Component> friendButtons;

    if (friendsList.empty()) {
        ftxui::Component renderNoFriends =
            ftxui::Renderer(ftxui::Container::Vertical({}), [&] {
                return ftxui::vbox({
                    ftxui::text("You don't have friends yet"),
                });
            });
        friendButtons.push_back(renderNoFriends);
        return friendButtons;
    }

    for (const bindings::User &friendUser : friendsList) {
        friendButtons.push_back(ftxui::Button(
            friendUser.username,
            [&] {
                manageFriendlistScreen(friendUser);
                screen_.ExitLoopClosure()();
            },
            GlobalButtonStyle()));
    }

    return friendButtons;
}

void FriendsMenu::manageFriendlistScreen(const bindings::User &friendUser) {
    ftxui::Component buttonYes = ftxui::Button(
        "Yes",
        [&] {
            controller_.removeFriend(friendUser.playerId);
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());

    ftxui::Component buttonNo = ftxui::Button(
        "No", [&] { screen_.ExitLoopClosure()(); },
        GlobalButtonStyle()); // Like it's a back button

    ftxui::Component container = ftxui::Container::Vertical({
        buttonYes,
        buttonNo,
    });

    ftxui::Component component = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
                   ftxui::text("Do you want to remove " + friendUser.username
                               + " from your friends list ?")
                       | ftxui::bold | ftxui::center,
                   ftxui::separator(),
                   buttonYes->Render() | ftxui::flex,
                   buttonNo->Render() | ftxui::flex,
               })
               | ftxui::borderHeavy | ftxui::center;
    });

    screen_.Loop(handleCtrl(component));
}

void FriendsMenu::createButtons() {
    buttonBack_ = ftxui::Button(
        "Back", [&] { screen_.ExitLoopClosure()(); }, GlobalButtonStyle());

    buttonAddFriend_ = ftxui::Button(
        "Add a friend",
        [&] {
            addFriendScreen();
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());

    input_ = ftxui::Input(&friendNameBuffer_, "Name of friend")
             | ftxui::borderHeavy | ftxui::center;

    submitButton_ = ftxui::Button(
        "Add",
        [&] {
            controller_.sendFriendRequest(friendNameBuffer_);
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());

    buttonBackToMainMenu_ = ftxui::Button(
        "Back to main menu",
        [&] {
            exit_ = true; // Exit the while loop
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());
}
