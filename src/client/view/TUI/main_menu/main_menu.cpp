/**
 * @file main_menu.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief MainMenu class definition file
 * @date 2025-02-12
 * 
 */

#include "main_menu.hpp"
#include "../messaging/messaging.hpp"
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>


// ### Constructor ###
MainMenu::MainMenu(std::shared_ptr<ftxui::ScreenInteractive> &screen) : 
screen_(screen) 
{
    userState_ = MainMenuState::NONE;
    userInput_ = {"", "", ""};
    buttonBack_ = ftxui::Button("Back", [&] {
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;
}

// ### Protected methods ###

void MainMenu::displayMainMenuButtons()
{
    buttonPlay_ = ftxui::Button("Create a game", [&] {
        userState_ = MainMenuState::CREATE_GAME;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    buttonJoinGame_ = ftxui::Button("Join a game", [&] {
        userState_ = MainMenuState::JOIN_GAME;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    buttonSendMessagesToFriends_ = ftxui::Button("Send messages to friends", [&] {
        userState_ = MainMenuState::SEND_MESSAGES;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    buttonLookRanking_ = ftxui::Button("Look at ranking", [&] {
        userState_ = MainMenuState::LOOK_RANKING;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    buttonManageProfile_ = ftxui::Button("Manage profile", [&] {
        userState_ = MainMenuState::MANAGE_PROFILE;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    buttonManageFriendsList_ = ftxui::Button("Manage friends list", [&] {
        userState_ = MainMenuState::MANAGE_FRIENDS_LIST;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    buttonExit_ = ftxui::Button("Exit", [&] {
        userState_ = MainMenuState::EXIT;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;
}

void MainMenu::displayMainWindow()
{
    displayMainMenuButtons();

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
            ftxui::text("Welcome to the main menu of Tetris Royal !") | ftxui::center,
            ftxui::separator(),
            buttonPlay_->Render(),
            buttonJoinGame_->Render(),
            buttonSendMessagesToFriends_->Render(),
            buttonLookRanking_->Render(),
            buttonManageProfile_->Render(),
            buttonManageFriendsList_->Render(),
            buttonExit_->Render(),
        }) | ftxui::border | ftxui::center;
    });
}

void MainMenu::displayRankingList(const std::vector<std::tuple<int, std::string, int>> &ranking)
{
    // Clear the rows of the ranking table to avoid duplicates
    rowsRanking_.clear(); 

    // Width of the columns
    const int widthRanking = 10;
    const int widthUser = 30;
    const int widthScore = 10;

    // Title of the table
    rowsRanking_.push_back(
        ftxui::hbox({
            ftxui::text("Ranking") | ftxui::bold | size(ftxui::WIDTH, ftxui::EQUAL, widthRanking) | ftxui::center,
            ftxui::text("User")    | ftxui::bold | size(ftxui::WIDTH, ftxui::EQUAL, widthUser)    | ftxui::center,
            ftxui::text("Score")   | ftxui::bold | size(ftxui::WIDTH, ftxui::EQUAL, widthScore)   | ftxui::center,
        })
    );
    rowsRanking_.push_back(ftxui::separator());

    // infos of the ranking table (Ranking, User, Score) with the ranking vector
    for (const auto& [rank, user, score] : ranking) {
        rowsRanking_.push_back(
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
}

void MainMenu::displayRankingWindow(const std::vector<std::tuple<int, std::string, int>> &ranking)
{
    displayRankingList(ranking);

    ftxui::Component container = ftxui::Container::Vertical({
        buttonBack_,
    });

    rankingWindow_ = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
            ftxui::text("Endless mod Ranking") | ftxui::bold | ftxui::center,
            ftxui::separator(),
            ftxui::vbox(rowsRanking_) | ftxui::border,
            ftxui::separator(),
            buttonBack_->Render(),
        }) | ftxui::border | ftxui::center;
    });
}

void MainMenu::displayProfileManagerButton()
{
    inputChangeUsername_ = ftxui::Input(&userInput_.at(0), "New username") | ftxui::border;

    inputChangePassword_ = ftxui::Input(&userInput_.at(1), "New password") | ftxui::border;

    submitButton_ = ftxui::Button("Submit", [&] {
        if (userInput_.at(0).empty() && userInput_.at(1).empty()) {
            userInput_.at(2) = "Please enter a new username or password";
        }
        else {
            screen_->ExitLoopClosure()();
        }
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;
}

void MainMenu::displayProfileManagerWindow()
{
    userInput_.at(0) = ""; // Clear the user input to take new ones
    userInput_.at(1) = "";
    userInput_.at(2) = "";

    displayProfileManagerButton();

    ftxui::Component container = ftxui::Container::Vertical({
        inputChangeUsername_,
        inputChangePassword_,
        submitButton_,
        buttonBack_
    });

    profileManagerWindow_ = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
            ftxui::text("Profile Manager") | ftxui::bold | ftxui::center,
            ftxui::separator(),
            ftxui::text("You can change your username and password here") | ftxui::center,
            ftxui::separator(),
            ftxui::text(""), // Empty line
            inputChangeUsername_->Render(),
            inputChangePassword_->Render(),
            ftxui::text(userInput_.at(2)),
            ftxui::separator(),
            submitButton_->Render(),
            ftxui::separator(),
            buttonBack_->Render(),
        }) | ftxui::border | ftxui::center;
    });
}

// ### Public methods ###
MainMenuState MainMenu::render() {
    
    displayMainWindow();

    screen_->Loop(mainMenuWindow_);

    return userState_;
}


void MainMenu::renderRanking(const std::vector<std::tuple<int, std::string, int>> &ranking) {

    displayRankingWindow(ranking);

    screen_->Loop(rankingWindow_);    
}

void MainMenu::renderMessagingMenu(const std::vector<std::string>& friendsList){
    // very bad just for the tests
    Messaging messagingMenue(screen_, friendsList);
    messagingMenue.render();
}

void MainMenu::renderProfileManager() {

    displayProfileManagerWindow();

    screen_->Loop(profileManagerWindow_);
}

std::vector<std::string> MainMenu::getUserNewInput() {
    return userInput_;
}
