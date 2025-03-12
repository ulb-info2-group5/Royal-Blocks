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


// ### Public methods ###

FriendsMenu::FriendsMenu(ScreenManager &screenManager,
                         Controller &controller)
    : screenManager_(screenManager), controller_(controller), exit_(false) {
    createButtons();
}

void FriendsMenu::render() {
    while (!exit_) {
        const std::vector<bindings::User> &friendsList =
            controller_.getFriendsList();

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
                           ftxui::text(std::string(STR_FRIENDS_LIST)) | ftxui::bold
                               | ftxui::center,
                           ftxui::separator(),
                           ftxui::text(std::string(STR_FRIENDS)) | ftxui::center,
                           friendsContainer->Render() | ftxui::borderHeavy,
                           ftxui::separator(),
                           buttonAddFriend_->Render(),
                           ftxui::separator(),
                           buttonBackToMainMenu_->Render(),
                       })
                       | ftxui::borderHeavy | ftxui::center;
            });

        screenManager_.render(render);
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
                       ftxui::text(std::string(STR_ADD_A_FRIEND)) | ftxui::bold
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

    screenManager_.render(component);
}

std::vector<ftxui::Component> FriendsMenu::displayFriendButtons(
    const std::vector<bindings::User> &friendsList) {
    std::vector<ftxui::Component> friendButtons;

    if (friendsList.empty()) {
        ftxui::Component renderNoFriends =
            ftxui::Renderer(ftxui::Container::Vertical({}), [&] {
                return ftxui::vbox({
                    ftxui::text(std::string(STR_NO_FRIEND)),
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
                screenManager_.stopRender();
            },
            GlobalButtonStyle()));
    }

    return friendButtons;
}

void FriendsMenu::manageFriendlistScreen(const bindings::User &friendUser) {
    ftxui::Component buttonYes = ftxui::Button(
        std::string(STR_YES),
        [&] {
            controller_.removeFriend(friendUser.playerId);
            screenManager_.stopRender();
        },
        GlobalButtonStyle());

    ftxui::Component buttonNo = ftxui::Button(
        std::string(STR_NO), [&] { screenManager_.stopRender(); },
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

    screenManager_.render(component);
}

void FriendsMenu::createButtons() {
    buttonBack_ = ftxui::Button(
        std::string(STR_BACK), [&] { screenManager_.stopRender(); }, GlobalButtonStyle());

    buttonAddFriend_ = ftxui::Button(
        std::string(STR_ADD_A_FRIEND),
        [&] {
            addFriendScreen();
            screenManager_.stopRender();
        },
        GlobalButtonStyle());

    input_ = ftxui::Input(&friendNameBuffer_, std::string(STR_NAME_OF_FRIEND))
             | ftxui::borderHeavy | ftxui::center;

    submitButton_ = ftxui::Button(
        std::string(STR_ADD),
        [&] {
            controller_.sendFriendRequest(friendNameBuffer_);
            screenManager_.stopRender();
        },
        GlobalButtonStyle());

    buttonBackToMainMenu_ = ftxui::Button(
        std::string(STR_BACK_TO_MAIN_MENU),
        [&] {
            exit_ = true; // Exit the while loop
            screenManager_.stopRender();
        },
        GlobalButtonStyle());
}
