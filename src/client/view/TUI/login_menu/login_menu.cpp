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
LoginMenu::LoginMenu(std::shared_ptr<ftxui::ScreenInteractive> screen, std::shared_ptr<LoginInput> loginInput, std::shared_ptr<LoginInput> registerInput) : screen_(screen), loginInput_(loginInput), registerInput_(registerInput) {}

void LoginMenu::render() {
    auto buttonRegister = ftxui::Button("Register", [&] {
        if (registerInput_->render() == InputState::SUCCESS) {
            std::string addMessage = "Account created successfully ! You can now login";
            loginInput_->addMessage(addMessage);
            if (loginInput_->render() == InputState::SUCCESS) {
                exit_ = true;
                screen_->ExitLoopClosure();
                return;
            }
        }
    });
    auto buttonLogin = ftxui::Button("Login", [&] {
        if (loginInput_->render() == InputState::SUCCESS) {
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
            ftxui::separator(),
            ftxui::text("Please login to your accounnt or create one to enter the game") | ftxui::center,
            ftxui::separator(),
            buttonRegister->Render(),
            buttonLogin->Render(),
            buttonExit->Render(),
        }) | ftxui::border;
    });

    screen_->Loop(render);
}