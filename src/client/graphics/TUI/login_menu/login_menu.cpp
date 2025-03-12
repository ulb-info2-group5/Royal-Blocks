/**
 * @file login_menu.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief LoginMenu class definition file
 * @date 2025-02-12
 *
 */

#include "login_menu.hpp"

#include "../../../core/controller/controller.hpp"
#include "../ftxui_config/ftxui_config.hpp"

#include <cstdlib>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

// ### constructor ###
LoginMenu::LoginMenu(ScreenManager &screenManager, Controller &controller)
    : screenManager_(screenManager), controller_(controller),
      loginInput_(LoginInput(screenManager_, controller_, LOGIN_INPUT_TITLE,
                             LoginType::LOGIN)),
      registerInput_(LoginInput(screenManager_, controller_, REGISTER_INPUT_TITLE,
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
            STR_REGISTER,
            [&] {
                if (registerInput_.render() == LoginState::SUBMIT) {
                    loginInput_.addMessage(LOGIN_MESSAGE);
                    if (loginInput_.render() == LoginState::SUBMIT) {
                        loginState_ = Login::LOGGED;
                    }
                }
                screenManager_.stopRender();
            }, GlobalButtonStyle());

    buttonLogin_ = ftxui::Button(
                       STR_LOGIN,
                       [&] {
                           if (loginInput_.render() == LoginState::SUBMIT) {
                               loginState_ = Login::LOGGED;
                           }
                           screenManager_.stopRender();
                       }, GlobalButtonStyle());

    buttonExit_ = ftxui::Button(
                      STR_EXIT,
                      [&] {
                          loginState_ = Login::EXIT;
                          screenManager_.stopRender();
                      }, GlobalButtonStyle());
}

void LoginMenu::displayWindow() {
    ftxui::Component component = ftxui::Container::Vertical({
        buttonRegister_,
        buttonLogin_,
        buttonExit_,
    });

    displayWindow_ = ftxui::Renderer(component, [&] {
        return ftxui::vbox({
                   ftxui::text(STR_LOGIN_MENU) | ftxui::bold | ftxui::center
                       | ftxui::bgcolor(ftxui::Color::Black),
                   ftxui::separator(),
                   ftxui::text(STR_INSTRUCTION_LOGIN)
                       | ftxui::center | ftxui::bgcolor(ftxui::Color::Black),
                   ftxui::separator(),
                   buttonRegister_->Render()
                       | ftxui::bgcolor(ftxui::Color::Black),
                   buttonLogin_->Render() | ftxui::bgcolor(ftxui::Color::Black),
                   buttonExit_->Render() | ftxui::bgcolor(ftxui::Color::Black),
               })
               | ftxui::borderHeavy | ftxui::center
               | ftxui::bgcolor(ftxui::Color::Black);
    });
}

// ### public methods ###
LoginResult LoginMenu::render() {
    while (loginState_ == Login::NONE) {
        displayWindow();
        screenManager_.render(displayWindow_);
    }
    if (loginState_ == Login::EXIT) {
        return LoginResult::EXIT;
    }

    return LoginResult::SUCCESS;
}
