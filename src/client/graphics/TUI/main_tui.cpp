#include "main_tui.hpp"

#include "../../core/controller/controller.hpp"
#include "ftxui_config/ftxui_config.hpp"
#include "graphics/TUI/login_menu/login_menu.hpp"

namespace TUI {

    MainTui::MainTui() : screen_(ftxui::ScreenInteractive::Fullscreen()) {
        screen_.ForceHandleCtrlC(false);
        screen_.ForceHandleCtrlZ(false);
    }

    void MainTui::run(Controller &controller) {
        LoginMenu loginMenu(*this, controller);
        MainMenu mainMenu(*this, controller);

        drawStartScreen();

        // Handle the login menu
        if (loginMenu.render() == LoginResult::SUCCESS) {
            mainMenu.render();
        }
        drawEndScreen();
    }

    void MainTui::render(ftxui::Component &component) {
        currentWindow_ = component;
        screen_.Loop(handleCtrl(currentWindow_));
    }

    void MainTui::stopRender() { screen_.ExitLoopClosure()(); }

    void MainTui::forceRefresh(UpdateType /* updateType */) {
        screen_.PostEvent(ftxui::Event::Custom);
    }

    void MainTui::simulateTab() { screen_.PostEvent(ftxui::Event::Tab); }

    // ### Private methods ###

    void MainTui::drawStartScreen() {
        bool exit = false;

        ftxui::Component title =
            ftxui::Renderer(
                [&] { return exit ? ftxui::text("") : WELCOME_TITLE; })
            | ftxui::center;

        // Use a thread to exit this display after 2 seconds
        std::thread([&] {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            exit = true;
            forceRefresh(UpdateType::OTHER); // Refresh the screen to exit
                                             // the display after 3 seconds
            stopRender();
        }).detach();

        render(title);
    }

    void MainTui::drawEndScreen() {
        bool exit = false;

        ftxui::Component title =
            ftxui::Renderer(
                [&] { return exit ? ftxui::text("") : GOODBYE_TITLE; })
            | ftxui::center;

        std::thread([&] {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            exit = true;
            forceRefresh(UpdateType::OTHER); // Refresh the screen to exit
                                             // the display after 2 seconds
            stopRender();
        }).detach();

        render(title);
    }

    ftxui::Component MainTui::handleCtrl(ftxui::Component &component) {
        return ftxui::CatchEvent(component, [&](ftxui::Event event) {
            if (event == ftxui::Event::Custom) {
                return true;
            } else if (event == ftxui::Event::Character('\x03')
                       || event == ftxui::Event::Character('\x1A')) {
                forceRefresh(UpdateType::OTHER);
                return true;
            }
            return false;
        });
    }

} // namespace TUI
