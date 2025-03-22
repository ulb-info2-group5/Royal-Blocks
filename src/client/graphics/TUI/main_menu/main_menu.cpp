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
#include "../main_tui.hpp"

// ### Constructor ###
MainMenu::MainMenu(MainTui &mainTui, Controller &controller)
    : mainTui_(mainTui), controller_(controller), state_(MainMenuState::NONE),
      friendsMenu_(mainTui_, controller), messagingMenu_(mainTui_, controller),
      gameMenu_(mainTui_, controller) {

    createMainMenuButtons();

    buttonBack_ = ftxui::Button(
        std::string(STR_BACK),
        [&] {
            state_ = MainMenuState::BACK;
            mainTui_.stopRender();
        },
        GlobalButtonStyle());

    buttonOK_ = ftxui::Button(
        std::string(STR_OK),
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
        std::string(STR_CREATE_GAME),
        [&] {
            state_ = MainMenuState::CREATE_GAME;
            mainTui_.stopRender();
        },
        GlobalButtonStyle());

    buttonJoinGame_ = ftxui::Button(
        std::string(STR_JOIN_GAME),
        [&] {
            state_ = MainMenuState::JOIN_GAME;
            mainTui_.stopRender();
        },
        GlobalButtonStyle());

    buttonSendMessagesToFriends_ = ftxui::Button(
        std::string(STR_MESSAGES),
        [&] {
            state_ = MainMenuState::SEND_MESSAGES_TO_FRIENDS;
            mainTui_.stopRender();
        },
        GlobalButtonStyle());

    buttonLookRanking_ = ftxui::Button(
        std::string(STR_RANKING),
        [&] {
            state_ = MainMenuState::LOOK_RANKING;
            mainTui_.stopRender();
        },
        GlobalButtonStyle());

    buttonManageProfile_ = ftxui::Button(
        std::string(STR_MANAGE_PROFILE),
        [&] {
            state_ = MainMenuState::MANAGE_PROFILE;
            mainTui_.stopRender();
        },
        GlobalButtonStyle());

    buttonManageFriendsList_ = ftxui::Button(
        std::string(STR_MANAGE_FRIENDS_LIST),
        [&] {
            state_ = MainMenuState::MANAGE_FRIENDS_LIST;
            mainTui_.stopRender();
        },
        GlobalButtonStyle());

    buttonExit_ = ftxui::Button(
        std::string(STR_QUIT_GAME),
        [&] {
            state_ = MainMenuState::EXIT;
            mainTui_.stopRender();
        },
        GlobalButtonStyle());
}

void MainMenu::displayMainWindow() {
    mainMenuWindow_ = ftxui::Renderer(
        ftxui::Container::Vertical({
            buttonPlay_,
            buttonJoinGame_,
            buttonSendMessagesToFriends_,
            buttonLookRanking_,
            buttonManageProfile_,
            buttonManageFriendsList_,
            buttonExit_,
        }),
        [&] {
            return ftxui::vbox({
                       ftxui::text(std::string(STR_MAIN_MENU)) | ftxui::bold
                           | ftxui::center | ftxui::color(ftxui::Color::Cyan),
                       ftxui::separator(),
                       ftxui::text(std::string(STR_WELCOME)) | ftxui::center,
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

void MainMenu::displayRankingWindow() {
    ftxui::Component container = ftxui::Container::Vertical({
        buttonBack_,
    });

    rankingWindow_ = ftxui::Renderer(container, [&] {
        std::vector<ftxui::Element> rows;

        constexpr int widthRanking = 10;
        constexpr int widthUser = 30;
        constexpr int widthScore = 10;

        // Title of the ranking
        rows.push_back(ftxui::hbox({
                           ftxui::text(std::string(STR_RANKING)) | ftxui::bold
                               | size(ftxui::WIDTH, ftxui::EQUAL, widthRanking)
                               | ftxui::center,
                           ftxui::text("   "),
                           ftxui::text(std::string(STR_USER)) | ftxui::bold
                               | size(ftxui::WIDTH, ftxui::EQUAL, widthUser)
                               | ftxui::center,
                           ftxui::text("   "),
                           ftxui::text(std::string(STR_SCORE)) | ftxui::bold
                               | size(ftxui::WIDTH, ftxui::EQUAL, widthScore)
                               | ftxui::center,
                       })
                       | ftxui::center);
        rows.push_back(ftxui::separator());

        // Ranking of the players
        for (auto [rank, player] :
             std::views::enumerate(controller_.getRanking())) {
            const auto &[user, score] = player;

            rows.push_back(
                ftxui::hbox({
                    ftxui::text(std::to_string(rank + 1))
                        | size(ftxui::WIDTH, ftxui::EQUAL, widthRanking)
                        | ftxui::center,
                    ftxui::text("   "),
                    ftxui::text(user)
                        | size(ftxui::WIDTH, ftxui::EQUAL, widthUser)
                        | ftxui::center,
                    ftxui::text("   "),
                    ftxui::text(std::to_string(score))
                        | size(ftxui::WIDTH, ftxui::EQUAL, widthScore)
                        | ftxui::center,
                })
                | ftxui::center);
        }

        return ftxui::vbox({
                   ftxui::text(std::string(STR_ENDLESS_RANKING)) | ftxui::bold
                       | ftxui::center,
                   ftxui::separator(),
                   ftxui::vbox(rows) | ftxui::borderHeavy,
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
        ftxui::Input(&username_, std::string(STR_NEW_USERNAME))
        | ftxui::borderHeavy;

    inputChangePassword_ =
        ftxui::Input(&password_, std::string(STR_NEW_PASSWORD),
                     PasswordInputOption())
        | ftxui::borderHeavy;

    submitButton_ = ftxui::Button(
        std::string(STR_SUBMIT),
        [&] {
            controller_.changeProfile(username_, password_); // profile screen
            mainTui_.stopRender();
        },
        GlobalButtonStyle());
}

void MainMenu::displayProfileManagerWindow() {
    displayProfileManagerButton();

    profileManagerWindow_ = ftxui::Renderer(
        ftxui::Container::Vertical({inputChangeUsername_, inputChangePassword_,
                                    submitButton_, buttonBack_}),
        [&] {
            return ftxui::vbox({
                       ftxui::text(std::string(STR_PROFILE_MANAGER))
                           | ftxui::bold | ftxui::center,
                       ftxui::separator(),
                       ftxui::text(std::string(STR_CHANGE_INFO))
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

    mainTui_.render(rankingWindow_);
}

void MainMenu::renderProfileManager() {

    displayProfileManagerWindow();

    mainTui_.render(profileManagerWindow_);
}

// ### Public methods ###
void MainMenu::render() {
    while (state_ != MainMenuState::EXIT) {
        displayMainWindow();
        mainTui_.render(mainMenuWindow_);
        handleChoice();
    }
}
