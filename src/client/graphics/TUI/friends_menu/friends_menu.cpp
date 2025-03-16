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
#include <vector>

#include "../main_tui.hpp"

// ### Public methods ###

FriendsMenu::FriendsMenu(MainTui &mainTui, Controller &controller)
    : mainTui_(mainTui), controller_(controller), exit_(false) {
    createButtons();
}

void FriendsMenu::render() {
    while (!exit_) {

        ftxui::Component friendsContainer = ftxui::Container::Vertical({});

        auto updateFriendsList = [&] {
            friendsContainer->DetachAllChildren();
            const std::vector<bindings::User> &friendsList =
                controller_.getFriendsList();
            std::vector<ftxui::Component> friendsButtons = displayFriendButtons(
                friendsList, ManageOrRequestFriend::MANAGE);
            for (const ftxui::Component &friendButton : friendsButtons) {
                friendsContainer->Add(friendButton);
            }
            if (friendsContainer->ChildCount() == 0) {
                ftxui::Component renderNoFriends =
                    ftxui::Renderer(ftxui::Container::Vertical({}), [&] {
                        return ftxui::vbox({
                            ftxui::text(std::string(STR_NO_FRIEND)),
                        });
                    });
                friendsContainer->Add(renderNoFriends);
            }
        };

        ftxui::Component render = ftxui::Renderer(
            ftxui::Container::Vertical({ftxui::Container::Vertical({
                friendsContainer,
                buttonAddFriend_,
                ManageFriendRequest_,
                buttonBackToMainMenu_,
            })}),
            [&] {
                updateFriendsList();
                return ftxui::vbox({
                           ftxui::text(std::string(STR_FRIENDS_LIST))
                               | ftxui::bold | ftxui::center,
                           ftxui::separator(),
                           ftxui::text(std::string(STR_FRIENDS))
                               | ftxui::center,
                           friendsContainer->Render() | ftxui::borderHeavy,
                           ftxui::separator(),
                           buttonAddFriend_->Render(),
                           ftxui::separator(),
                           ManageFriendRequest_->Render(),
                           ftxui::separator(),
                           buttonBackToMainMenu_->Render(),
                       })
                       | ftxui::borderHeavy | ftxui::center;
            });

        mainTui_.render(render);
    }
    exit_ = false; // Reset the exit boolean for the next time
}

// ### Private methods ###

void FriendsMenu::addFriendScreen() {
    friendNameBuffer_.clear();

    ftxui::Component component = ftxui::Renderer(
        ftxui::Container::Vertical({
            ftxui::Container::Vertical({
                input_,
                submitButton_,
                buttonBack_,
            }),
        }),
        [&] {
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

    mainTui_.render(component);
}

std::vector<ftxui::Component> FriendsMenu::displayFriendButtons(
    const std::vector<bindings::User> &friendsList,
    ManageOrRequestFriend manageOrRequest) {
    std::vector<ftxui::Component> friendButtons;

    for (const bindings::User &friendUser : friendsList) {
        friendButtons.push_back(ftxui::Button(
            friendUser.username,
            [&] {
                manageFriendlistScreen(friendUser, manageOrRequest);
                mainTui_.stopRender();
            },
            GlobalButtonStyle()));
    }

    return friendButtons;
}

void FriendsMenu::manageFriendlistScreen(
    const bindings::User &friendUser, ManageOrRequestFriend manageOrRequest) {
    std::string message;

    if (manageOrRequest == ManageOrRequestFriend::MANAGE) {
        message = "Do you want to remove " + friendUser.username
                  + " from your friends list ?";
    } else {
        message = "Do you want to accept or decline " + friendUser.username
                  + " friend request ?";
    }

    ftxui::Component buttonYes = ftxui::Button(
        std::string(STR_YES),
        [&] {
            if (manageOrRequest == ManageOrRequestFriend::MANAGE) {
                controller_.removeFriend(friendUser.userID);
            } else {
                controller_.acceptFriendRequest(friendUser.userID);
                // TODO: with controller to accept or decline friend request
            }
            mainTui_.stopRender();
        },
        GlobalButtonStyle());

    ftxui::Component buttonNo = ftxui::Button(
        std::string(STR_NO), [&] { mainTui_.stopRender(); },
        GlobalButtonStyle());

    ftxui::Component component = ftxui::Renderer(
        ftxui::Container::Vertical({
            buttonYes,
            buttonNo,
        }),
        [&] {
            return ftxui::vbox({
                       ftxui::text(message) | ftxui::bold | ftxui::center,
                       ftxui::separator(),
                       buttonYes->Render() | ftxui::flex,
                       buttonNo->Render() | ftxui::flex,
                   })
                   | ftxui::borderHeavy | ftxui::center;
        });

    mainTui_.render(component);
}

void FriendsMenu::createButtons() {
    buttonBack_ = ftxui::Button(
        std::string(STR_BACK), [&] { mainTui_.stopRender(); },
        GlobalButtonStyle());

    buttonAddFriend_ = ftxui::Button(
        std::string(STR_ADD_A_FRIEND),
        [&] {
            addFriendScreen();
            mainTui_.stopRender();
        },
        GlobalButtonStyle());

    input_ = ftxui::Input(&friendNameBuffer_, std::string(STR_NAME_OF_FRIEND))
             | ftxui::borderHeavy | ftxui::center;

    submitButton_ = ftxui::Button(
        std::string(STR_ADD),
        [&] {
            controller_.sendFriendRequest(friendNameBuffer_);
            mainTui_.stopRender();
        },
        GlobalButtonStyle());

    buttonBackToMainMenu_ = ftxui::Button(
        std::string(STR_BACK_TO_MAIN_MENU),
        [&] {
            exit_ = true; // Exit the while loop
            mainTui_.stopRender();
        },
        GlobalButtonStyle());

    ManageFriendRequest_ = ftxui::Button(
        std::string(STR_MANAGE_FRIENDS_REQUESTS),
        [&] {
            FriendRequestScreen();
            mainTui_.stopRender();
        },
        GlobalButtonStyle());
}

void FriendsMenu::FriendRequestScreen() {

    ftxui::Component friendsContainer = ftxui::Container::Vertical({});

    auto updateFriendsList = [&] {
        friendsContainer->DetachAllChildren();

        // TODO: get the list of friends from the controller
        const std::vector<bindings::User> &friendsList =
            controller_.getPendingFriendRequests();

        std::vector<ftxui::Component> friendsButtons =
            displayFriendButtons(friendsList, ManageOrRequestFriend::REQUEST);
        for (const ftxui::Component &friendButton : friendsButtons) {
            friendsContainer->Add(friendButton);
        }
        if (friendsContainer->ChildCount() == 0) {
            ftxui::Component renderNoFriends =
                ftxui::Renderer(ftxui::Container::Vertical({}), [&] {
                    return ftxui::vbox({
                        ftxui::text(std::string(STR_NO_FRIEND_REQUEST)),
                    });
                });
            friendsContainer->Add(renderNoFriends);
        }
    };

    ftxui::Component render = ftxui::Renderer(
        ftxui::Container::Vertical({ftxui::Container::Vertical({
            friendsContainer,
            buttonBack_,
        })}),
        [&] {
            updateFriendsList();
            return ftxui::vbox({
                       ftxui::text("Friend request received") | ftxui::center
                           | ftxui::bold,
                       ftxui::separator(),
                       friendsContainer->Render() | ftxui::borderHeavy,
                       ftxui::separator(),
                       buttonBack_->Render(),
                   })
                   | ftxui::borderHeavy | ftxui::center;
        });

    mainTui_.render(render);
}
