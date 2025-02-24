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
    screenManager_.manageMainMenu();
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