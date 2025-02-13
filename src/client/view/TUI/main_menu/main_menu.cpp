/**
 * @file main_menu.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief MainMenu class definition file
 * @date 2025-02-12
 * 
 */

#include "main_menu.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

// ### Public methods ###
MainMenu::MainMenu(std::shared_ptr<ftxui::ScreenInteractive> screen) : screen_(screen) {}

void MainMenu::render() {
    auto buttonPlay = ftxui::Button("Play a game", [&] {});
    auto buttonJoinGame = ftxui::Button("Join a game", [&] {});
    auto buttonSendMessagesToFriends = ftxui::Button("Send messages to friends", [&] {});
    auto buttonLookRanking = ftxui::Button("Look at ranking", [&] {});
    auto buttonManageProfile = ftxui::Button("Manage profile", [&] {});
    auto buttonManageFriendsList = ftxui::Button("Manage friends list", [&] {});
    auto buttonExit = ftxui::Button("Exit", [&] {
        exit_ = true;
        screen_->ExitLoopClosure();
    });

    auto component = ftxui::Container::Vertical({
        buttonPlay,
        buttonJoinGame,
        buttonSendMessagesToFriends,
        buttonLookRanking,
        buttonManageProfile,
        buttonManageFriendsList,
        buttonExit,
    });

    auto render = ftxui::Renderer(component, [&] {
        if (exit_) {
            screen_->ExitLoopClosure()();
        }
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
        }) | ftxui::border;
    });

    screen_->Loop(render);
}