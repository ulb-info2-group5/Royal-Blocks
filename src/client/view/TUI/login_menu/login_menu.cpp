/**
 * @file login_menu.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief LoginMenu class definition file
 * @date 2025-02-12
 * 
 */

#include "login_menu.hpp"
#include "../input/login_input.hpp"

#include <cstdlib>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

// ### Public methods ###
LoginMenu::LoginMenu(ScreenManager *screenManager, LoginOption option) : screenManager_(screenManager), option_(option), loginInput_(this, screenManager_, "Login", InputType::LOGIN), registerInput_(this, screenManager_, "Sign in", InputType::REGISTER) {
    std::string loginInstruction = "Please enter your username and password to login";
    std::string registerInstruction = "Please enter a username and a password to create an account";
    loginInput_.addInstruction(loginInstruction);
    registerInput_.addInstruction(registerInstruction);
}

void LoginMenu::render() {
    checkOption();

    ftxui::Component buttonRegister = ftxui::Button("Register", [&] {
        registerInput_.render();
        checkOption();
    });

    ftxui::Component buttonLogin = ftxui::Button("Login", [&] {
        loginInput_.render();
        checkOption();
    });

    ftxui::Component buttonExit = ftxui::Button("Exit", [&] {
        screenManager_->exit();
    });

    ftxui::Component component = ftxui::Container::Vertical({
        buttonRegister,
        buttonLogin,
        buttonExit,
    });

    ftxui::Component render = ftxui::Renderer(component, [&] {
        if (exit_) {
            screenManager_->exitLoop();
        }
        return ftxui::vbox({
            ftxui::text("Login Menu") | ftxui::bold | ftxui::center,
            ftxui::separator(),
            ftxui::text("Please login to your accounnt or create one to enter the game") | ftxui::center,
            ftxui::separator(),
            buttonRegister->Render(),
            buttonLogin->Render(),
            buttonExit->Render(),
        }) | ftxui::border | ftxui::center;
    });

    screenManager_->renderComponent(render);
}

void LoginMenu::addOption(const LoginOption option) {
    option_ = option;
}

void LoginMenu::checkOption() {
    if (option_ == LoginOption::LOGIN_SUCCESS) {
        exit_ = true;
    }
    else if (option_ == LoginOption::REGISTER_SUCCESS) {
        std::string msg = "Account created successfully, you can now login";
        loginInput_.addMessage(msg);
        loginInput_.render();
        exit_ = true;
    }
    
}