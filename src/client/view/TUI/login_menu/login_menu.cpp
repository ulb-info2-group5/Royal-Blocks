/**
 * @file login_menu.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief LoginMenu class definition file
 * @date 2025-02-12
 * 
 */

#include "login_menu.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <memory>

// ### Public methods ###
LoginMenu::LoginMenu(std::shared_ptr<ftxui::ScreenInteractive> &screen) : screen_(screen) {}

LoginState LoginMenu::render() {
    LoginState res = LoginState::NONE;

    ftxui::Component buttonRegister = ftxui::Button("Register", [&] {
        res = LoginState::LAUNCH_REGISTER;
        screen_->ExitLoopClosure()();
    });

    ftxui::Component buttonLogin = ftxui::Button("Login", [&] {
        res = LoginState::LAUNCH_LOGIN;
        screen_->ExitLoopClosure()();
    });

    ftxui::Component buttonExit = ftxui::Button("Exit", [&] {
        res = LoginState::EXIT;
        screen_->ExitLoopClosure()();
    });

    ftxui::Component component = ftxui::Container::Vertical({
        buttonRegister,
        buttonLogin,
        buttonExit,
    });

    ftxui::Component render = ftxui::Renderer(component, [&] {
        return ftxui::vbox({
            ftxui::text("Login Menu") | ftxui::bold | ftxui::center,
            ftxui::separator(),
            ftxui::text("Please login to your account or create one to enter the game") | ftxui::center,
            ftxui::separator(),
            buttonRegister->Render(),
            buttonLogin->Render(),
            buttonExit->Render(),
        }) | ftxui::border | ftxui::center;
    });

    screen_->Loop(render);

    return res;
}