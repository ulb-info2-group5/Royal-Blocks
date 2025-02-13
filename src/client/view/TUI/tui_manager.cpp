/**
 * @file tui_manager.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief TuiManager class definition file
 * @date 2025-02-13
 * 
 */

#include "tui_manager.hpp"
#include "login_menu/login_menu.hpp"
#include "main_menu/main_menu.hpp"

#include <chrono>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/node.hpp>
#include <memory>
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
    MainMenu mainMenu = MainMenu(screen_);
    loginMenu.render();
    mainMenu.render();
}


// ### Private methods ###
void TuiManager::startScreen() {
    bool exit = false;

    ftxui::Component title = ftxui::Renderer([&] {
        return exit ? ftxui::text("") : ftxui::vbox({
            ftxui::text(R"(__          __  _                            _          _____                   _   _______   _        _       _ )"),
            ftxui::text(R"(\ \        / / | |                          | |        |  __ \                 | | |__   __| | |      (_)     | |)"),
            ftxui::text(R"( \ \  /\  / /__| | ___ ___  _ __ ___   ___  | |_ ___   | |__) |___  _   _  __ _| |    | | ___| |_ _ __ _ ___  | |)"),
            ftxui::text(R"(  \ \/  \/ / _ \ |/ __/ _ \| '_ ` _ \ / _ \ | __/ _ \  |  _  // _ \| | | |/ _` | |    | |/ _ \ __| '__| / __| | |)"),
            ftxui::text(R"(   \  /\  /  __/ | (_| (_) | | | | | |  __/ | || (_) | | | \ \ (_) | |_| | (_| | |    | |  __/ |_| |  | \__ \ |_|)"),
            ftxui::text(R"(    \/  \/ \___|_|\___\___/|_| |_| |_|\___|  \__\___/  |_|  \_\___/ \__, |\__,_|_|    |_|\___|\__|_|  |_|___/ (_))"),
            ftxui::text(R"(                                                                     __/ |                                       )"),
            ftxui::text(R"(                                                                    |___/                                        )"),
        });
    }) | ftxui::border | ftxui::center;

    // Use a thread to exit this display after 2 seconds
    std::thread([&] {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        exit = true;
        screen_->PostEvent(ftxui::Event::Custom); // Refresh the screen to exit the display after 2 seconds
        screen_->ExitLoopClosure()();
    }).detach();

    screen_->Loop(title);
}