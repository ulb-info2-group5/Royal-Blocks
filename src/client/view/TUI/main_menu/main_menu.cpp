/**
 * @file main_menu.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief MainMenu class definition file
 * @date 2025-02-12
 * 
 */

#include "main_menu.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <memory>
#include <string>

// ### Public methods ###
MainMenu::MainMenu(std::shared_ptr<ftxui::ScreenInteractive> screen) : screen_(screen) {}

void MainMenu::render() {
    ftxui::Component buttonPlay = ftxui::Button("Play a game", [&] {});
    ftxui::Component buttonJoinGame = ftxui::Button("Join a game", [&] {});
    ftxui::Component buttonSendMessagesToFriends = ftxui::Button("Send messages to friends", [&] {});
    ftxui::Component buttonLookRanking = ftxui::Button("Look at ranking", [&] {
        // TODO: It's an example, must remove it
        std::vector<std::tuple<int, std::string, int>> ranking = {
            {1, "Player1", 1500},
            {2, "Player2", 1200},
            {3, "ethan", 900},
            {4, "readyPlayerOne", 800},
            {5, "theBestPlayerOfTheGame", 750}
        };
        renderRanking(ranking);
    });
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
        if (exit_ == true) {
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
        }) | ftxui::border | ftxui::center;
    });

    screen_->Loop(render);
}


// ### Private methods ###
void MainMenu::renderRanking(std::vector<std::tuple<int, std::string, int>> ranking) {
    bool exit = false;
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
    for (auto& [rank, user, score] : ranking) {
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

    // Bouton "Back"
    auto buttonBack = ftxui::Button("Back", [&] {
        exit = true;
        screen_->ExitLoopClosure()();
    });

    auto container = ftxui::Container::Vertical({
        buttonBack,
    });

    auto component = ftxui::Renderer(container, [&] {
        if (exit) {
            screen_->ExitLoopClosure()();
        }
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




