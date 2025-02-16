/**
 * @file login_input.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief LoginInput class definition file
 * @date 2025-02-12
 * 
 */

#include "login_input.hpp"
#include "../login_menu/login_menu.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

// ### Public methods ###
LoginInput::LoginInput(LoginMenu *loginMenu, ScreenManager *screenManager, std::string title, InputType type) : loginMenu_(loginMenu), screenManager_(screenManager), title_(title), type_(type) {}

void LoginInput::render() {
    std::string msg;

    ftxui::Component inputUsername = ftxui::Input(&username_, "Enter username");
    ftxui::Component inputPassword = ftxui::Input(&password_, "Enter password");

    ftxui::Component buttonSubmit = ftxui::Button("Submit", [&] {
        if (!username_.empty() && !password_.empty()) {
            // TODO: add logic with controller and server to check with the database for the register
            // TODO: add logic with controller and server to check with the database for the login
            if (type_ == InputType::LOGIN) {
                loginMenu_->addOption(LoginOption::LOGIN_SUCCESS);
            } else {
                loginMenu_->addOption(LoginOption::REGISTER_SUCCESS);
            }
            screenManager_->exitLoop();
        } else {
            username_.clear();
            password_.clear();
            msg = "Please enter a valid username and a valid password";
        }
    });

    ftxui::Component buttonBack = ftxui::Button("Back", [&] {
        username_.clear();
        password_.clear();
        screenManager_->exitLoop();
    });

    ftxui::Component component = ftxui::Container::Vertical({
        inputUsername,
        inputPassword,
        buttonSubmit,
        buttonBack,
    });


    ftxui::Component render = ftxui::Renderer(component, [&] {
        return ftxui::vbox({
            ftxui::text(title_) | ftxui::bold | ftxui::center,
            ftxui::separator(),
            ftxui::text(instruction_) | ftxui::center, 
            ftxui::separator(),
            inputUsername->Render(),
            inputPassword->Render(),
            buttonSubmit->Render(),
            buttonBack->Render(),
            ftxui::text(msg),
            ftxui::text(message_),
        }) | ftxui::border | ftxui::center;
    });

    screenManager_->renderComponent(render);
}

void LoginInput::addInstruction(std::string &instruction) {
    instruction_ = instruction;
}

void LoginInput::addMessage(std::string &message) {
    message_ = message;
}

std::string LoginInput::getUsername() const {
    return username_;
}

std::string LoginInput::getPassword() const {
    return password_;
}