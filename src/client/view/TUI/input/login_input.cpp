/**
 * @file login_input.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief LoginInput class definition file
 * @date 2025-02-12
 * 
 */

#include "login_input.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <memory>
#include <string>

// ### Public methods ###
LoginInput::LoginInput(std::shared_ptr<ftxui::ScreenInteractive> &screen, std::string title) : screen_(screen), title_(title) {}

InputState LoginInput::render() {
    InputState res = InputState::NONE;
    std::string msg;

    ftxui::Component inputUsername = ftxui::Input(&username_, "Enter username") | ftxui::border;
    ftxui::Component inputPassword = ftxui::Input(&password_, "Enter password") | ftxui::border;

    ftxui::Component buttonSubmit = ftxui::Button("Submit", [&] {
        if (!username_.empty() && !password_.empty()) {
            // TODO: add logic with controller and server to check with the database for the register
            // TODO: add logic with controller and server to check with the database for the login
            res = InputState::DONE;
            screen_->ExitLoopClosure()();
        } else {
            username_.clear();
            password_.clear();
            message_.clear(); 
            msg = "Please enter a valid username and a valid password";
        }
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    ftxui::Component buttonBack = ftxui::Button("Back", [&] {
        username_.clear();
        password_.clear();
        res = InputState::BACK;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    ftxui::Component component = ftxui::Container::Vertical({
        inputUsername,
        inputPassword,
        buttonSubmit,
        buttonBack,
    });

    ftxui::Component render = ftxui::Renderer(component, [&] {
        std::vector<ftxui::Element> elements = {
            ftxui::text(title_) | ftxui::bold | ftxui::center,
        };

        if (!instruction_.empty()) {
            elements.push_back(ftxui::separator());
            elements.push_back(ftxui::text(instruction_) | ftxui::center);
            elements.push_back(ftxui::separator());
        }

        elements.push_back(inputUsername->Render());
        elements.push_back(inputPassword->Render());
        elements.push_back(ftxui::separator());

        if (!msg.empty()) {
            elements.push_back(ftxui::text(msg));
            elements.push_back(ftxui::separator());
        }
        
        if (!message_.empty()) {
            elements.push_back(ftxui::text(message_));
            elements.push_back(ftxui::separator());
        }

        elements.push_back(buttonSubmit->Render());
        elements.push_back(buttonBack->Render());

        return ftxui::vbox(elements) | ftxui::border | ftxui::center;
    });

    screen_->Loop(render);

    return res;
}

void LoginInput::addInstruction(const std::string_view instruction) {
    instruction_ = instruction;
}

void LoginInput::addMessage(const std::string_view message) {
    message_ = message;
}

std::string LoginInput::getUsername() const {
    return username_;
}

std::string LoginInput::getPassword() const {
    return password_;
}