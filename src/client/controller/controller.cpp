/**
 * @file controller.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Controller class definition file
 * @date 2025-02-24
 *
 */

#include "controller.hpp"
#include "../network/network_manager.hpp"
#include "../view/TUI/screen_manager.hpp"

// ### Public methods ###

Controller::Controller() : screenManager_(ScreenManager(this)) {};

Controller::~Controller() {}

void Controller::run() {
    networkManager_.connect();

    screenManager_.run();
}

bool Controller::verifyRegister(const std::string &username, const std::string &password) const {
    // TODO: check with the server for the register
    // TODO: remove this because it's an example
    if (username == "ethan" && password == "ethan") {
        return true;
    }
    return false;
}

bool Controller::verifyLogin(const std::string &username, const std::string &password) const {
    // TODO: check with the server if the username and password are correct
    // TODO: remove this because it's an example
    if (username == "ethan" && password == "ethan") {
        return true;
    }
    return false;
}