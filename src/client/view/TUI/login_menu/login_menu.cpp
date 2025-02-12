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

LoginMenu::LoginMenu(std::shared_ptr<ftxui::ScreenInteractive> screen) : screen_(screen) {}

void LoginMenu::render() {
    std::string emptyMessage = "";

    auto buttonRegister = ftxui::Button("Register", [&] {
        if (ShowRegister(emptyMessage) == InputState::SUCCESS) {
            std::string addMessage = "Account created successfully ! You can now login";
            if (ShowLogin(addMessage) == InputState::SUCCESS) {
                exit_ = true;
                screen_->ExitLoopClosure();
                return;
            }
        }
    });
    auto buttonLogin = ftxui::Button("Login", [&] {
        if (ShowLogin(emptyMessage) == InputState::SUCCESS) {
            exit_ = true;
            screen_->ExitLoopClosure();
            return;
        }
    });

    auto buttonExit = ftxui::Button("Exit", [&] {
        exit_ = true;
        screen_->ExitLoopClosure();
    });

    auto component = ftxui::Container::Vertical({
        buttonRegister,
        buttonLogin,
        buttonExit,
    });

    auto render = Renderer(component, [&] {
        if (exit_) {
            screen_->ExitLoopClosure()();
        }
        return ftxui::vbox({
            ftxui::text("Login Menu") | ftxui::bold | ftxui::center,
            buttonRegister->Render(),
            buttonLogin->Render(),
            buttonExit->Render(),
        }) | ftxui::border;
    });

    screen_->Loop(render);
}

InputState LoginMenu::ShowRegister(std::string &addMessage) {
    std::string title = "Register";
    std::string instruction = "Please enter a username and a password to create an account";
    LoginInput registerInput(screen_, title);
    registerInput.addInstruction(instruction);
    if (!addMessage.empty()) {
        registerInput.addMessage(addMessage);
    }
    return registerInput.render();
}

InputState LoginMenu::ShowLogin(std::string &addMessage) {
    std::string title = "Login";
    std::string instruction = "Please enter your username and password to login";
    LoginInput loginInput(screen_, title);
    loginInput.addInstruction(instruction);
    if (!addMessage.empty()) {
        loginInput.addMessage(addMessage);
    }
    return loginInput.render();
}