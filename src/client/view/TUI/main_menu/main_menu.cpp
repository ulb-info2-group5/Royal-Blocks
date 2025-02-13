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
    ftxui::Component buttonPlay = ftxui::Button("Play a game", [&] {});
    ftxui::Component buttonJoinGame = ftxui::Button("Join a game", [&] {});
    ftxui::Component buttonSendMessagesToFriends = ftxui::Button("Send messages to friends", [&] {});
    ftxui::Component buttonLookRanking = ftxui::Button("Look at ranking", [&] {});
    ftxui::Component buttonManageProfile = ftxui::Button("Manage profile", [&] {});
    ftxui::Component buttonManageFriendsList = ftxui::Button("Manage friends list", [&] {});
    ftxui::Component buttonExit = ftxui::Button("Exit", [&] {
        exit_ = true;
        screen_->ExitLoopClosure();
    });

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