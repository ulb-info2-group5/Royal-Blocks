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

#include "../../../core/controller/controller.hpp"
#include "../ftxui_config/ftxui_config.hpp"
#include "ftxui/component/component.hpp"

// ### Constructor ###

GameMenu::GameMenu(ftxui::ScreenInteractive &screen, Controller &controller)
    : screen_(screen), controller_(controller), joinType_(JoinType::NONE),
      typeGame_(TypeGame::NONE), quitMenu_(false) {

    gameDisplay_ =
        std::make_unique<GameDisplay>(screen_, controller_.getGameState());

    endlessButon_ = ftxui::Button(
        "Endless",
        [&] {
            joinType_ = JoinType::ENDLESS;
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());

    duelButon_ = ftxui::Button(
        "Duel",
        [&] {
            gameDisplay_ = std::make_unique<GameDisplay>(
                screen_, controller_.getGameState());
            joinFriendOrRandomScreen();
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());

    classicButon_ = ftxui::Button(
        "Classic",
        [&] {
            gameDisplay_ = std::make_unique<GameDisplay>(
                screen_, controller_.getGameState());
            joinFriendOrRandomScreen();
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());

    royalButon_ = ftxui::Button(
        "Royal",
        [&] {
            gameDisplay_ = std::make_unique<GameDisplay>(
                screen_, controller_.getGameState());
            joinFriendOrRandomScreen();
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());

    backButton_ = ftxui::Button(
        "Back",
        [&] {
            joinType_ = JoinType::BACK;
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());

    quitMenuButton_ = ftxui::Button(
        "Back",
        [&] {
            quitMenu_ = true;
            joinType_ = JoinType::BACK;
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());
}

// ### Private methods ###

void GameMenu::renderAllGames() {
        
    ftxui::Component container = ftxui::Container::Vertical({
        endlessButon_,
        duelButon_,
        classicButon_,
        royalButon_,
        quitMenuButton_,
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
                quitMenuButton_->Render(),
            })
            | ftxui::borderHeavy | ftxui::center
            | ftxui::bgcolor(ftxui::Color::Black);
    });

    screen_.Loop(handleCtrl(renderer));

}

void GameMenu::renderOnlineGames() {
    ftxui::Component container = ftxui::Container::Vertical({
        duelButon_,
        classicButon_,
        royalButon_,
        quitMenuButton_,
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
                quitMenuButton_->Render(),
            })
            | ftxui::borderHeavy | ftxui::center
            | ftxui::bgcolor(ftxui::Color::Black);
    });

    screen_.Loop(handleCtrl(renderer));
}

void GameMenu::joinFriendOrRandomScreen() {
    ftxui::Component joinFriendButton = ftxui::Button(
        "Join a friend",
        [&] {
            joinType_ = JoinType::FRIEND;
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());
    ftxui::Component joinRandomButton = ftxui::Button(
        "Join a random game",
        [&] {
            joinType_ = JoinType::RANDOM;
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());

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
               | ftxui::borderHeavy | ftxui::center
               | ftxui::bgcolor(ftxui::Color::Black);
    });

    screen_.Loop(handleCtrl(renderer));
}

void GameMenu::handleChoice() {
    while (joinType_ != JoinType::BACK) {

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
        joinFriendOrRandomScreen();
    }
}

void GameMenu::joinFriendScreen() {
    const std::vector<bindings::User> &friendsList =
        controller_.getFriendsList().friendsList;

    std::vector<ftxui::Component> friendButtons;

    for (const bindings::User &friendUser : friendsList) {
        if (friendUser.online) {
            friendButtons.push_back(
                makeFriendButton(friendUser.playerId, friendUser.username));
        }
    }

    ftxui::Component friendsContainer =
        ftxui::Container::Vertical(friendButtons);

    ftxui::Component mainContainer = ftxui::Container::Vertical(
        {friendsContainer, backButton_}
    );

    // TODO: do we need this
    // friendsContainer->Add(backButton_);

    ftxui::Component renderer = ftxui::Renderer(mainContainer, [&] {
        return ftxui::vbox({
                   ftxui::text("Select a friend to join") | ftxui::center
                       | ftxui::bold,
                   ftxui::separator(),
                   friendsContainer->Render() | ftxui::borderHeavy,
                   ftxui::separator(),
                   // TODO: do we need this
                   backButton_->Render(),
               })
               | ftxui::borderHeavy | ftxui::center
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
                   | ftxui::borderHeavy | ftxui::center
                   | ftxui::bgcolor(ftxui::Color::Black);
        });

    screen_.Loop(handleCtrl(renderer));
}

ftxui::Component GameMenu::makeFriendButton(PlayerID playerId,
                                            const std::string &friendName) {
    return ftxui::Button(
        friendName,
        [&] {
            // TODO: Ask the controller to send the join request to the server
            // using the playerId
            waitingFriendScreen();
            screen_.ExitLoopClosure()();
        },
        GlobalButtonStyle());
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
                   | ftxui::borderHeavy | ftxui::center
                   | ftxui::bgcolor(ftxui::Color::Black);
        });

    screen_.Loop(handleCtrl(renderer));
}

// ### Public methods ###
void GameMenu::render(const TypeGame &typeGame) {
    typeGame_ = typeGame;
        
    switch (typeGame_) {
    case TypeGame::JOIN_GAME:
        while (!quitMenu_) {
            renderAllGames();
            handleChoice();
        }
        break;

    case TypeGame::CREATE_GAME:
        while (!quitMenu_) {
            renderOnlineGames();
        }
        break;

    default:
        throw std::invalid_argument(
            "Invalid type of game in GameMenu::render()");
        break;
    }
    quitMenu_ = false; // Reset the quitMenu_ variable for the next time we open
                       // the screen
}
