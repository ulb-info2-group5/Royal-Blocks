/**
 * @file login_menu.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief LoginMenu class definition file
 * @date 2025-02-12
 *
 */

#include "login_menu.hpp"

#include "../../../controller/controller.hpp"
#include "../handle_ctrl/handle_ctrl.hpp"

#include <cstdlib>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

// ### constructor ###
LoginMenu::LoginMenu(ftxui::ScreenInteractive &screen, Controller &controller)
    : screen_(screen), controller_(controller),
      loginInput_(LoginInput(screen_, controller_, LOGIN_INPUT_TITLE,
                             LoginType::LOGIN)),
      registerInput_(LoginInput(screen_, controller_, REGISTER_INPUT_TITLE,
                                LoginType::REGISTER)) {
    loginInput_.addInstruction(LOGIN_INSTRUCTIONS);
    registerInput_.addInstruction(REGISTER_INSTRUCTIONS);

    loginState_ = Login::NONE;

    createButtons();
}

// ### protected methods ###

void LoginMenu::createButtons() {

    buttonRegister_ =
        ftxui::Button(
            "Register",
            [&] {
                if (registerInput_.render() == LoginState::SUBMIT) {
                    loginInput_.addMessage(LOGIN_MESSAGE);
                    if (loginInput_.render() == LoginState::SUBMIT) {
                        loginState_ = Login::LOGGED;
                    }
                }
                screen_.ExitLoopClosure()();
            },
            ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
        | ftxui::border;

    buttonLogin_ = ftxui::Button(
                       "Login",
                       [&] {
                           if (loginInput_.render() == LoginState::SUBMIT) {
                               loginState_ = Login::LOGGED;
                           }
                           screen_.ExitLoopClosure()();
                       },
                       ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
                   | ftxui::border;

    buttonExit_ = ftxui::Button(
                      "Exit",
                      [&] {
                          loginState_ = Login::EXIT;
                          screen_.ExitLoopClosure()();
                      },
                      ftxui::ButtonOption::Animated(ftxui::Color::Grey0))
                  | ftxui::border;
}

void LoginMenu::displayWindow() {
    ftxui::Component component = ftxui::Container::Vertical({
        buttonRegister_,
        buttonLogin_,
        buttonExit_,
    });

    displayWindow_ = ftxui::Renderer(component, [&] {
        return ftxui::vbox({
                   ftxui::text("Login Menu") | ftxui::bold | ftxui::center
                       | ftxui::bgcolor(ftxui::Color::Black),
                   ftxui::separator(),
                   ftxui::text("Please login to your account or create one to "
                               "enter the game")
                       | ftxui::center | ftxui::bgcolor(ftxui::Color::Black),
                   ftxui::separator(),
                   buttonRegister_->Render()
                       | ftxui::bgcolor(ftxui::Color::Black),
                   buttonLogin_->Render() | ftxui::bgcolor(ftxui::Color::Black),
                   buttonExit_->Render() | ftxui::bgcolor(ftxui::Color::Black),
               })
               | ftxui::border | ftxui::center
               | ftxui::bgcolor(ftxui::Color::Black);
    });
}

// ### public methods ###
LoginResult LoginMenu::render() {
    while (loginState_ == Login::NONE) {
        displayWindow();
        screen_.Loop(handleCtrl(displayWindow_));
    }
    if (loginState_ == Login::EXIT) {
        return LoginResult::EXIT;
    }

    return LoginResult::SUCCESS;
}