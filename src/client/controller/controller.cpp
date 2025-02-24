/**
 * @file controller.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Controller class definition file
 * @date 2025-02-24
 * 
 */

#include "controller.hpp"

// ### Public methods ###

Controller::Controller() {}

Controller::~Controller() {}

void Controller::run() {
    networkManager_.connect();

    screenManager_.drawStartScreen();
    handleLoginMenu();
    handleMainMenu();
}

// ### Private methods ###

void Controller::handleLoginMenu() {
    switch (screenManager_.runLoginMenu()) {
        case LoginState::EXIT:
            std::exit(0);
            break;
        
        case LoginState::LAUNCH_REGISTER: {
            handleInputMenu(InputType::REGISTER);
            break;
        }
            
        case LoginState::LAUNCH_LOGIN:
            handleInputMenu(InputType::LOGIN);
            break;

        default:
            throw std::runtime_error("Invalid LoginState");    
    }
}

void Controller::handleInputMenu(const InputType type) {
    if (type == InputType::LOGIN) {
        switch (screenManager_.runLoginInput()) {
            case InputState::BACK:
                handleLoginMenu();
                break;
            
            case InputState::SUBMIT: {
                // TODO: add logic with controller and server to check with the database for the logic
                LoginInfo info = screenManager_.getLoginInfo();
                // TODO : It's for the test, must be removed and add logic with server
                const std::string username = "ethan";
                const std::string password = "ethan";
                if (info.username != username && info.password != password) {
                    screenManager_.addMessageToLoginInput("Invalid username or password");
                    handleInputMenu(InputType::LOGIN);
                }
                break;
            }
                
            default:
                throw std::runtime_error("Invalid InputState");
        }
    } else {
        switch (screenManager_.runRegisterInput()) {
            case InputState::BACK:
                handleLoginMenu();
                break;
            
            case InputState::SUBMIT: {
                // TODO: add logic with controller and server to check with the database for the register
                LoginInfo info = screenManager_.getRegisterInfo();
                // TODO : It's for the test, must be removed and add logic with server
                const std::string username = "ethan";
                const std::string password = "ethan";
                if (info.username != username && info.password != password) {
                    screenManager_.addMessageToRegisterInput("Invalid username or password");
                    handleInputMenu(InputType::REGISTER);
                } else {
                    screenManager_.addMessageToLoginInput("Your account has been created, please login");
                    handleInputMenu(InputType::LOGIN);
                }
                break;
            }
                
            default:
                throw std::runtime_error("Invalid InputState");
        }
    }
}

void Controller::handleMainMenu() {
    switch (screenManager_.runMainMenu()) {

        case MainMenuState::PLAY: {
            screenManager_.runGame();
            handleMainMenu();
            break;
        }

        case MainMenuState::EXIT:
            std::exit(0); // TODO: check the exit
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

            screenManager_.getMainMenu()->renderRanking(ranking);
            handleMainMenu();
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

            screenManager_.getMainMenu()->renderFriendsManager(friendsList);
            handleMainMenu();
            break;
        }
            
        case MainMenuState::MANAGE_PROFILE:
            screenManager_.getMainMenu()->renderProfileManager();
            handleMainMenu();
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
    
            screenManager_.getMainMenu()->renderMessagingMenu(friendsList);
            handleMainMenu();
            break;
        }

        default:
            throw std::runtime_error("Invalid MainMenuState");
    }
}