#include "screen_manager.hpp"
#include "handle_ctrl/handle_ctrl.hpp"
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

// ### Public methods ###
ScreenManager::ScreenManager(Controller &controller)
    : controller_(controller), screen_(ftxui::ScreenInteractive::Fullscreen()),
      loginMenu_(LoginMenu(screen_, controller_)),
      mainMenu_(MainMenu(screen_, controller_)) {
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

// ### Private methods ###

void ScreenManager::drawStartScreen() {

    bool exit = false;

    ftxui::Component title =
        ftxui::Renderer([&] {
            return exit
                       ? ftxui::text("")
                       : ftxui::vbox({
                           ftxui::text(
                               R"(__          __  _                            _          _____                   _   _______   _        _       _ )"),
                           ftxui::text(
                               R"(\ \        / / | |                          | |        |  __ \                 | | |__   __| | |      (_)     | |)"),
                           ftxui::text(
                               R"( \ \  /\  / /__| | ___ ___  _ __ ___   ___  | |_ ___   | |__) |___  _   _  __ _| |    | | ___| |_ _ __ _ ___  | |)"),
                           ftxui::text(
                               R"(  \ \/  \/ / _ \ |/ __/ _ \| '_ ` _ \ / _ \ | __/ _ \  |  _  // _ \| | | |/ _` | |    | |/ _ \ __| '__| / __| | |)"),
                           ftxui::text(
                               R"(   \  /\  /  __/ | (_| (_) | | | | | |  __/ | || (_) | | | \ \ (_) | |_| | (_| | |    | |  __/ |_| |  | \__ \ |_|)"),
                           ftxui::text(
                               R"(    \/  \/ \___|_|\___\___/|_| |_| |_|\___|  \__\___/  |_|  \_\___/ \__, |\__,_|_|    |_|\___|\__|_|  |_|___/ (_))"),
                           ftxui::text(
                               R"(                                                                     __/ |                                       )"),
                           ftxui::text(
                               R"(                                                                    |___/                                        )"),
                       });
        }) | ftxui::center;

    // Use a thread to exit this display after 2 seconds
    std::thread([&] {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        exit = true;
        screen_.PostEvent(ftxui::Event::Custom); // Refresh the screen to exit
                                                  // the display after 3 seconds
        screen_.ExitLoopClosure()();
    }).detach();

    screen_.Loop(handleCtrl(title));
}

void ScreenManager::drawEndScreen() {
    bool exit = false;

    ftxui::Component title =
        ftxui::Renderer([&] {
            return exit
                       ? ftxui::text("")
                       : ftxui::vbox({
                        ftxui::text(R"(  ______                 _ _                    _ )"),
                        ftxui::text(R"( / _____)               | | |                  | |)"),
                        ftxui::text(R"(| /  ___  ___   ___   _ | | | _  _   _  ____   | |)"),
                        ftxui::text(R"(| | (___)/ _ \ / _ \ / || | || \| | | |/ _  )  |_|)"),
                        ftxui::text(R"(| \____/| |_| | |_| ( (_| | |_) ) |_| ( (/ /    _ )"),
                        ftxui::text(R"( \_____/ \___/ \___/ \____|____/ \__  |\____)  |_|)"),
                        ftxui::text(R"(                                (____/            )"),
            });
        }) | ftxui::center;

    std::thread([&] {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        exit = true;
        screen_.PostEvent(ftxui::Event::Custom); // Refresh the screen to exit
                                                    // the display after 2 seconds
        screen_.ExitLoopClosure()();
    }).detach();

    screen_.Loop(handleCtrl(title));
}