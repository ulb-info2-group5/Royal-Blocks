/**
 * @file main_menu.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief MainMenu class definition file
 * @date 2025-02-12
 *
 */

#include "main_menu.hpp"
#include "../../../core/controller/controller.hpp"
#include "../ftxui_config/ftxui_config.hpp"
#include "../messaging/messaging.hpp"

#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>

// ### Constructor ###
MainMenu::MainMenu(ftxui::ScreenInteractive &screen, Controller &controller)
    : screen_(screen), controller_(controller), state_(MainMenuState::NONE),
      friendsMenu_(screen, controller), messagingMenu_(screen, controller),
      gameMenu_(screen, controller) {

    createMainMenuButtons();

    buttonBack_ = ftxui::Button(
        "Back",
        [&] {
            state_ = MainMenuState::BACK;
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());

    buttonOK_ = ftxui::Button(
        "OK",
        [&] {
            state_ =
                MainMenuState::BACK; // like a back button but with ok title
        },
        GlobalButtonStyle());
}

// ### Private methods ###
void MainMenu::handleChoice() {
    switch (state_) {
    case MainMenuState::CREATE_GAME:
        gameMenu_.render(
            TypeGame::CREATE_GAME); // Can only create a game online
        break;

    case MainMenuState::JOIN_GAME:
        gameMenu_.render(TypeGame::JOIN_GAME); // Can join all the games modes
        break;

    case MainMenuState::SEND_MESSAGES_TO_FRIENDS:
        messagingMenu_.render();
        break;

    case MainMenuState::LOOK_RANKING:
        renderRanking();
        break;

    case MainMenuState::MANAGE_PROFILE:
        renderProfileManager();
        break;

    case MainMenuState::MANAGE_FRIENDS_LIST:
        friendsMenu_.render();
        break;

    case MainMenuState::EXIT:
        break;

    case MainMenuState::BACK:
        break;

    case MainMenuState::NONE:
        break;

    default:
        throw std::invalid_argument(
            "Invalid state in MainMenu::handleChoice()");
        break;
    }
}

// ### Protected methods ###

void MainMenu::createMainMenuButtons() {
    buttonPlay_ = ftxui::Button(
        "▶ Create a game",
        [&] {
            state_ = MainMenuState::CREATE_GAME;
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());

    buttonJoinGame_ = ftxui::Button(
        "▶ Join a game",
        [&] {
            state_ = MainMenuState::JOIN_GAME;
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());

    buttonSendMessagesToFriends_ = ftxui::Button(
        "💬 Messages",
        [&] {
            state_ = MainMenuState::SEND_MESSAGES_TO_FRIENDS;
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());

    buttonLookRanking_ = ftxui::Button(
        "🏆 Leaderboard",
        [&] {
            state_ = MainMenuState::LOOK_RANKING;
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());

    buttonManageProfile_ = ftxui::Button(
        "⚙ Manage Profile",
        [&] {
            state_ = MainMenuState::MANAGE_PROFILE;
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());

    buttonManageFriendsList_ = ftxui::Button(
        "👥 Manage friends list",
        [&] {
            state_ = MainMenuState::MANAGE_FRIENDS_LIST;
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());

    buttonExit_ = ftxui::Button(
        "Quit the game",
        [&] {
            state_ = MainMenuState::EXIT;
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());
}

void MainMenu::displayMainWindow() {
    ftxui::Component buttonDisplay = ftxui::Container::Vertical({
        buttonPlay_,
        buttonJoinGame_,
        buttonSendMessagesToFriends_,
        buttonLookRanking_,
        buttonManageProfile_,
        buttonManageFriendsList_,
        buttonExit_,
    });

    mainMenuWindow_ = ftxui::Renderer(buttonDisplay, [&] {
        return ftxui::vbox({
                   ftxui::text("🎮 Main Menu 🎮") | ftxui::bold | ftxui::center
                       | ftxui::color(ftxui::Color::Cyan),
                   ftxui::separator(),
                   ftxui::text("Welcome to the game menu of Tetris Royal !")
                       | ftxui::center,
                   ftxui::separator(),
                   buttonPlay_->Render(),
                   buttonJoinGame_->Render(),
                   buttonSendMessagesToFriends_->Render(),
                   buttonLookRanking_->Render(),
                   buttonManageProfile_->Render(),
                   buttonManageFriendsList_->Render(),
                   buttonExit_->Render(),
               })
               | ftxui::borderHeavy | ftxui::center;
    });
}

void MainMenu::displayRankingList() {
    rowsRanking_.clear();

    // column width
    constexpr int widthRanking = 10;
    constexpr int widthUser = 30;
    constexpr int widthScore = 10;

    // table titles
    rowsRanking_.push_back(ftxui::hbox({
        ftxui::text("Ranking") | ftxui::bold
            | size(ftxui::WIDTH, ftxui::EQUAL, widthRanking) | ftxui::center,
        ftxui::text("User") | ftxui::bold
            | size(ftxui::WIDTH, ftxui::EQUAL, widthUser) | ftxui::center,
        ftxui::text("Score") | ftxui::bold
            | size(ftxui::WIDTH, ftxui::EQUAL, widthScore) | ftxui::center,
    }));
    rowsRanking_.push_back(ftxui::separator());

    for (auto [rank, player] :
         std::views::enumerate(controller_.getRanking())) {
        const auto &[user, score] = player;

        rowsRanking_.push_back(ftxui::hbox({
            ftxui::text(std::to_string(rank + 1))
                | size(ftxui::WIDTH, ftxui::EQUAL, widthRanking),

            ftxui::text(user) | size(ftxui::WIDTH, ftxui::EQUAL, widthUser),

            ftxui::text(std::to_string(score))
                | size(ftxui::WIDTH, ftxui::EQUAL, widthScore),
        }));
    }
}

void MainMenu::displayRankingWindow() {
    displayRankingList();

    ftxui::Component container = ftxui::Container::Vertical({
        buttonBack_,
    });

    rankingWindow_ = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
                   ftxui::text("Endless mod Ranking") | ftxui::bold
                       | ftxui::center,
                   ftxui::separator(),
                   ftxui::vbox(rowsRanking_) | ftxui::borderHeavy,
                   ftxui::separator(),
                   buttonBack_->Render(),
               })
               | ftxui::borderHeavy | ftxui::center;
    });
}

void MainMenu::displayProfileManagerButton() {
    username_.clear(); // Empty username
    password_.clear(); // Empty password

    inputChangeUsername_ =
        ftxui::Input(&username_, "New username") | ftxui::borderHeavy;

    inputChangePassword_ =
        ftxui::Input(&password_, "New password", PasswordInputOption())
        | ftxui::borderHeavy;

    submitButton_ = ftxui::Button(
        "Submit",
        [&] {
            controller_.changeProfile(username_, password_); // profile screen
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());
}

void MainMenu::displayProfileManagerWindow() {

    displayProfileManagerButton();

    ftxui::Component container =
        ftxui::Container::Vertical({inputChangeUsername_, inputChangePassword_,
                                    submitButton_, buttonBack_});

    profileManagerWindow_ = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
                   ftxui::text("Profile Manager") | ftxui::bold | ftxui::center,
                   ftxui::separator(),
                   ftxui::text("You can change your username and password here")
                       | ftxui::center,
                   ftxui::separator(),
                   inputChangeUsername_->Render(),
                   inputChangePassword_->Render(),
                   ftxui::separator(),
                   submitButton_->Render(),
                   ftxui::separator(),
                   buttonBack_->Render(),
               })
               | ftxui::borderHeavy | ftxui::center;
    });
}

void MainMenu::renderRanking() {

    displayRankingWindow();

    screen_.Loop(handleCtrl(rankingWindow_));
}

void MainMenu::renderProfileManager() {

    displayProfileManagerWindow();

    screen_.Loop(handleCtrl(profileManagerWindow_));
}

// ### Public methods ###
void MainMenu::render() {
    while (state_ != MainMenuState::EXIT) {
        displayMainWindow();
        screen_.Loop(handleCtrl(mainMenuWindow_));
        handleChoice();
    }
}
