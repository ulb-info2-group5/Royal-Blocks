#include "screen_manager.hpp"
#include <memory>


// ### Public methods ###
ScreenManager::ScreenManager(Controller *controller) : controller_(controller), screen_(std::shared_ptr<ftxui::ScreenInteractive>(new ftxui::ScreenInteractive(ftxui::ScreenInteractive::Fullscreen()))), loginMenu_(LoginMenu(screen_, controller_)), mainMenu_(MainMenu(screen_, controller_)) {}

void ScreenManager::run() {
    drawStartScreen();

    // Handle the login menu
    loginMenu_.render();
    mainMenu_.render();
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
        screen_->PostEvent(ftxui::Event::Custom); // Refresh the screen to exit the display after 2 seconds
        screen_->ExitLoopClosure()();
    }).detach();

    screen_->Loop(title);    
}