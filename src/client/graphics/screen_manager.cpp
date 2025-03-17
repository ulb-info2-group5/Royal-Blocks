#include "screen_manager.hpp"

#include <ftxui/component/component_base.hpp>
#include <qapplication.h>

#include "TUI/ftxui_config/ftxui_config.hpp"
#include "GUI/mainwindow.h"
#include "../core/controller/controller.hpp"

// ### Public methods ###
ScreenManager::ScreenManager(Controller &controller, UiChoice uiChoice)
    : controller_(controller), uiChoice_(uiChoice),
      screen_(ftxui::ScreenInteractive::Fullscreen()),
      loginMenu_(LoginMenu(*this, controller_)),
      mainMenu_(MainMenu(*this, controller_)) {
    screen_.ForceHandleCtrlC(false);
    screen_.ForceHandleCtrlZ(false);
}

void ScreenManager::run() {
    if (uiChoice_ == UiChoice::TUI) {
        drawStartScreen();

        // Handle the login menu
        if (loginMenu_.render() == LoginResult::SUCCESS) {
            mainMenu_.render();
        }
        drawEndScreen();
    }

    int argc = 2;
    char *argv[] = {"./tetris_royal_client", "--gui"};
    QApplication app(argc, argv);
    MainWindow mainWindow(nullptr, &controller_);
    mainWindow.show();
    app.exec();
}

void ScreenManager::render(ftxui::Component &component) {
    currentWindow_ = component;
    screen_.Loop(handleCtrl(currentWindow_));
}

void ScreenManager::stopRender() { screen_.ExitLoopClosure()(); }

void ScreenManager::forceRefresh() { screen_.PostEvent(ftxui::Event::Custom); }

void ScreenManager::simulateTab() { screen_.PostEvent(ftxui::Event::Tab); }

// ### Private methods ###

void ScreenManager::drawStartScreen() {
    bool exit = false;

    ftxui::Component title =
        ftxui::Renderer([&] { return exit ? ftxui::text("") : WELCOME_TITLE; })
        | ftxui::center;

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
        ftxui::Renderer([&] { return exit ? ftxui::text("") : GOODBYE_TITLE; })
        | ftxui::center;

    std::thread([&] {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        exit = true;
        forceRefresh(); // Refresh the screen to exit
                        // the display after 2 seconds
        stopRender();
    }).detach();

    render(title);
}

ftxui::Component ScreenManager::handleCtrl(ftxui::Component &component) {
    return ftxui::CatchEvent(component, [&](ftxui::Event event) {
        if (event == ftxui::Event::Custom) {
            return true;
        } else if (event == ftxui::Event::Character('\x03')
                   || event == ftxui::Event::Character('\x1A')) {
            forceRefresh();
            return true;
        }
        return false;
    });
}