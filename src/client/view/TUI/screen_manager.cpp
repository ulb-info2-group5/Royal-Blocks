#include "screen_manager.hpp"
#include "input/login_input.hpp"
#include "login_menu/login_menu.hpp"
#include "main_menu/main_menu.hpp"

// ### Public methods ###
ScreenManager::ScreenManager() {
    loginInput_.addInstruction(LOGIN_INSTRUCTIONS);
    registerInput_.addInstruction(REGISTER_INSTRUCTIONS);
}

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

LoginInfo ScreenManager::getLoginInfo() {
    LoginInfo info;
    info.username = loginInput_.getUsername();
    info.password = loginInput_.getPassword();
    return info;
}

LoginInfo ScreenManager::getRegisterInfo() {
    LoginInfo info;
    info.username = registerInput_.getUsername();
    info.password = registerInput_.getPassword();
    return info;
}

LoginState ScreenManager::runLoginMenu() {
    return loginMenu_.render();
}

InputState ScreenManager::runLoginInput() {
    loginInput_.clearInfo();
    return loginInput_.render();
}

InputState ScreenManager::runRegisterInput() {
    registerInput_.clearInfo();
    return registerInput_.render();
}

MainMenuState ScreenManager::runMainMenu() {
    return mainMenu_.render();
}

void ScreenManager::runGame() {
    game_.render();
}

void ScreenManager::addMessageToLoginInput(const std::string_view message) {
    loginInput_.addMessage(message);
}

void ScreenManager::addMessageToRegisterInput(const std::string_view message) {
    registerInput_.addMessage(message);
}

void ScreenManager::runRankingMenu(std::vector<std::tuple<int, std::string, int>> &ranking) {
    mainMenu_.renderRanking(ranking);
}

void ScreenManager::runFriendsManager(const std::vector<std::string> &friendsList) {
    mainMenu_.renderFriendsManager(friendsList);
}

std::vector<std::string> ScreenManager::runProfileManager() {
    mainMenu_.renderProfileManager();
    return mainMenu_.getUserNewInput();
}