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
            const std::vector<bindings::User> friendsList =
                controller_.getFriendsList();
            std::vector<ftxui::Component> friendsButtons =
                displayFriendButtons(friendsList);
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
    addMessage_.clear();

    ftxui::Component component = ftxui::Renderer(
        ftxui::Container::Vertical({
            ftxui::Container::Vertical({
                input_,
                submitButton_,
                buttonBack_,
            }),
        }),
        [&] {
            std::vector<ftxui::Element> elements = {
                ftxui::text(std::string(STR_ADD_A_FRIEND)) | ftxui::bold
                    | ftxui::center,
                ftxui::separator(), input_->Render(), ftxui::separator()};

            if (!addMessage_.empty()) {
                elements.push_back(ftxui::text(addMessage_) | ftxui::bold
                                   | ftxui::center);
                elements.push_back(ftxui::separator());
            }

            elements.push_back(submitButton_->Render());
            elements.push_back(buttonBack_->Render());

            return ftxui::vbox(elements) | ftxui::borderHeavy | ftxui::center;
        });

    mainTui_.render(component);
}

std::vector<ftxui::Component> FriendsMenu::displayFriendButtons(
    const std::vector<bindings::User> &friendsList) {
    std::vector<ftxui::Component> friendButtons;

    for (const bindings::User &friendUser : friendsList) {
        friendButtons.push_back(ftxui::Button(
            friendUser.username,
            [this, friendUser] { manageFriendlistScreen(friendUser); },
            GlobalButtonStyle()));
    }

    return friendButtons;
}

void FriendsMenu::manageFriendlistScreen(const bindings::User &friendUser) {
    std::string message = "Do you want to remove " + friendUser.username
                          + " from your friends list ?";

    ftxui::Component buttonYes = ftxui::Button(
        std::string(STR_YES),
        [&] {
            controller_.removeFriend(friendUser.userID);
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

    input_ =
        ftxui::Input(&friendNameBuffer_, std::string(STR_NAME_OF_FRIEND))
        | ftxui::borderHeavy | ftxui::center
        | ftxui::CatchEvent([&](ftxui::Event event) {
              if (event == ftxui::Event::Return && !friendNameBuffer_.empty()) {
                  controller_.sendFriendRequest(friendNameBuffer_);
                  addMessage_ = "Friend request sent to " + friendNameBuffer_;
                  friendNameBuffer_.clear();
                  return true;
              } else if (event == ftxui::Event::Return) {
                  return true; // Do not send an empty friend request
              }
              return false;
          });

    submitButton_ = ftxui::Button(
        std::string(STR_ADD),
        [&] {
            controller_.sendFriendRequest(friendNameBuffer_);
            addMessage_ = "Friend request sent to " + friendNameBuffer_;
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
        [&] { FriendRequestScreen(); }, GlobalButtonStyle());
}

void FriendsMenu::FriendRequestScreen() {

    bool activeRequest = false;
    bindings::User chosenFriend;

    ftxui::Component mainContainer = ftxui::Container::Vertical({});

    ftxui::Component buttonDecline = ftxui::Button(
        "Refuse Request",
        [&] {
            controller_.declineFriendRequest(chosenFriend.userID);
            activeRequest = false;
        },
        GlobalButtonStyle());

    ftxui::Component buttonAccept = ftxui::Button(
        "Accept Request",
        [&] {
            controller_.acceptFriendRequest(chosenFriend.userID);
            activeRequest = false;
        },
        GlobalButtonStyle());

    auto updateFriendsList = [&] {
        mainContainer->DetachAllChildren();

        const std::vector<bindings::User> friendsList =
            controller_
                .getPendingFriendRequests(); 

        std::vector<ftxui::Component> friendsButtons;
        for (const bindings::User &friendUser : friendsList) {
            friendsButtons.push_back(ftxui::Button(
                friendUser.username,
                [this, friendUser, &activeRequest, &chosenFriend] {
                    activeRequest = true;
                    chosenFriend = friendUser;
                },
                GlobalButtonStyle()));
        }

        if (friendsButtons.size() == 0) {
            ftxui::Component renderNoFriends =
                ftxui::Renderer(ftxui::Container::Vertical({}), [&] {
                    return ftxui::vbox({
                        ftxui::text(std::string(STR_NO_FRIEND_REQUEST))
                            | ftxui::center,
                    });
                });
            mainContainer->Add(renderNoFriends);
        } else {
            mainContainer->Add(ftxui::Renderer([] {
                return ftxui::text("List of your pending friends requests");
            }));
            for (const ftxui::Component &friendButton : friendsButtons) {
                mainContainer->Add(friendButton);
            }
        }

        if (activeRequest) {
            mainContainer->Add(
                ftxui::Renderer([] { return ftxui::separator(); }));
            mainContainer->Add(ftxui::Renderer([&] {
                return ftxui::text("Do you want to accept or decline "
                                   + chosenFriend.username
                                   + " friend request ?")
                       | ftxui::center | ftxui::bold;
            }));
            mainContainer->Add(buttonAccept);
            mainContainer->Add(buttonDecline);
        }

        mainContainer->Add(ftxui::Renderer([] { return ftxui::separator(); }));
        mainContainer->Add(buttonBack_);
    };

    ftxui::Component render = ftxui::Renderer(mainContainer, [&] {
        updateFriendsList();
        return ftxui::vbox({
                   ftxui::text("Friend request received") | ftxui::center
                       | ftxui::bold,
                   ftxui::separator(),
                   mainContainer->Render(),
               })
               | ftxui::borderHeavy | ftxui::center;
    });

    mainTui_.render(render);
}
