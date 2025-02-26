/**
 * @file login_input.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief LoginInput class definition file
 * @date 2025-02-12
 * 
 */

#include "login_input.hpp"

#include "../../../controller/controller.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <memory>
#include <string>

// ### Constructor ###
LoginInput::LoginInput(std::shared_ptr<ftxui::ScreenInteractive> &screen, Controller *controller, std::string title, LoginType loginType) : 
        screen_(screen), controller_(controller), title_(title), loginType_(loginType), loginState_(LoginState::NONE) {}

// ### protected methods ###

void LoginInput::displayButtonBack()
{
    buttonBack_ = ftxui::Button("Back", [&] {
        username_.clear();
        password_.clear();
        loginState_ = LoginState::BACK;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;
}

void LoginInput::displayButtonSubmit()
{
    buttonSubmit_ = ftxui::Button("Submit", [&] {
        if (loginType_ == LoginType::REGISTER && controller_->verifyRegister(username_, password_)) {
            loginState_ = LoginState::SUBMIT;
            screen_->ExitLoopClosure()();
        } else if (loginType_ == LoginType::LOGIN && controller_->verifyLogin(username_, password_)) {
            loginState_ = LoginState::SUBMIT;
            screen_->ExitLoopClosure()();
        } else {
            username_.clear();
            password_.clear();
            message_.clear(); 
            msg_ = "The username or password is incorrect!";
        }
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;
}

void LoginInput::displayWindow() 
{
    displayButtonBack();
    displayButtonSubmit();

    inputUsername_ = ftxui::Input(&username_, "Enter username") | ftxui::border;
    inputPassword_ = ftxui::Input(&password_, "Enter password") | ftxui::border;

    ftxui::Component displayButtons = ftxui::Container::Vertical({
        inputUsername_,
        inputPassword_,
        buttonSubmit_,
        buttonBack_,
    });

    displayWindow_ = ftxui::Renderer(displayButtons, [&] {
        std::vector<ftxui::Element> elements = {
            ftxui::text(title_) | ftxui::bold | ftxui::center,
        };

        if (!instruction_.empty()) {
            elements.push_back(ftxui::separator());
            elements.push_back(ftxui::text(instruction_) | ftxui::center);
            elements.push_back(ftxui::separator());
        }

        elements.push_back(inputUsername_->Render());
        elements.push_back(inputPassword_->Render());
        elements.push_back(ftxui::separator());

        if (!msg_.empty()) {
            elements.push_back(ftxui::text(msg_) | ftxui::center | ftxui::color(ftxui::Color::Red));
            elements.push_back(ftxui::separator());
        }
        
        if (!message_.empty()) {
            elements.push_back(ftxui::text(message_) | ftxui::color(ftxui::Color::Red) | ftxui::center);
            elements.push_back(ftxui::separator());
        }

        elements.push_back(buttonSubmit_->Render());
        elements.push_back(buttonBack_->Render());

        return ftxui::vbox(elements) | ftxui::border | ftxui::center;
    });

}

// ### public methods ###

void LoginInput::addInstruction(const std::string_view instruction) {
    instruction_ = instruction;
}

void LoginInput::addMessage(const std::string_view message) {
    message_ = message;
}

void LoginInput::clearInfo() {
    username_.clear();
    password_.clear();
}

LoginState LoginInput::render() {
    displayWindow();

    screen_->Loop(displayWindow_);

    return loginState_;
}