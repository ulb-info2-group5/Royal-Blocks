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

std::vector<std::tuple<int, std::string, int>> Controller::getRanking() const {
    // TODO: communicate with the server to get the ranking
    // TODO: remove this because it's an example
    std::vector<std::tuple<int, std::string, int>> ranking;
    ranking.push_back(std::make_tuple(1, "user1", 100));
    ranking.push_back(std::make_tuple(2, "user2", 90));
    ranking.push_back(std::make_tuple(3, "user3", 80));
    ranking.push_back(std::make_tuple(4, "user4", 70));
    ranking.push_back(std::make_tuple(5, "user5", 60));
    
    return ranking;
}

bool Controller::changeProfile(const std::string &username, const std::string &password) const {
    // TODO: communicate with the server to change the profile
    // TODO: remove this because it's an example
    if (username == "ethan" && password == "ethan") {
        return true;
    }
    return false;
}

std::vector<std::string> Controller::getFriendsList() const {
    // TODO: communicate with the server to get the friends list
    // TODO: remove this because it's an example
    std::vector<std::string> friendsList;
    friendsList.push_back("friend1");
    friendsList.push_back("friend2");
    friendsList.push_back("friend3");
    friendsList.push_back("friend4");
    friendsList.push_back("friend5");

    return friendsList;
}

bool Controller::addFriend(const std::string &friendName) const {
    // TODO: communicate with the server to add the friend
    return true;
}

bool Controller::removeFriend(const std::string &friendName) const {
    // TODO: communicate with the server to remove the friend
    return true;
}