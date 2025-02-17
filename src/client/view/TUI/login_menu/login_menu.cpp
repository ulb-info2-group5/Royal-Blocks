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
    }, ftxui::ButtonOption::Animated());

    ftxui::Component buttonLogin = ftxui::Button("Login", [&] {
        res = LoginState::LAUNCH_LOGIN;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated());

    ftxui::Component buttonExit = ftxui::Button("Exit", [&] {
        res = LoginState::EXIT;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated());

    ftxui::Component component = ftxui::Container::Vertical({
        buttonRegister,
        buttonLogin,
        buttonExit,
    });

    ftxui::Component render = ftxui::Renderer(component, [&] {
        return ftxui::vbox({
            ftxui::text("Login Menu") | ftxui::bold | ftxui::center | ftxui::bgcolor(ftxui::Color::Black),
            ftxui::separator(),
            ftxui::text("Please login to your account or create one to enter the game") | ftxui::center | ftxui::bgcolor(ftxui::Color::Black),
            ftxui::separator(),
            buttonRegister->Render() | ftxui::bgcolor(ftxui::Color::Black),
            buttonLogin->Render() | ftxui::bgcolor(ftxui::Color::Black),
            buttonExit->Render() | ftxui::bgcolor(ftxui::Color::Black),
        }) | ftxui::border | ftxui::center | ftxui::bgcolor(ftxui::Color::Black);
    });

    screen_->Loop(render);

    return res;
}