#include "login_menu.hpp"
#include "login_input.hpp"
#include <ftxui/component/component.hpp>

LoginMenu::LoginMenu(std::shared_ptr<ScreenManager> screenManager) : MenuUi(screenManager, "Login Menu", std::vector<std::string>{"Login", "Exit"}) {}

void LoginMenu::run() {
    std::string loginStr = "Login";
    std::string registerStr = "Register";
    LoginInput loginInput(screenManager_, loginStr);
    LoginInput registerInput(screenManager_, registerStr);

    auto buttonLogin = ftxui::Button("Login", [&] {
        loginInput.run();
    });

    auto buttonRegister = ftxui::Button("Register", [&] {
        registerInput.run();
        loginInput.run();
    });

    auto buttonBack = ftxui::Button("Exit", [&] {
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
        }) | ftxui::border;
    });

    screenManager_->loopScreen(renderer);
}