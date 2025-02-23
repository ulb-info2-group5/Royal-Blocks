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

// ### constructor ###
LoginMenu::LoginMenu(std::shared_ptr<ftxui::ScreenInteractive> &screen) : 
        screen_(screen) 
{
    userState_ = LoginState::NONE;
}

// ### protected methods ###

void LoginMenu::displayButtons() 
{
    buttonRegister_ = ftxui::Button("Register", [&] {
        userState_ = LoginState::LAUNCH_REGISTER;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    buttonLogin_ = ftxui::Button("Login", [&] {
        userState_ = LoginState::LAUNCH_LOGIN;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    buttonExit_ = ftxui::Button("Exit", [&] {
        userState_ = LoginState::EXIT;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;
}

void LoginMenu::displayWindow()
{
    displayButtons();

     ftxui::Component component = ftxui::Container::Vertical({
        buttonRegister_,
        buttonLogin_,
        buttonExit_,
    });

    displayWindow_ = ftxui::Renderer(component, [&] {
        return ftxui::vbox({
            ftxui::text("Login Menu") | ftxui::bold | ftxui::center | ftxui::bgcolor(ftxui::Color::Black),
            ftxui::separator(),
            ftxui::text("Please login to your account or create one to enter the game") | ftxui::center | ftxui::bgcolor(ftxui::Color::Black),
            ftxui::separator(),
            buttonRegister_->Render() | ftxui::bgcolor(ftxui::Color::Black),
            buttonLogin_->Render() | ftxui::bgcolor(ftxui::Color::Black),
            buttonExit_->Render() | ftxui::bgcolor(ftxui::Color::Black),
        }) | ftxui::border | ftxui::center | ftxui::bgcolor(ftxui::Color::Black);
    });
    
}

// ### public methods ###

LoginState LoginMenu::render() 
{

    displayWindow();

    screen_->Loop(displayWindow_);

    return userState_;
}