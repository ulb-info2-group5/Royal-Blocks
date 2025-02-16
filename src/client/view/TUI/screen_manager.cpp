#include "screen_manager.hpp"
#include "login_menu/login_menu.hpp"
#include "main_menu/main_menu.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <thread>
#include <csignal>

// ### Public methods ###
ScreenManager::ScreenManager() : screen_(ftxui::ScreenInteractive::Fullscreen()), component_(nullptr), exit_(false) {}

void ScreenManager::run() {
    LoginMenu loginMenu = LoginMenu(this);
    MainMenu mainMenu = MainMenu(this);

    drawStartScreen();
    loginMenu.render();
    if (exit_) {
        return;
    }
    mainMenu.render();
}

void ScreenManager::renderComponent(const ftxui::Component &component) {
    if (component_ != nullptr) {
        screen_.ExitLoopClosure();
    }
    component_ = component;
    screen_.Loop(component_);

}

void ScreenManager::renderComponentNoExitLoop(const ftxui::Component &component) {
    component_ = component;
    screen_.Loop(component_);
}


void ScreenManager::exit() {
    exit_ = true;
    exitLoop();
}

void ScreenManager::exitLoop() {
    screen_.ExitLoopClosure()();
    component_ = nullptr;
}


// ### Private methods ###
void ScreenManager::drawStartScreen() {

    bool exit = false;

    ftxui::Component title = ftxui::Renderer([&] {
        return exit ? ftxui::text("") : ftxui::vbox({
            ftxui::text(R"(__          __  _                            _          _____                   _   _______   _        _       _ )"),
            ftxui::text(R"(\ \        / / | |                          | |        |  __ \                 | | |__   __| | |      (_)     | |)"),
            ftxui::text(R"( \ \  /\  / /__| | ___ ___  _ __ ___   ___  | |_ ___   | |__) |___  _   _  __ _| |    | | ___| |_ _ __ _ ___  | |)"),
            ftxui::text(R"(  \ \/  \/ / _ \ |/ __/ _ \| '_ ` _ \ / _ \ | __/ _ \  |  _  // _ \| | | |/ _` | |    | |/ _ \ __| '__| / __| | |)"),
            ftxui::text(R"(   \  /\  /  __/ | (_| (_) | | | | | |  __/ | || (_) | | | \ \ (_) | |_| | (_| | |    | |  __/ |_| |  | \__ \ |_|)"),
            ftxui::text(R"(    \/  \/ \___|_|\___\___/|_| |_| |_|\___|  \__\___/  |_|  \_\___/ \__, |\__,_|_|    |_|\___|\__|_|  |_|___/ (_))"),
            ftxui::text(R"(                                                                     __/ |                                       )"),
            ftxui::text(R"(                                                                    |___/                                        )"),
        });
    }) | ftxui::border | ftxui::center;

    // Use a thread to exit this display after 2 seconds
    std::thread([&] {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        exit = true;
        screen_.PostEvent(ftxui::Event::Custom); // Refresh the screen to exit the display after 2 seconds
        screen_.ExitLoopClosure()();
    }).detach();

    renderComponent(title);    
}