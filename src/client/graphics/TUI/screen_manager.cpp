#include "screen_manager.hpp"

#include "ftxui_config/ftxui_config.hpp"

#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

// ### Public methods ###
ScreenManager::ScreenManager(Controller &controller)
    : controller_(controller), screen_(ftxui::ScreenInteractive::Fullscreen()),
      loginMenu_(LoginMenu(*this, controller_)),
      mainMenu_(MainMenu(*this, controller_)) {
    screen_.ForceHandleCtrlC(false);
    screen_.ForceHandleCtrlZ(false);
}

void ScreenManager::run() {
    drawStartScreen();

    // Handle the login menu
    if (loginMenu_.render() == LoginResult::SUCCESS) {
        mainMenu_.render();
    }
    drawEndScreen();
}

void ScreenManager::render(ftxui::Component &component) {
    screen_.Loop(handleCtrl(component));
}

void ScreenManager::stopRender() {
    screen_.ExitLoopClosure()();
}

void ScreenManager::forceRefresh() {
    screen_.PostEvent(ftxui::Event::Custom);
}

void ScreenManager::simulateTab() {
    screen_.PostEvent(ftxui::Event::Tab);
}

// ### Private methods ###

void ScreenManager::drawStartScreen() {
    bool exit = false;

    ftxui::Component title =
        ftxui::Renderer([&] {
            return exit ? ftxui::text("") : WELCOME_TITLE;
        }) | ftxui::center;

    // Use a thread to exit this display after 2 seconds
    std::thread([&] {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        exit = true;
        forceRefresh(); // Refresh the screen to exit
                                                 // the display after 3 seconds
        stopRender();
    }).detach();

    render(title);
}

void ScreenManager::drawEndScreen() {
    bool exit = false;

    ftxui::Component title =
        ftxui::Renderer([&] {
            return exit ? ftxui::text("") : GOODBYE_TITLE;}) | ftxui::center;

    std::thread([&] {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        exit = true;
        forceRefresh(); // Refresh the screen to exit
                                                 // the display after 2 seconds
        stopRender();
    }).detach();

    render(title);
}

ftxui::Component ScreenManager::handleCtrlC(ftxui::Component &component) {
    return ftxui::CatchEvent(component, [&](ftxui::Event event) {
        forceRefresh();
        return event == ftxui::Event::Character('\x03'); // Ctrl+C event
    });
}

ftxui::Component ScreenManager::handleCtrlZ(ftxui::Component &component) {
    return ftxui::CatchEvent(component, [](ftxui::Event event) {
        return event == ftxui::Event::Character('\x1A'); // Ctrl+Z event
    });
}

ftxui::Component ScreenManager::handleCtrl(ftxui::Component &component) {
    return ftxui::CatchEvent(component, [](ftxui::Event event) {
        return event == ftxui::Event::Character('\x1A')
               || event
                      == ftxui::Event::Character(
                          '\x03'); // Ctrl+Z or Ctrl+C event
    });
}