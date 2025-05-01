#include "main_tui.hpp"

#include "../../core/controller/controller.hpp"
#include "ftxui_config/ftxui_config.hpp"
#include "graphics/TUI/login_menu/login_menu.hpp"
#include "graphics/TUI/main_menu/main_menu.hpp"
#include "graphics/common/abstract_display.hpp"

namespace TUI {

    MainTui::MainTui(Controller &controller) : AbstractDisplay(controller), screen_(ftxui::ScreenInteractive::Fullscreen()), loginMenu_(*this, controller_), mainMenu_(*this, controller_) {
        screen_.ForceHandleCtrlC(false);
        screen_.ForceHandleCtrlZ(false);
    }

    void MainTui::run() {
        drawStartScreen();

        // Handle the login menu
        if (loginMenu_.render() == LoginResult::SUCCESS) {
            mainMenu_.render();
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
        std::thread startScreenThread([&] {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            exit = true;
            forceRefresh(UpdateType::OTHER); // Refresh the screen to exit
                                             // the display after 3 seconds
            stopRender();
        });

        render(title);

        if (startScreenThread.joinable()) {
            startScreenThread.join();
        }
    }

    void MainTui::drawEndScreen() {
        bool exit = false;

        ftxui::Component title =
            ftxui::Renderer(
                [&] { return exit ? ftxui::text("") : GOODBYE_TITLE; })
            | ftxui::center;

        std::thread endScreenThread([&] {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            exit = true;
            forceRefresh(UpdateType::OTHER); // Refresh the screen to exit
                                             // the display after 2 seconds
            stopRender();
        });

        render(title);

        if (endScreenThread.joinable()) {
            endScreenThread.join();
        }
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

    void MainTui::onDisconnected() {
        // DO NOTHING ?
    }
} // namespace TUI
