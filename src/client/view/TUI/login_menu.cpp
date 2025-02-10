#include "login_menu.hpp"
#include <ftxui/component/component.hpp>

LoginMenu::LoginMenu(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<LoginInput> loginInput) : MenuUi(screenManager, "Login Menu", std::vector<std::string>{"Login", "Exit"}), loginInput_(loginInput) {}

void LoginMenu::run() {
    std::string message;

    auto buttonRegister = ftxui::Button("Register", [&] {
        loginInput_->run();
    });

    auto buttonLogin = ftxui::Button("Login", [&] {
        loginInput_->run();
    });

    auto buttonBack = ftxui::Button("Back", [&] {
        screenManager_->ExitLoopClosure();
    });

    auto component = ftxui::Container::Vertical({
        buttonRegister,
        buttonLogin,
        buttonBack,
    });

    auto renderer = ftxui::Renderer(component, [&] {
        return ftxui::vbox({
            ftxui::text("Login Menu") | ftxui::bold | ftxui::center,
            buttonRegister->Render(),
            buttonLogin->Render(),
            buttonBack->Render(),
            ftxui::text(message) | ftxui::color(ftxui::Color::Red),
        }) | ftxui::border;
    });

    screenManager_->loopScreen(renderer);
}