/**
 * @file login_menu.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief LoginMenu class definition file
 * @date 2025-02-12
 * 
 */

#include "login_menu.hpp"
#include "../login_input/login_input.hpp"
#include <cstdlib>
#include <ftxui/component/component.hpp>

LoginMenu::LoginMenu(ScreenManager *screenManager) : MenuUi(screenManager, "Login Menu", std::vector<std::string>{"Login", "Exit"}) {}

void LoginMenu::run() {
    std::string loginStr = "Login";
    std::string registerStr = "Sign In";
    LoginInput loginInput(screenManager_, loginStr);
    LoginInput registerInput(screenManager_, registerStr);
    registerInput.addInstructions("Please enter a username and a password to create an account");


    auto buttonRegister = ftxui::Button("Register", [&] {
        if (registerInput.run() == SUCCESS) {
            loginInput.addTextUnder("Your account has been created ! You can now login");
            if (loginInput.run() == SUCCESS) {
                screenManager_->exitLoop();
            }
        }
    });

    auto buttonLogin = ftxui::Button("Login", [&] {
        if (loginInput.run() == SUCCESS) {
            screenManager_->exitLoop();
        }
    });

    auto buttonExit = ftxui::Button("Exit", [&] {
        screenManager_->exit();
    });

    auto component = ftxui::Container::Vertical({
        buttonRegister,
        buttonLogin,
        buttonExit,
    });

    auto renderer = ftxui::Renderer(component, [&] {
        return ftxui::vbox({
            ftxui::text("Connection Menu") | ftxui::bold | ftxui::center,
            buttonRegister->Render(),
            buttonLogin->Render(),
            buttonExit->Render(),
        }) | ftxui::border;
    });

    screenManager_->loopScreen(renderer);
}