/**
 * @file game_menu.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Game menu class definition file
 * @date 2025-02-24
 *
 */

#include "game_menu.hpp"

#include "../../../core/controller/controller.hpp"
#include "../ftxui_config/ftxui_config.hpp"
#include "../game_display/game_display.hpp"
#include "../main_tui.hpp"

// ### Constructor ###

GameMenu::GameMenu(MainTui &mainTui, Controller &controller)
    : mainTui_(mainTui), controller_(controller),
      joinType_(JoinType::NONE), typeGame_(TypeGame::NONE), quitMenu_(false) {

    gameDisplay_ = std::make_unique<GameDisplay>(mainTui_, controller_);

    endlessButon_ = ftxui::Button(
        std::string(STR_ENDLESS),
        [&] {
            gameMode_ = GameMode::Endless;
            controller_.joinGame(gameMode_, std::nullopt);
            mainTui_.stopRender();
        },
        GlobalButtonStyle());

    duelButon_ = ftxui::Button(
        std::string(STR_DUAL),
        [&] {
            gameMode_ = GameMode::Dual;
            mainTui_.stopRender();
        },
        GlobalButtonStyle());

    classicButon_ = ftxui::Button(
        std::string(STR_CLASSIC),
        [&] {
            gameMode_ = GameMode::Classic;
            mainTui_.stopRender();
        },
        GlobalButtonStyle());

    royalButon_ = ftxui::Button(
        std::string(STR_ROYAL),
        [&] {
            gameMode_ = GameMode::RoyalCompetition;
            mainTui_.stopRender();
        },
        GlobalButtonStyle());

    backButton_ = ftxui::Button(
        std::string(STR_BACK),
        [&] {
            joinType_ = JoinType::BACK;
            mainTui_.stopRender();
        },
        GlobalButtonStyle());

    quitMenuButton_ = ftxui::Button(
        std::string(STR_BACK),
        [&] {
            quitMenu_ = true;
            joinType_ = JoinType::BACK;
            mainTui_.stopRender();
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
                   ftxui::text(std::string(STR_SELECT_MOD)) | ftxui::center
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

    mainTui_.render(renderer);

    if (!quitMenu_) {
        joinFriendOrRandomScreen();
        handleChoice();
    }
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
                   ftxui::text(std::string(STR_SELECT_MOD)) | ftxui::center
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

    mainTui_.render(renderer);

    if (!quitMenu_) {
        selectPlayerCountScreen();
    }
}

void GameMenu::joinFriendOrRandomScreen() {
    if (gameMode_ == GameMode::Endless) {
        return; // Endless mode is directly started without waiting for a friend
                // or a random game
    }

    ftxui::Component joinFriendButton = ftxui::Button(
        std::string(STR_JOIN_FRIEND),
        [&] {
            joinType_ = JoinType::FRIEND;
            mainTui_.stopRender();
        },
        GlobalButtonStyle());
    ftxui::Component joinRandomButton = ftxui::Button(
        std::string(STR_JOIN_RANDOM),
        [&] {
            joinType_ = JoinType::RANDOM;
            controller_.joinGame(gameMode_, std::nullopt);
            mainTui_.stopRender();
        },
        GlobalButtonStyle());

    ftxui::Component container = ftxui::Container::Vertical(
        {joinFriendButton, joinRandomButton, backButton_});

    ftxui::Component renderer = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
                   ftxui::text(std::string(STR_JOIN_FRIEND_OR_RANDOM))
                       | ftxui::center | ftxui::bold,
                   ftxui::separator(),
                   joinFriendButton->Render(),
                   joinRandomButton->Render(),
                   ftxui::separator(),
                   backButton_->Render(),
               })
               | ftxui::borderHeavy | ftxui::center
               | ftxui::bgcolor(ftxui::Color::Black);
    });

    mainTui_.render(renderer);
}

void GameMenu::handleChoice() {
    if (gameMode_ == GameMode::Endless) {
        quitMenu_ = true; // Set the quitMenu_ variable to true to exit the menu
                          // loop when the game is finished
        mainTui_.stopRender();
        gameDisplay_->render(); // Endless mode is directly started without
                                // waiting for a friend or a random game
        return;
    }

    while (joinType_ != JoinType::BACK) {

        if (joinType_ == JoinType::FRIEND) {
            joinFriendScreen();
            // TODO: Launch the game when the friend screen has been exited
            // because the game has started ?
        }

        else if (joinType_ == JoinType::RANDOM) {
            joinRandomScreen(); // We can exit the random screen when the game
                                // just if the game has started
            gameDisplay_->render(); // The game has started because the random
                                    // screen has been exited
            quitMenu_ = true;
            break;
        }
        joinFriendOrRandomScreen(); // If the user goes back to the previous
                                    // screen
    }
}

void GameMenu::joinFriendScreen() {

    ftxui::Component friendsContainer = ftxui::Container::Vertical({});

    auto updateFriendsList = [&] {
        friendsContainer->DetachAllChildren();
        const std::vector<bindings::User> &friendsList =
            controller_.getFriendsList();

        if (friendsList.empty()) {
            ftxui::Component renderNoFriends =
                ftxui::Renderer(ftxui::Container::Vertical({}), [&] {
                    return ftxui::vbox({
                        ftxui::text(std::string(STR_NO_FRIEND)),
                    });
                });
            friendsContainer->Add(renderNoFriends);
            return;
        }

        for (const bindings::User &friendUser : friendsList) {
            if (friendUser.isJoinable() && friendUser.gameMode == gameMode_) {
                friendsContainer->Add(
                    makeFriendButton(friendUser.userID, friendUser.username));
            }
        }
    };

    ftxui::Component mainContainer =
        ftxui::Container::Vertical({friendsContainer, backButton_});

    ftxui::Component renderer = ftxui::Renderer(mainContainer, [&] {
        updateFriendsList();
        return ftxui::vbox({
                   ftxui::text(std::string(STR_SELECT_FRIEND_TO_JOIN))
                       | ftxui::center | ftxui::bold,
                   ftxui::separator(),
                   friendsContainer->Render() | ftxui::borderHeavy,
                   ftxui::separator(),
                   backButton_->Render(),
               })
               | ftxui::borderHeavy | ftxui::center
               | ftxui::bgcolor(ftxui::Color::Black);
    });

    mainTui_.render(renderer);
}

void GameMenu::joinRandomScreen() {
    ftxui::Component renderer =
        ftxui::Renderer(ftxui::Container::Vertical({}), [&] {
            if (controller_.gameHasStarted()) {
                mainTui_.stopRender();
            }

            return ftxui::vbox({
                       ftxui::text("Searching for a random game")
                           | ftxui::center | ftxui::bold,
                       ftxui::separator(),
                       ftxui::text("Please wait ...") | ftxui::center,
                   })
                   | ftxui::borderHeavy | ftxui::center
                   | ftxui::bgcolor(ftxui::Color::Black);
        });

    mainTui_.render(renderer);
}

void GameMenu::createGameScreen() {
    ftxui::Component renderer =
        ftxui::Renderer(ftxui::Container::Vertical({}), [&] {
            if (controller_.gameHasStarted()) {
                mainTui_.stopRender();
            }

            return ftxui::vbox({
                       ftxui::text("Game is launching") | ftxui::center
                           | ftxui::bold,
                       ftxui::separator(),
                       ftxui::text("Please wait ...") | ftxui::center,
                   })
                   | ftxui::borderHeavy | ftxui::center
                   | ftxui::bgcolor(ftxui::Color::Black);
        });

    mainTui_.render(renderer);
}

ftxui::Component GameMenu::makeFriendButton(UserID userID,
                                            const std::string &friendName) {
    return ftxui::Button(
        friendName,
        [this, userID] {
            controller_.joinGame(gameMode_, userID);
            waitingFriendScreen();
            mainTui_.stopRender();
        },
        GlobalButtonStyle());
}

void GameMenu::waitingFriendScreen() {
    // TODO: communicate with the server to join the friend here ?
    ftxui::Component renderer =
        ftxui::Renderer(ftxui::Container::Vertical({}), [&] {
            return ftxui::vbox({
                       ftxui::text(std::string(STR_WAITING_FRIEND))
                           | ftxui::center | ftxui::bold,
                       ftxui::separator(),
                       ftxui::text(std::string(STR_WAIT)) | ftxui::center,
                   })
                   | ftxui::borderHeavy | ftxui::center
                   | ftxui::bgcolor(ftxui::Color::Black);
        });

    mainTui_.render(renderer);
}

// ### Public methods ###
void GameMenu::render(const TypeGame &typeGame) {
    typeGame_ = typeGame;

    switch (typeGame_) {
    case TypeGame::JOIN_GAME:
        while (!quitMenu_) {
            renderAllGames();
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
    quitMenu_ = false; // Reset the quitMenu_ variable for the next time we
                       // open the screen
}

void GameMenu::selectPlayerCountScreen() {
    if (gameMode_ == GameMode::Dual) {
        controller_.createGame(gameMode_, 2);
        createGameScreen();
        mainTui_.stopRender();
        return;
    }
    const int minPlayers = 3;
    const int maxPlayers = 9;
    int playerCount = minPlayers;

    ftxui::Component minButton = ftxui::Button(
        " - ",
        [&] {
            if (playerCount > minPlayers) playerCount--;
        },
        GlobalButtonStyle());

    ftxui::Component plusButton = ftxui::Button(
        " + ",
        [&] {
            if (playerCount < maxPlayers) playerCount++;
        },
        GlobalButtonStyle());

    ftxui::Component confirmButton = ftxui::Button(
        std::string(STR_CONFIRM),
        [&] {
            controller_.createGame(gameMode_, playerCount);
            createGameScreen();
            mainTui_.stopRender();
        },
        GlobalButtonStyle());

    ftxui::Component horizontalContainer = ftxui::Container::Horizontal({
        minButton,
        ftxui::Renderer([&] {
            return ftxui::text(
                " " + std::to_string(playerCount)
                + " "); // set space between the number and the buttons
        }),
        plusButton,
    });

    ftxui::Component container = ftxui::Container::Vertical({
        horizontalContainer,
        confirmButton,
        backButton_,
    });

    ftxui::Component renderer = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
                   ftxui::text(std::string(STR_SELECT_NUM_PLAYERS))
                       | ftxui::center | ftxui::bold,
                   ftxui::separator(),
                   horizontalContainer->Render() | ftxui::center,
                   confirmButton->Render() | ftxui::center,
                   ftxui::separator(),
                   backButton_->Render() | ftxui::center,
               })
               | ftxui::borderHeavy | ftxui::center
               | ftxui::bgcolor(ftxui::Color::Black);
    });

    mainTui_.render(renderer);
}
