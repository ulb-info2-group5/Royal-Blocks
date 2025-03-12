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

// ### Constructor ###
LoginInput::LoginInput(ScreenManager &screenManager, Controller &controller,
                       std::string title, LoginType loginType)
    : screenManager_(screenManager), controller_(controller), title_(title),
      loginType_(loginType), loginState_(LoginState::NONE) {

    createButtonBack();
    createButtonSubmit();

    inputUsername_ =
        ftxui::Input(&username_, std::string(STR_ENTER_USERNAME))
        | ftxui::borderHeavy
        | ftxui::CatchEvent([this](const ftxui::Event &event) {
              if (event == ftxui::Event::Return) {
                  screenManager_.simulateTab(); // Move to the next input
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

// ### protected methods ###

void LoginInput::createButtonBack() {
    buttonBack_ = ftxui::Button(
        std::string(STR_BACK),
        [&] {
            clearInfo();
            loginState_ = LoginState::BACK;
            screenManager_.stopRender();
        },
        GlobalButtonStyle());
}

void LoginInput::createButtonSubmit() {
    buttonSubmit_ = ftxui::Button(
        std::string(STR_SUBMIT),
        [&] {
            if (loginType_ == LoginType::REGISTER) {
                controller_.tryRegister(username_, password_);

                // Thread to check if registration is successful
                std::thread([this]() {
                    for (int i = 0; i < 20;
                         ++i) { // 2 seconds limit (20 * 100ms)
                        std::this_thread::sleep_for(
                            std::chrono::milliseconds(100));
                        if (controller_.getRegistrationState()
                            == Controller::RegistrationState::Registered) {
                            loginState_ = LoginState::SUBMIT;
                            screenManager_.stopRender();
                            return;
                        }
                    }
                    clearInfo();
                    msg_ = STR_REGISTRATION_FAILED;
                    screenManager_
                        .forceRefresh(); // Post event to update screen
                }).detach();

            } else if (loginType_ == LoginType::LOGIN) {
                controller_.tryLogin(username_, password_);

                // Thread to check if registration is successful
                std::thread([this]() {
                    for (int i = 0; i < 20;
                         ++i) { // 2 seconds limit (20 * 100ms)
                        std::this_thread::sleep_for(
                            std::chrono::milliseconds(100));
                        if (controller_.getAuthState()
                            == Controller::AuthState::Authenticated) {
                            loginState_ = LoginState::SUBMIT;
                            screenManager_.stopRender();
                            return;
                        }
                    }
                    clearInfo();
                    msg_ = STR_INCORRECT;
                    screenManager_
                        .forceRefresh(); // Post event to update screen
                }).detach();
            }
            clearInfo();
        },
        GlobalButtonStyle());
}

void LoginInput::displayWindow() {

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
            elements.push_back(ftxui::text(msg_) | ftxui::center
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
    msg_.clear();
    message_.clear();
}

LoginState LoginInput::render() {
    displayWindow();

    screenManager_.render(displayWindow_);

    return loginState_;
}
