/**
 * @file game_menu.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Game menu class definition file
 * @date 2025-02-24
 *
 */

#include "game_menu.hpp"
#include <ftxui/dom/elements.hpp>
#include <vector>

#include "../../../controller/controller.hpp"
#include "../handle_ctrl/handle_ctrl.hpp"
#include "ftxui/component/component.hpp"

// ### Constructor ###

GameMenu::GameMenu(ftxui::ScreenInteractive &screen,
                   Controller &controller)
    : screen_(screen), controller_(controller),
      joinType_(JoinType::NONE), typeGame_(TypeGame::NONE) {
     
    gameDisplay_ = std::make_unique<GameDisplay>(screen_, controller_.getGameState());
    

    endlessButon_ = ftxui::Button(
                        "Endless",
                        [&] {
                            joinType_ = JoinType::ENDLESS;
                            screen_.ExitLoopClosure()();
                        },
                        ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
                    | ftxui::border;

    duelButon_ = ftxui::Button(
                     "Duel",
                     [&] {
                         gameDisplay_ = std::make_unique<GameDisplay>(screen_, controller_.getGameState());
                         joinFriendOrRandomScreen();
                         screen_.ExitLoopClosure()();
                     },
                     ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
                 | ftxui::border;

    classicButon_ = ftxui::Button(
                        "Classic",
                        [&] {
                            gameDisplay_ = std::make_unique<GameDisplay>(screen_, controller_.getGameState());
                            joinFriendOrRandomScreen();
                            screen_.ExitLoopClosure()();
                        },
                        ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
                    | ftxui::border;

    royalButon_ = ftxui::Button(
                      "Royal",
                      [&] {
                          gameDisplay_ = std::make_unique<GameDisplay>(screen_, controller_.getGameState());
                          joinFriendOrRandomScreen();
                          screen_.ExitLoopClosure()();
                      },
                      ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
                  | ftxui::border;

    backButton_ = ftxui::Button(
                      "Back",
                      [&] {
                          joinType_ = JoinType::BACK;
                          screen_.ExitLoopClosure()();
                      },
                      ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
                  | ftxui::border;
}

// ### Private methods ###

void GameMenu::renderAllGames() {
    ftxui::Component container = ftxui::Container::Vertical({
        endlessButon_,
        duelButon_,
        classicButon_,
        royalButon_,
        backButton_,
    });

    ftxui::Component renderer = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
                   ftxui::text("Select a game mode") | ftxui::center
                       | ftxui::bold,
                   ftxui::separator(),
                   endlessButon_->Render(),
                   duelButon_->Render(),
                   classicButon_->Render(),
                   royalButon_->Render(),
                   ftxui::separator(),
                   backButton_->Render(),
               })
               | ftxui::border | ftxui::center
               | ftxui::bgcolor(ftxui::Color::Black);
    });

    screen_.Loop(handleCtrl(renderer));
}

void GameMenu::renderOnlineGames() {
    ftxui::Component container = ftxui::Container::Vertical({
        duelButon_,
        classicButon_,
        royalButon_,
        backButton_,
    });

    ftxui::Component renderer = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
                   ftxui::text("Select a game mode") | ftxui::center
                       | ftxui::bold,
                   ftxui::separator(),
                   duelButon_->Render(),
                   classicButon_->Render(),
                   royalButon_->Render(),
                   ftxui::separator(),
                   backButton_->Render(),
               })
               | ftxui::border | ftxui::center
               | ftxui::bgcolor(ftxui::Color::Black);
    });

    screen_.Loop(handleCtrl(renderer));
}

void GameMenu::joinFriendOrRandomScreen() {
    ftxui::Component joinFriendButton =
        ftxui::Button(
            "Join a friend",
            [&] {
                joinType_ = JoinType::FRIEND;
                screen_.ExitLoopClosure()();
            },
            ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
        | ftxui::border;
    ftxui::Component joinRandomButton =
        ftxui::Button(
            "Join a random game",
            [&] {
                joinType_ = JoinType::RANDOM;
                screen_.ExitLoopClosure()();
            },
            ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
        | ftxui::border;

    ftxui::Component container = ftxui::Container::Vertical(
        {joinFriendButton, joinRandomButton, backButton_});

    ftxui::Component renderer = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
                   ftxui::text("Join a friend or a random game") | ftxui::center
                       | ftxui::bold,
                   ftxui::separator(),
                   joinFriendButton->Render(),
                   joinRandomButton->Render(),
                   ftxui::separator(),
                   backButton_->Render(),
               })
               | ftxui::border | ftxui::center
               | ftxui::bgcolor(ftxui::Color::Black);
    });

    screen_.Loop(handleCtrl(renderer));
}

void GameMenu::handleChoice() {
    switch (joinType_) {
    case JoinType::FRIEND:
        joinFriendScreen();
        break;

    case JoinType::RANDOM:
        joinRandomScreen();
        break;

    case JoinType::ENDLESS:
        gameDisplay_->render(); // Endless mode is directly started without
                               // waiting for a friend or a random game
        break;

    case JoinType::BACK: // Do nothing because the user pressed the back button
        break;

    default:
        throw std::invalid_argument(
            "Invalid state in GameMenu::handleChoice()");
        break;
    }
}

void GameMenu::joinFriendScreen() {
    const std::vector<std::string> friendsList =
        controller_.getFriendsOnline();

    std::vector<ftxui::Component> friendButtons;

    for (const std::string &friendName : friendsList) {
        friendButtons.push_back(makeFriendButton(friendName));
    }

    ftxui::Component friendsContainer =
        ftxui::Container::Vertical(friendButtons);

    for (const ftxui::Component &friendButton : friendButtons) {
        friendsContainer->Add(friendButton);
    }

    friendButtons.push_back(backButton_);

    ftxui::Component renderer = ftxui::Renderer(friendsContainer, [&] {
        return ftxui::vbox({
                   ftxui::text("Select a friend to join") | ftxui::center
                       | ftxui::bold,
                   ftxui::separator(),
                   friendsContainer->Render() | ftxui::border,
                   ftxui::separator(),
                   backButton_->Render(),
               })
               | ftxui::border | ftxui::center
               | ftxui::bgcolor(ftxui::Color::Black);
    });

    screen_.Loop(handleCtrl(renderer));
}

void GameMenu::joinRandomScreen() {
    ftxui::Component renderer =
        ftxui::Renderer(ftxui::Container::Vertical({}), [&] {
            return ftxui::vbox({
                       ftxui::text("Searching for a random game")
                           | ftxui::center | ftxui::bold,
                       ftxui::separator(),
                       ftxui::text("Please wait ...") | ftxui::center,
                   })
                   | ftxui::border | ftxui::center
                   | ftxui::bgcolor(ftxui::Color::Black);
        });

    screen_.Loop(handleCtrl(renderer));
}

ftxui::Component GameMenu::makeFriendButton(const std::string &friendName) {
    return ftxui::Button(
        friendName,
        [&] {
            // TODO: communicate with the server to join the friend here ?
            waitingFriendScreen();
            screen_.ExitLoopClosure()();
        },
        ftxui::ButtonOption::Animated(ftxui::Color::Grey0));
}

void GameMenu::waitingFriendScreen() {
    // TODO: communicate with the server to join the friend here ?
    ftxui::Component renderer =
        ftxui::Renderer(ftxui::Container::Vertical({}), [&] {
            return ftxui::vbox({
                       ftxui::text("Waiting for the friend to start the game")
                           | ftxui::center | ftxui::bold,
                       ftxui::separator(),
                       ftxui::text("Please wait ...") | ftxui::center,
                   })
                   | ftxui::border | ftxui::center
                   | ftxui::bgcolor(ftxui::Color::Black);
        });

    screen_.Loop(handleCtrl(renderer));
}

// ### Public methods ###
void GameMenu::render(const TypeGame &typeGame) {
    typeGame_ = typeGame;
    switch (typeGame_) {
    case TypeGame::JOIN_GAME:
        renderAllGames();
        handleChoice();
        break;

    case TypeGame::CREATE_GAME:
        renderOnlineGames();
        break;

    default:
        throw std::invalid_argument(
            "Invalid type of game in GameMenu::render()");
        break;
    }
}
