/**
 * @file tui_manager.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief TuiManager class definition file
 * @date 2025-02-13
 * 
 */

#include "tui_manager.hpp"
#include "login_menu/login_menu.hpp"

#include <chrono>
#include <thread>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

// ### Public methods ###
TuiManager::TuiManager() {
    screen_ = std::shared_ptr<ftxui::ScreenInteractive>(
        new ftxui::ScreenInteractive(ftxui::ScreenInteractive::Fullscreen())
    );
    std::string login = "Login";
    std::string signIn = "Sign in";
    std::string loginInstruction = "Please enter your username and password to login";
    std::string registerInstruction = "Please enter a username and password to create an account";

    loginInput_ = std::shared_ptr<LoginInput>(new LoginInput(screen_, login));
    registerInput_ = std::shared_ptr<LoginInput>(new LoginInput(screen_, signIn));

    loginInput_->addInstruction(loginInstruction);
    registerInput_->addInstruction(registerInstruction);
}

void TuiManager::run() {
    startScreen();
    LoginMenu loginMenu = LoginMenu(screen_, loginInput_, registerInput_);
    loginMenu.render();
}


// ### Private methods ###
void TuiManager::startScreen() {
    bool exit = false;

    auto title = ftxui::Renderer([&] {
        return exit ? ftxui::text("") : ftxui::vbox({
            ftxui::filler(),
            ftxui::hbox({
                ftxui::filler(),
                ftxui::text("Welcome to Tetris Royal !") | ftxui::bold | ftxui::border | ftxui::center,
                ftxui::filler()
            }),
            ftxui::filler()
        });
    });

    // Use a thread to exit this display after 2 seconds
    std::thread([&] {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        exit = true;
        screen_->PostEvent(ftxui::Event::Custom); // Refresh the screen to exit the display after 2 seconds
        screen_->ExitLoopClosure()();
    }).detach();

    screen_->Loop(title);
}