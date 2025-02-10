#include "login_input.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>

LoginInput::LoginInput(std::shared_ptr<ScreenManager> screenManager) : screenManager_(screenManager) {}

void LoginInput::run() {
    std::string message;

    ftxui::Component inputUsername = ftxui::Input(&username_, "Enter username");
    ftxui::Component inputPassword = ftxui::Input(&password_, "Enter password");

    auto buttonSubmit = ftxui::Button("Submit", [&] {
        if (!username_.empty() && !password_.empty()) {
            screenManager_->ExitLoopClosure();
        } else {
            message = "Please enter a username and a password";
        }
    });

    auto component = ftxui::Container::Vertical({
        inputUsername,
        inputPassword,
        buttonSubmit,
    });

    auto renderer = ftxui::Renderer(component, [&] {
        return ftxui::vbox({
            inputUsername->Render(),
            inputPassword->Render(),
            buttonSubmit->Render(),
        }) | ftxui::border;
    });
   
    screenManager_->loopScreen(renderer);

}