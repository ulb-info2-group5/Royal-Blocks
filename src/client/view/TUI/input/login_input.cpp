/**
 * @file login_input.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief LoginInput class definition file
 * @date 2025-02-12
 * 
 */

#include "login_input.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

// ### Public methods ###
LoginInput::LoginInput(std::shared_ptr<ftxui::ScreenInteractive> screen, std::string &title) : screen_(screen), title_(title) {}

InputState LoginInput::render() {
    InputState state = InputState::WAITING;
    std::string msg;

    ftxui::Component inputUsername = ftxui::Input(&username_, "Enter username");
    ftxui::Component inputPassword = ftxui::Input(&password_, "Enter password");

    auto buttonSubmit = ftxui::Button("Submit", [&] {
        if (!username_.empty() && !password_.empty()) {
            // TODO: add logic with controller and server to check with the database for the register
            // TODO: add logic with controller and server to check with the database for the login
            state = InputState::SUCCESS;
            screen_->ExitLoopClosure()();
            return state;

        } else {
            username_.clear();
            password_.clear();
            msg = "Please enter a valid username and a valid password";
        }
        return state;
    });

    auto buttonBack = ftxui::Button("Back", [&] {
        username_.clear();
        password_.clear();
        screen_->ExitLoopClosure()();
    });

    auto component = ftxui::Container::Vertical({
        inputUsername,
        inputPassword,
        buttonSubmit,
        buttonBack,
    });


    auto render = ftxui::Renderer(component, [&] {
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
        }) | ftxui::border;
    });

    screen_->Loop(render);
    return state;
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