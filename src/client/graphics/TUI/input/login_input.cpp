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
 
 #include <chrono>
 #include <ftxui/component/component.hpp>
 #include <ftxui/component/component_base.hpp>
 #include <ftxui/component/screen_interactive.hpp>
 #include <ftxui/dom/elements.hpp>
 
 #include <string>
 #include <thread>
 
 // ### Constructor ###
 LoginInput::LoginInput(ftxui::ScreenInteractive &screen, Controller &controller,
                        std::string title, LoginType loginType)
     : screen_(screen), controller_(controller), title_(title),
       loginType_(loginType), loginState_(LoginState::NONE) {
 
     createButtonBack();
     createButtonSubmit();
 
 
     inputUsername_ = ftxui::Input(&username_, "Enter username") | ftxui::borderHeavy | 
     ftxui::CatchEvent([this](const ftxui::Event& event) {
        if (event == ftxui::Event::Return) {
            screen_.PostEvent(ftxui::Event::Tab); // Simule un Tab pour passer au champ suivant
            return true; // Empêche l'entrée d'une nouvelle ligne
        }
        return false;
    });

     inputPassword_ = ftxui::Input(&password_, "Enter password", PasswordInputOption()) | ftxui::borderHeavy |
     ftxui::CatchEvent([this](const ftxui::Event& event) {
        if (event == ftxui::Event::Return) {
            buttonSubmit_->OnEvent(event); // Simuler un clic sur "Submit"
            return true; // Empêcher le retour à la ligne
        }
        return false;
    });
 }
 
 // ### protected methods ###
 
 void LoginInput::createButtonBack() {
     buttonBack_ = ftxui::Button(
                       "Back",
                       [&] {
                           clearInfo();
                           loginState_ = LoginState::BACK;
                           screen_.ExitLoopClosure()();
                       }, GlobalButtonStyle());
 }
 
 void LoginInput::createButtonSubmit() {
     buttonSubmit_ = ftxui::Button(
         "Submit",
         [&] {
             if (loginType_ == LoginType::REGISTER) {
                 controller_.tryRegister(username_, password_);
 
                 // Thread to check if registration is successful
                 std::thread([this]() {
                     for (int i = 0; i < 20; ++i) { // 2 seconds limit (20 * 100ms)
                         std::this_thread::sleep_for(std::chrono::milliseconds(100));
                         if (controller_.getRegistrationState() == Controller::RegistrationState::Registered) {
                             loginState_ = LoginState::SUBMIT;
                             screen_.ExitLoopClosure()();
                             return;
                         }
                     }
                     clearInfo();
                     msg_ = "Registration failed! Try again.";
                     screen_.PostEvent(ftxui::Event::Custom); // Post event to update screen
                 }).detach();
 
             } else if (loginType_ == LoginType::LOGIN) {
                 controller_.tryLogin(username_, password_);
 
                 // Thread to check if registration is successful
                 std::thread([this]() {
                     for (int i = 0; i < 20; ++i) { // 2 seconds limit (20 * 100ms)
                         std::this_thread::sleep_for(std::chrono::milliseconds(100));
                         if (controller_.getAuthState() == Controller::AuthState::Authenticated) {
                             loginState_ = LoginState::SUBMIT;
                             screen_.ExitLoopClosure()();
                             return;
                         }
                     }
                     clearInfo();
                     msg_ = "Incorrect username or password!";
                     screen_.PostEvent(ftxui::Event::Custom); // Post event to update screen
                 }).detach();
             }
             clearInfo();
         },
         GlobalButtonStyle()
     );
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
 
     screen_.Loop(handleCtrl(displayWindow_));
 
     return loginState_;
 }
 