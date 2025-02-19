/**
 * @file main_menu.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief MainMenu class definition file
 * @date 2025-02-12
 * 
 */

#include "main_menu.hpp"

#include "../messaging/messaging.hpp"

#include <cstdlib>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/mouse.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <memory>
#include <string>
#include <tuple>
#include <vector>


// ### Public methods ###
MainMenu::MainMenu(std::shared_ptr<ftxui::ScreenInteractive> &screen) : screen_(screen) {}

MainMenuState MainMenu::render() {
    MainMenuState res = MainMenuState::NONE;

    ftxui::Component buttonPlay = ftxui::Button("Play a game", [&] {
        res = MainMenuState::PLAY;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated()) | ftxui::border;
    ftxui::Component buttonJoinGame = ftxui::Button("Join a game", [&] {
        res = MainMenuState::JOIN_GAME;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated()) | ftxui::border;
    ftxui::Component buttonSendMessagesToFriends = ftxui::Button("Send messages to friends", [&] {
        res = MainMenuState::SEND_MESSAGES;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated()) | ftxui::border;
    ftxui::Component buttonLookRanking = ftxui::Button("Look at ranking", [&] {
        res = MainMenuState::LOOK_RANKING;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated()) | ftxui::border;
    ftxui::Component buttonManageProfile = ftxui::Button("Manage profile", [&] {
        res = MainMenuState::MANAGE_PROFILE;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated()) | ftxui::border;
    ftxui::Component buttonManageFriendsList = ftxui::Button("Manage friends list", [&] {
        res = MainMenuState::MANAGE_FRIENDS_LIST;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated()) | ftxui::border;
    ftxui::Component buttonExit = ftxui::Button("Exit", [&] {
        res = MainMenuState::EXIT;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated()) | ftxui::border;

    ftxui::Component component = ftxui::Container::Vertical({
        buttonPlay,
        buttonJoinGame,
        buttonSendMessagesToFriends,
        buttonLookRanking,
        buttonManageProfile,
        buttonManageFriendsList,
        buttonExit,
    });

    ftxui::Component render = ftxui::Renderer(component, [&] {
        return ftxui::vbox({
            ftxui::text("Main Menu") | ftxui::bold | ftxui::center,
            ftxui::separator(),
            ftxui::text("Welcome to the main menu of Tetris Royal !") | ftxui::center,
            ftxui::separator(),
            buttonPlay->Render(),
            buttonJoinGame->Render(),
            buttonSendMessagesToFriends->Render(),
            buttonLookRanking->Render(),
            buttonManageProfile->Render(),
            buttonManageFriendsList->Render(),
            buttonExit->Render(),
        }) | ftxui::border | ftxui::center;
    });

    screen_->Loop(render);

    return res;
}


void MainMenu::renderRanking(const std::vector<std::tuple<int, std::string, int>> &ranking) {
    std::vector<ftxui::Element> rows;

    // Width of the columns
    const int widthRanking = 10;
    const int widthUser = 30;
    const int widthScore = 10;

    // Title of the table
    rows.push_back(
        ftxui::hbox({
            ftxui::text("Ranking") | ftxui::bold | size(ftxui::WIDTH, ftxui::EQUAL, widthRanking) | ftxui::center,
            ftxui::text("User")    | ftxui::bold | size(ftxui::WIDTH, ftxui::EQUAL, widthUser)    | ftxui::center,
            ftxui::text("Score")   | ftxui::bold | size(ftxui::WIDTH, ftxui::EQUAL, widthScore)   | ftxui::center,
        })
    );
    rows.push_back(ftxui::separator());

    // infos of the ranking table (Ranking, User, Score) with the ranking vector
    for (const auto& [rank, user, score] : ranking) {
        rows.push_back(
            ftxui::hbox({
                // Ranging on the left
                ftxui::text(std::to_string(rank))
                    | size(ftxui::WIDTH, ftxui::EQUAL, widthRanking),

                // User in the middle
                ftxui::text(user)
                    | size(ftxui::WIDTH, ftxui::EQUAL, widthUser),

                // Score on the right
                ftxui::text(std::to_string(score))
                    | size(ftxui::WIDTH, ftxui::EQUAL, widthScore),
            })
        );
    }

    ftxui::Component buttonBack = ftxui::Button("Back", [&] {
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated());

    ftxui::Component container = ftxui::Container::Vertical({
        buttonBack,
    });

    ftxui::Component component = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
            ftxui::text("Endless mod Ranking") | ftxui::bold | ftxui::center,
            ftxui::separator(),
            ftxui::vbox(rows) | ftxui::border,
            ftxui::separator(),
            buttonBack->Render(),
        }) | ftxui::border | ftxui::center;
    });

    screen_->Loop(component);    
}

void MainMenu::renderMessagingMenu(const std::vector<std::string>& friendsList){
    // very bad just for the tests
    Messaging messagingMenue(screen_, friendsList);
    messagingMenue.render();
}

void MainMenu::renderFriendsManager(const std::vector<std:: string> &friendsList) {
    std::vector<ftxui::Component> buttons;
    for (const std::string& friendName : friendsList) {
        buttons.push_back(ftxui::Button(friendName, [&] {
            manageFriendlistScreen(friendName);
        }, ftxui::ButtonOption::Animated()));
    }

    ftxui::Component buttonAddFriend = ftxui::Button("Add a friend", [&] {
        addFriendScreen();
    }, ftxui::ButtonOption::Animated());
        
    ftxui::Component buttonBack = ftxui::Button("Back", [&] {
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated());

    ftxui::Component friendsContainer = ftxui::Container::Vertical({});
    for (const ftxui::Component& button : buttons) {
        friendsContainer->Add(button);
    }

    ftxui::Component addContainer = ftxui::Container::Vertical({
        buttonAddFriend,
    });

    ftxui::Component backContainer = ftxui::Container::Vertical({
        buttonBack,
    });

    ftxui::Component component = ftxui::Renderer(ftxui::Container::Vertical({friendsContainer, addContainer, backContainer}), [&] {
        return ftxui::vbox({
            ftxui::text("Friends List") | ftxui::bold | ftxui::center,
            ftxui::separator(),
            ftxui::text("Your friends") | ftxui::center,
            friendsContainer->Render() | ftxui::border,
            ftxui::separator(),
            addContainer->Render() | ftxui::border,
            ftxui::separator(),
            backContainer->Render() | ftxui::border,
        }) | ftxui::border | ftxui::center;
    });

    screen_->Loop(component);
}

void MainMenu::renderProfileManager() {
    std::string username;
    std::string password;
    std::string msg;

    ftxui::Component inputChangeUsername = ftxui::Input(&username, "New username") | ftxui::border;

    ftxui::Component inputChangePassword = ftxui::Input(&password, "New password") | ftxui::border;

    ftxui::Component submitButton = ftxui::Button("Submit", [&] {
        if (username.empty() && password.empty()) {
            msg = "Please enter a new username or password";
        }
        else {
            screen_->ExitLoopClosure()();
        }
    }, ftxui::ButtonOption::Animated()) | ftxui::border;

    ftxui::Component buttonBack = ftxui::Button("Back", [&] {
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated()) | ftxui::border;

    ftxui::Component container = ftxui::Container::Vertical({
        inputChangeUsername,
        inputChangePassword,
        submitButton,
        buttonBack,
    });

    ftxui::Component component = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
            ftxui::text("Profile Manager") | ftxui::bold | ftxui::center,
            ftxui::separator(),
            ftxui::text("You can change your username and password here") | ftxui::center,
            ftxui::separator(),
            ftxui::text(""), // Empty line
            inputChangeUsername->Render(),
            inputChangePassword->Render(),
            ftxui::text(msg),
            ftxui::separator(),
            submitButton->Render(),
            buttonBack->Render(),
        }) | ftxui::border | ftxui::center;
    });

    screen_->Loop(component);
}


// ### Private methods ###
void MainMenu::manageFriendlistScreen(const std::string &friendName) {

    ftxui::Component buttonYes = ftxui::Button("Yes", [&] {}, ftxui::ButtonOption::Animated()); // TODO: Implement the function to send to server to remove the friend
    ftxui::Component buttonNo = ftxui::Button("No", [&] {
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated()); // Like it's a back button

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


void MainMenu::addFriendScreen() {
    // TODO: communicate with the server to add the friend to the list
    std::string friendName;
    std::string msg;

    ftxui::Component input = ftxui::Input(&friendName, "Name of friend") | ftxui::border | ftxui::center;

    ftxui::Component submitButton = ftxui::Button("Add", [&] {
        if (friendName.empty()) {
            // TODO: add check if name exist with server, etc
            msg = "Please enter a name";
        }
        else {
            screen_->ExitLoopClosure()();
        }
    }, ftxui::ButtonOption::Animated()) | ftxui::border;

    ftxui::Component backButton = ftxui::Button("Back", [&] {
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated()) | ftxui::border;

    ftxui::Component component = ftxui::Renderer(ftxui::Container::Vertical({input, submitButton,backButton}), [&] {
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
}

