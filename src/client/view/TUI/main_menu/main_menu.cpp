/**
 * @file main_menu.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief MainMenu class definition file
 * @date 2025-02-12
 *
 */

#include "main_menu.hpp"
#include "../../../controller/controller.hpp"
#include "../messaging/messaging.hpp"

#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <vector>

// ### Constructor ###
MainMenu::MainMenu(ftxui::ScreenInteractive &screen,
                   Controller *controller)
    : screen_(screen), controller_(controller), state_(MainMenuState::NONE),
      friendsMenu_(screen, controller),
      messagingMenu_(screen, controller),
      gameMenu_(screen, controller) {

    createMainMenuButtons();    

    buttonBack_ = ftxui::Button(
                      "Back",
                      [&] {
                          state_ = MainMenuState::BACK;
                          screen_.ExitLoopClosure()();
                      },
                      ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
                  | ftxui::border;

    buttonOK_ =
        ftxui::Button(
            "OK",
            [&] {
                state_ =
                    MainMenuState::BACK; // like a back button but with ok title
            },
            ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
        | ftxui::border;
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

void MainMenu::confirmUpdateProfileScreen() const {
    ftxui::Component okButton =
        ftxui::Button(
            "OK", [&] { screen_.ExitLoopClosure()(); },
            ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
        | ftxui::border;

    ftxui::Component component =
        ftxui::Renderer(ftxui::Container::Vertical({okButton}), [&] {
            return ftxui::vbox({
                       ftxui::text("Friend added successfully") | ftxui::bold
                           | ftxui::center,
                       ftxui::separator(),
                       okButton->Render() | ftxui::center,
                   })
                   | ftxui::border | ftxui::center;
        });

    screen_.Loop(component);
}

// ### Protected methods ###

void MainMenu::createMainMenuButtons() {
    buttonPlay_ = ftxui::Button(
                      "Create a game",
                      [&] {
                          state_ = MainMenuState::CREATE_GAME;
                          screen_.ExitLoopClosure()();
                      },
                      ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
                  | ftxui::border;

    buttonJoinGame_ = ftxui::Button(
                          "Join a game",
                          [&] {
                              state_ = MainMenuState::JOIN_GAME;
                              screen_.ExitLoopClosure()();
                          },
                          ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
                      | ftxui::border;

    buttonSendMessagesToFriends_ =
        ftxui::Button(
            "Send messages to friends",
            [&] {
                state_ = MainMenuState::SEND_MESSAGES_TO_FRIENDS;
                screen_.ExitLoopClosure()();
            },
            ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
        | ftxui::border;

    buttonLookRanking_ = ftxui::Button(
                             "Look at ranking",
                             [&] {
                                 state_ = MainMenuState::LOOK_RANKING;
                                 screen_.ExitLoopClosure()();
                             },
                             ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
                         | ftxui::border;

    buttonManageProfile_ =
        ftxui::Button(
            "Manage profile",
            [&] {
                state_ = MainMenuState::MANAGE_PROFILE;
                screen_.ExitLoopClosure()();
            },
            ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
        | ftxui::border;

    buttonManageFriendsList_ =
        ftxui::Button(
            "Manage friends list",
            [&] {
                state_ = MainMenuState::MANAGE_FRIENDS_LIST;
                screen_.ExitLoopClosure()();
            },
            ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
        | ftxui::border;

    buttonExit_ = ftxui::Button(
                      "Exit",
                      [&] {
                          state_ = MainMenuState::EXIT;
                          screen_.ExitLoopClosure()();
                      },
                      ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
                  | ftxui::border;
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
                   ftxui::text("Main Menu") | ftxui::bold | ftxui::center,
                   ftxui::separator(),
                   ftxui::text("Welcome to the main menu of Tetris Royal !")
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
               | ftxui::border | ftxui::center;
    });
}

void MainMenu::displayRankingList() {

    // Get the ranking from the controller
    const std::vector<std::tuple<int, std::string, int>> ranking =
        controller_->getRanking();

    // Clear the rows of the ranking table to avoid duplicates
    rowsRanking_.clear();

    // Width of the columns
    const int widthRanking = 10;
    const int widthUser = 30;
    const int widthScore = 10;

    // Title of the table
    rowsRanking_.push_back(ftxui::hbox({
        ftxui::text("Ranking") | ftxui::bold
            | size(ftxui::WIDTH, ftxui::EQUAL, widthRanking) | ftxui::center,
        ftxui::text("User") | ftxui::bold
            | size(ftxui::WIDTH, ftxui::EQUAL, widthUser) | ftxui::center,
        ftxui::text("Score") | ftxui::bold
            | size(ftxui::WIDTH, ftxui::EQUAL, widthScore) | ftxui::center,
    }));
    rowsRanking_.push_back(ftxui::separator());

    // infos of the ranking table (Ranking, User, Score) with the ranking vector
    for (const auto &[rank, user, score] : ranking) {
        rowsRanking_.push_back(ftxui::hbox({
            // Ranging on the left
            ftxui::text(std::to_string(rank))
                | size(ftxui::WIDTH, ftxui::EQUAL, widthRanking),

            // User in the middle
            ftxui::text(user) | size(ftxui::WIDTH, ftxui::EQUAL, widthUser),

            // Score on the right
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
                   ftxui::vbox(rowsRanking_) | ftxui::border,
                   ftxui::separator(),
                   buttonBack_->Render(),
               })
               | ftxui::border | ftxui::center;
    });
}

void MainMenu::displayProfileManagerButton() {
    profileMessage_ = ""; // Empty message
    username_.clear();    // Empty username
    password_.clear();    // Empty password

    inputChangeUsername_ =
        ftxui::Input(&username_, "New username") | ftxui::border;

    inputChangePassword_ =
        ftxui::Input(&password_, "New password") | ftxui::border;

    submitButton_ =
        ftxui::Button(
            "Submit",
            [&] {
                if (!controller_->changeProfile(username_, password_)) {
                    profileMessage_ =
                        "The change of your profile has failed. Please enter "
                        "another username or password";
                } else {
                    confirmUpdateProfileScreen(); // Display the confirm update
                                                  // profile screen
                    screen_.ExitLoopClosure()();
                }
            },
            ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
        | ftxui::border;
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
                   ftxui::text(""), // Empty line
                   inputChangeUsername_->Render(),
                   inputChangePassword_->Render(),
                   ftxui::text(profileMessage_) | ftxui::center
                       | ftxui::color(ftxui::Color::Red),
                   ftxui::separator(),
                   submitButton_->Render(),
                   ftxui::separator(),
                   buttonBack_->Render(),
               })
               | ftxui::border | ftxui::center;
    });
}

void MainMenu::renderRanking() {

    displayRankingWindow();

    screen_.Loop(rankingWindow_);
}

void MainMenu::renderProfileManager() {

    displayProfileManagerWindow();

    screen_.Loop(profileManagerWindow_);
}

// ### Public methods ###
void MainMenu::render() {
    while (state_ != MainMenuState::EXIT) {
        displayMainWindow();
        screen_.Loop(mainMenuWindow_);
        handleChoice();
    }
}

