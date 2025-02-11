#include "login_input.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>

LoginInput::LoginInput(std::shared_ptr<ScreenManager> screenManager, std::string &title) : screenManager_(screenManager), title_(title) {}

void LoginInput::run() {
    std::string message;

    ftxui::Component inputUsername = ftxui::Input(&username_, "Enter username");
    ftxui::Component inputPassword = ftxui::Input(&password_, "Enter password");

    auto buttonSubmit = ftxui::Button("Submit", [&] {
        if (!username_.empty() && !password_.empty()) {
            screenManager_->ExitLoopClosure();
        } else {
            username_.clear();
            password_.clear();
            message = "Please enter a valid username and a valid password";
        }
    });

    auto component = ftxui::Container::Vertical({
        inputUsername,
        inputPassword,
        buttonSubmit,
    });

    auto renderer = ftxui::Renderer(component, [&] {
        return ftxui::vbox({
            ftxui::text(title_) | ftxui::bold | ftxui::center,
            ftxui::separator(),
            inputUsername->Render(),
            inputPassword->Render(),
            buttonSubmit->Render(),
            ftxui::text(message)
        }) | ftxui::border;
    });
   
    screenManager_->loopScreen(renderer);

}