/**
 * @file login_input.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief LoginInput class definition file
 * @date 2025-02-12
 * 
 */

#include "login_input.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <memory>
#include <string>

LoginInput::LoginInput(std::shared_ptr<ScreenManager> screenManager, std::string &title) : screenManager_(screenManager), title_(title) {}

LoginInputStatus LoginInput::run() {
    LoginInputStatus status = LoginInputStatus::FAILURE;
    std::string msg;

    ftxui::Component inputUsername = ftxui::Input(&username_, "Enter username");
    ftxui::Component inputPassword = ftxui::Input(&password_, "Enter password");

    auto buttonSubmit = ftxui::Button("Submit", [&] {
        if (!username_.empty() && !password_.empty()) {
            // TODO: add logic with controller and server to check with the database for the register
            // TODO: add logic with controller and server to check with the database for the login
            status = LoginInputStatus::SUCCESS;
            screenManager_->exitLoop();
        } else {
            username_.clear();
            password_.clear();
            msg = "Please enter a valid username and a valid password";
        }
    });

    auto buttonBack = ftxui::Button("Back", [&] {
        username_.clear();
        password_.clear();
        screenManager_->exitLoop();
    });

    auto component = ftxui::Container::Vertical({
        inputUsername,
        inputPassword,
        buttonSubmit,
        buttonBack,
    });


    auto renderer = ftxui::Renderer(component, [&] {
        return ftxui::vbox({
            ftxui::text(title_) | ftxui::bold | ftxui::center,
            ftxui::separator(),
            ftxui::text(instructons_) | ftxui::center,
            ftxui::separator(),
            inputUsername->Render(),
            inputPassword->Render(),
            buttonSubmit->Render(),
            buttonBack->Render(),
            ftxui::text(msg),
            ftxui::text(message_),
        }) | ftxui::border;
    });
   
    screenManager_->loopScreen(renderer);

    return status;
}

void LoginInput::addTextUnder(const std::string& text) {
    message_ = text;
}

void LoginInput::addInstructions(const std::string& instructions) {
    instructons_ = instructions;
}