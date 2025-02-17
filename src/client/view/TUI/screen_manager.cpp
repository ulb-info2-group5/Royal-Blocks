#include "screen_manager.hpp"

#include "input/login_input.hpp"
#include "login_menu/login_menu.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <string>
#include <thread>
#include <vector>

// ### Public methods ###
ScreenManager::ScreenManager() {
    std::string loginInstructions = "Please enter your username and password to login.";
    std::string registerInstructions = "Please enter a username and a password to create an account.";
    loginInput_.addInstruction(loginInstructions);
    registerInput_.addInstruction(registerInstructions);
}

void ScreenManager::run() {
    drawStartScreen();
    manageLoginMenu();
    manageMainMenu();
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

void ScreenManager::manageLoginMenu() {
    switch (loginMenu_.render()) {
        case LoginState::EXIT:
            std::exit(0);
            break;
        
        case LoginState::LAUNCH_REGISTER: {
            manageInputMenu(InputType::REGISTER);
            break;
        }
            
        case LoginState::LAUNCH_LOGIN:
            manageInputMenu(InputType::LOGIN);
            break;

        default:
            throw std::runtime_error("Invalid LoginState");    
    }
}

void ScreenManager::manageInputMenu(const InputType type) {
    if (type == InputType::LOGIN) {
        switch (loginInput_.render()) {
            case InputState::BACK:
                manageLoginMenu();
                break;
            
            case InputState::DONE:
                break;
                
            default:
                throw std::runtime_error("Invalid InputState");
        }
    } else {
        switch (registerInput_.render()) {
            case InputState::BACK:
                manageLoginMenu();
                break;
            
            case InputState::DONE: {
                std::string msg = "Your account has been created successfully! You can now login.";
                loginInput_.addMessage(msg);
                manageInputMenu(InputType::LOGIN);
                break;
            }
                
            default:
                throw std::runtime_error("Invalid InputState");
        }
    }
}

void ScreenManager::manageMainMenu() {
    switch (mainMenu_.render()) {
        case MainMenuState::EXIT:
            std::exit(0);
            break;
        
        case MainMenuState::LOOK_RANKING: {
            // TODO: remove it because it's an example
            // TODO: communicate with the server to get the ranking
            std::vector<std::tuple<int, std::string, int>> ranking = {};
            ranking.push_back(std::make_tuple(1, "Player1", 100));
            ranking.push_back(std::make_tuple(2, "Player2", 90));
            ranking.push_back(std::make_tuple(3, "Player3", 80));
            ranking.push_back(std::make_tuple(4, "Player4", 70));
            ranking.push_back(std::make_tuple(5, "Player5", 60));

            mainMenu_.renderRanking(ranking);
            manageMainMenu();
            break;
        }
            
        case MainMenuState::MANAGE_FRIENDS_LIST: {
            // TODO: remove it because it's an example
            // TODO: communicate with the server to get the friendsList
            std::vector<std::string> friendsList = {
                "Player1",
                "Player2",
                "ethan",
                "readyPlayerOne",
                "theBestPlayerOfTheGame"
            };

            mainMenu_.renderFriendsManager(friendsList);
            manageMainMenu();
            break;
        }
            
        case MainMenuState::MANAGE_PROFILE:
            break;
            
        case MainMenuState::SEND_MESSAGES: {
            // TODO: remove it because it's an example
            // TODO: communicate with the server to get the friends list
            std::vector<std::string> friendsList = {
                "Player1",
                "Player2",
                "ethan",
                "readyPlayerOne",
                "theBestPlayerOfTheGame"
            };
    
            mainMenu_.renderMessagingMenu(friendsList);
            manageMainMenu();
            break;
        }
            
        default:
            throw std::runtime_error("Invalid MainMenuState");
    }
}