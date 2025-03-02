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

// ### Private methods ###

void Controller::handlePacket(const std::string &pack) {
    std::cerr << "called with " << pack << std::endl;

    // TODO
}

// ### Public methods ###

Controller::Controller()
    : networkManager_{context_,
                      [this](const std::string &packet) {
                          handlePacket(packet);
                      }},
      screenManager_{this} {};

Controller::~Controller() {}

void Controller::run() {
    networkManager_.connect();

    ioThread_ = std::thread([this]() { context_.run(); });

    screenManager_.run();

    // TODO: I think this never gets called
    if (ioThread_.joinable()) {
        ioThread_.join();
    }
}

bool Controller::verifyRegister(const std::string &username,
                                const std::string &password) const {
    // TODO
    return true;
}

bool Controller::verifyLogin(const std::string &username,
                             const std::string &password) const {
    // TODO
    return true;
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

bool Controller::changeProfile(const std::string &username,
                               const std::string &password) const {
    // TODO
    return true;
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
    // TODO:
    return true;
}

bool Controller::removeFriend(const std::string &friendName) const {
    // TODO:
    return true;
}

bool Controller::sendMessage(const std::string &friendName,
                             const std::string &message) const {
    // TODO:
    return true;
}

std::map<std::string, std::vector<Message>> Controller::getMessages() const {
    // TODO: communicate with the server to get the conversations
    // TODO: remove this because it's an example

    std::map<std::string, std::vector<Message>> conversations;
    conversations["friend1"].push_back(Message{1, "message1"});
    conversations["friend2"].push_back(Message{2, "message2"});
    conversations["friend3"].push_back(Message{3, "message3"});
    conversations["friend4"].push_back(Message{4, "message4"});
    conversations["friend5"].push_back(Message{5, "message5"});

    return conversations;
}

std::shared_ptr<std::vector<std::array<std::array<colors, WIDTH>, HEIGHT>>>
Controller::getBoards() const {
    // TODO: communicate with the server to get the boards
    // TODO: remove this because it's an example
    std::vector<std::array<std::array<colors, WIDTH>, HEIGHT>> boards;
    boards.push_back(std::array<std::array<colors, WIDTH>, HEIGHT>());
    return std::make_shared<
        std::vector<std::array<std::array<colors, WIDTH>, HEIGHT>>>(boards);
}

std::vector<std::string> Controller::getFriendsOnline() const {
    // TODO: communicate with the server to get the friends online
    // TODO: remove this because it's an example
    std::vector<std::string> friendsOnline;
    friendsOnline.push_back("friend1");
    friendsOnline.push_back("friend2");
    friendsOnline.push_back("friend3");

    return friendsOnline;
}
