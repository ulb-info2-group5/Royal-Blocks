/**
 * @file login_menu.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief LoginMenu class definition file
 * @date 2025-02-12
 *
 */

#include "login_menu.hpp"

#include "../../../core/controller/controller.hpp"
#include "../main_tui.hpp"

#include "../ftxui_config/ftxui_config.hpp"

namespace TUI {

    // ### constructor ###
    LoginMenu::LoginMenu(MainTui &mainTui, Controller &controller)
        : mainTui_(mainTui), controller_(controller),
          loginInput_{mainTui_, controller_, LOGIN_INPUT_TITLE,
                      LoginType::LOGIN},
          registerInput_{mainTui_, controller_, REGISTER_INPUT_TITLE,
                         LoginType::REGISTER} {
        loginInput_.addInstruction(LOGIN_INSTRUCTIONS);
        registerInput_.addInstruction(REGISTER_INSTRUCTIONS);

        loginState_ = Login::NONE;

        createButtons();
    }

    // ### protected methods ###

    void LoginMenu::createButtons() {
        buttonRegister_ = ftxui::Button(
            std::string(STR_REGISTER),
            [&] {
                if (registerInput_.render() == LoginState::SUBMIT) {
                    loginInput_.addMessage(LOGIN_MESSAGE);
                    if (loginInput_.render() == LoginState::SUBMIT) {
                        loginState_ = Login::LOGGED;
                    }
                }
                mainTui_.stopRender();
            },
            GlobalButtonStyle());

        buttonLogin_ = ftxui::Button(
            std::string(STR_LOGIN),
            [&] {
                if (loginInput_.render() == LoginState::SUBMIT) {
                    loginState_ = Login::LOGGED;
                }
                mainTui_.stopRender();
            },
            GlobalButtonStyle());

        buttonExit_ = ftxui::Button(
            std::string(STR_EXIT),
            [&] {
                loginState_ = Login::EXIT;
                mainTui_.stopRender();
            },
            GlobalButtonStyle());
    }

    void LoginMenu::displayWindow() {
        displayWindow_ = ftxui::Renderer(
            ftxui::Container::Vertical({
                buttonRegister_,
                buttonLogin_,
                buttonExit_,
            }),
            [&] {
                return ftxui::vbox({
                           ftxui::text(std::string(STR_LOGIN_MENU))
                               | ftxui::bold | ftxui::center
                               | ftxui::bgcolor(ftxui::Color::Black),
                           ftxui::separator(),
                           ftxui::text(std::string(STR_INSTRUCTION_LOGIN))
                               | ftxui::center
                               | ftxui::bgcolor(ftxui::Color::Black),
                           ftxui::separator(),
                           buttonRegister_->Render()
                               | ftxui::bgcolor(ftxui::Color::Black),
                           buttonLogin_->Render()
                               | ftxui::bgcolor(ftxui::Color::Black),
                           buttonExit_->Render()
                               | ftxui::bgcolor(ftxui::Color::Black),
                       })
                       | ftxui::borderHeavy | ftxui::center
                       | ftxui::bgcolor(ftxui::Color::Black);
            });
    }

    // ### public methods ###
    LoginResult LoginMenu::render() {
        while (loginState_ == Login::NONE) {
            displayWindow();
            mainTui_.render(displayWindow_);
        }
        if (loginState_ == Login::EXIT) {
            return LoginResult::EXIT;
        }

        return LoginResult::SUCCESS;
    }

} // namespace TUI
