/**
 * @file login_input.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief LoginInput class definition file
 * @date 2025-02-12
 *
 */

#include "login_input.hpp"

#include "../../../core/controller/controller.hpp"
#include "../ftxui_config/ftxui_config.hpp"

#include "../main_tui.hpp"
#include <cctype>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <thread>

const std::string invalidChars = "!@#$%^&*()+=[]{}|\\\"'<>?/°;,~:²³§_£";


// ### Constructor ###
LoginInput::LoginInput(MainTui &mainTui, Controller &controller,
                       std::string title, LoginType loginType)
    : mainTui_(mainTui), controller_(controller), title_(title),
      loginType_(loginType), loginState_(LoginState::NONE) {

    createButtonBack();
    createButtonSubmit();

    inputUsername_ =
        ftxui::Input(&username_, std::string(STR_ENTER_USERNAME))
        | ftxui::borderHeavy
        | ftxui::CatchEvent([this](const ftxui::Event &event) {
              if (event == ftxui::Event::Return) {
                  mainTui_.simulateTab(); // Move to the next input
                  return true;
              }
              return false;
          });

    inputPassword_ = ftxui::Input(&password_, std::string(STR_ENTER_PASSWORD),
                                  PasswordInputOption())
                     | ftxui::borderHeavy
                     | ftxui::CatchEvent([this](const ftxui::Event &event) {
                           if (event == ftxui::Event::Return) {
                               buttonSubmit_->OnEvent(
                                   event); // Submit the username and password
                               return true;
                           }
                           return false;
                       });
}

// ### private methods ###

void LoginInput::createButtonBack() {
    buttonBack_ = ftxui::Button(
        std::string(STR_BACK),
        [&] {
            clearInfo();
            loginState_ = LoginState::BACK;
            mainTui_.stopRender();
        },
        GlobalButtonStyle());
}

void LoginInput::createButtonSubmit() {
    buttonSubmit_ = ftxui::Button(
        std::string(STR_SUBMIT),
        [&] {

            if (isValidUsername()) {

                std::thread loginThread;

                if (loginType_ == LoginType::REGISTER) {
                    controller_.tryRegister(username_, password_);

                    // Thread to check if registration is successful
                    loginThread = std::thread([this]() {
                        for (int i = 0; i < 20;
                            ++i) { // 2 seconds limit (20 * 100ms)
                            std::this_thread::sleep_for(
                                std::chrono::milliseconds(100));
                            if (controller_.getRegistrationState()
                                == Controller::RegistrationState::Registered) {
                                loginState_ = LoginState::SUBMIT;
                                mainTui_.stopRender();
                                return;
                            }
                        }
                        errorMessage_ = "Registration failed !";
                        message_.clear();
                        mainTui_
                            .forceRefresh(); // Post event to update screen
                    });

                } else if (loginType_ == LoginType::LOGIN) {
                    
                    controller_.tryLogin(username_, password_);

                    // Thread to check if authentication is successful
                    loginThread = std::thread([this]() {
                        for (int i = 0; i < 20;
                            ++i) { // 2 seconds limit (20 * 100ms)
                            std::this_thread::sleep_for(
                                std::chrono::milliseconds(100));
                            if (controller_.getAuthState()
                                == Controller::AuthState::Authenticated) {
                                loginState_ = LoginState::SUBMIT;
                                mainTui_.stopRender();
                                return;
                            }
                        }
                        errorMessage_ = "Login failed !";
                        message_.clear();
                        mainTui_
                            .forceRefresh(); // Post event to update screen
                    });
                }

                if (loginThread.joinable()) {
                    loginThread.join();
                }

                clearInfo();
            }
        },
        GlobalButtonStyle());
}

void LoginInput::displayWindow() {
    displayWindow_ = ftxui::Renderer(
        ftxui::Container::Vertical({
            inputUsername_,
            inputPassword_,
            buttonSubmit_,
            buttonBack_,
        }),
        [&] {
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

            if (!errorMessage_.empty()) {
                elements.push_back(ftxui::text(errorMessage_) | ftxui::center
                                   | ftxui::color(ftxui::Color::Red));
                elements.push_back(ftxui::separator());
            }

            if (!message_.empty()) {
                elements.push_back(ftxui::text(message_)
                                   | ftxui::color(ftxui::Color::Red)
                                   | ftxui::center);
                elements.push_back(ftxui::separator());
            }

            elements.push_back(buttonSubmit_->Render());
            elements.push_back(buttonBack_->Render());

            return ftxui::vbox(elements) | ftxui::borderHeavy | ftxui::center;
        });
}

bool LoginInput::isValidUsername() {
    errorMessage_.clear();

    if (username_.length() < 4) {
        errorMessage_ = "The lenght of your username is too short ! The username must have at least 4 characters";
        return false;
    }

    if (username_.length() > 20) {
        errorMessage_ = "The lenght of your username is too long ! It must have less than 20 characters";
    }

    for (const char c : username_) {
        if (invalidChars.find(c) != std::string::npos || isspace(c)) {
            if (isprint(c)) {
                errorMessage_ = "Your username contains an invalid character : '" + std::string(1, c) + "'";
            } else  {
                errorMessage_ = "Your username contains an invalid character with ASCII value " + std::to_string(static_cast<int>(c)) + " !";
            }
            return false;
        }
    }

    if (password_.empty()) {
        errorMessage_ = "Your password is empty ! You must enter a valid password";
        return false;
    }

    return true;
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

    mainTui_.render(displayWindow_);

    message_.clear();
    errorMessage_.clear();

    return loginState_;
}
