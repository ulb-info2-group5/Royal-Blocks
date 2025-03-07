/**
 * @file friends_menu.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief FriendsMenu class definition file
 * @date 2025-02-24
 *
 */

#include "friends_menu.hpp"

#include "../../../controller/controller.hpp"
#include "../handle_ctrl/handle_ctrl.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <vector>

// TODO: add screens for valid or invalid when adding or removing a friend
// TODO: check that the vector of friends is correctly updated when adding or
// removing a friend

// ### Public methods ###

FriendsMenu::FriendsMenu(ftxui::ScreenInteractive &screen,
                               Controller *controller)
    : screen_{screen}, controller_(controller) {
    createButtons();
}

void FriendsMenu::render() {
    while (!exit_) {

        std::vector<std::string> friendsList =
            controller_->getFriendsList(); // Get the friends list of the user
                                           // by asking the controller

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
                           friendsContainer->Render() | ftxui::border,
                           ftxui::separator(),
                           buttonAddFriend_->Render(),
                           ftxui::separator(),
                           buttonBackToMainMenu_->Render(),
                       })
                       | ftxui::border | ftxui::center;
            });

        screen_.Loop(handleCtrl(render));
    }
}

// ### Private methods ###

void FriendsMenu::addFriendScreen() {
    friendName_.clear(); // Reset the name of the friend when we (re)oprn the screen
    msg_.clear();        // Reset the message when we (re)open the screen

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
                       ftxui::text(msg_) | ftxui::center,
                       ftxui::separator(),
                       submitButton_->Render(),
                       buttonBack_->Render(),
                   })
                   | ftxui::border | ftxui::center;
        });

    screen_.Loop(handleCtrl(component));
}

std::vector<ftxui::Component> FriendsMenu::displayFriendButtons(
    const std::vector<std::string> &friendsList) {
    std::vector<ftxui::Component> friendButtons;
    for (const std::string &friendName : friendsList) {
        friendButtons.push_back(ftxui::Button(
            friendName,
            [&] {
                manageFriendlistScreen(friendName);
                screen_.ExitLoopClosure()();
            },
            ftxui::ButtonOption::Animated(ftxui::Color::Grey0)));
    }

    return friendButtons;
}

void FriendsMenu::manageFriendlistScreen(const std::string &friendName) {
    ftxui::Component buttonYes = ftxui::Button(
        "Yes",
        [&] {
            if (controller_->removeFriend(friendName)) {
                screen_.ExitLoopClosure()();
            }
        }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0))| ftxui::border;

    ftxui::Component buttonNo = ftxui::Button(
        "No", [&] { screen_.ExitLoopClosure()(); },
        ftxui::ButtonOption::Animated(
            ftxui::Color::Grey0)) | ftxui::border; // Like it's a back button

    ftxui::Component container = ftxui::Container::Horizontal({
        buttonYes,
        buttonNo,
    });

    ftxui::Component component = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
                   ftxui::text("Do you want to remove " + friendName
                               + " from your friends list ?")
                        | ftxui::bold | ftxui::center,
                    ftxui::separator(),
                    buttonYes->Render() | ftxui::flex,
                    buttonNo->Render() | ftxui::flex,
               }) | ftxui::border | ftxui::center;
    });

    screen_.Loop(handleCtrl(component));
}

void FriendsMenu::createButtons() {
    buttonBack_ = ftxui::Button(
        "Back", [&] { screen_.ExitLoopClosure()(); },
        ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
        | ftxui::border;

    buttonAddFriend_ = ftxui::Button(
                "Add a friend",
                [&] {
                    addFriendScreen();
                    screen_.ExitLoopClosure()();
                },
                ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
            | ftxui::border;

    input_ = ftxui::Input(&friendName_, "Name of friend") | ftxui::border
        | ftxui::center;

    submitButton_ = ftxui::Button(
            "Add",
            [&] {
                if (!controller_->addFriend(friendName_)) {
                    msg_ = "Please enter a valid name";
                } else {
                    screen_.ExitLoopClosure()();
                }
            },
            ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
        | ftxui::border;

    buttonBackToMainMenu_ =
        ftxui::Button(
            "Back to main menu",
            [&] {
                exit_ = true; // Exit the while loop
                screen_.ExitLoopClosure()();
            },
            ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
        | ftxui::border;
}