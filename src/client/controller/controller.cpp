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
#include <mutex>

// ### Private methods ###

void Controller::handlePacket(const std::string &pack) {
    std::cerr << "called with " << pack << std::endl;

    mutex_.lock();
    if (pack == "connected" || pack == "authenticated") {
        authState_ = Controller::AuthState::Authenticated;
    } else if (pack == "disconnected" || pack == "unauthenticated") {
        authState_ = Controller::AuthState::Unauthenticated;
    } else if (pack == "registered") {
        registrationState_ = Controller::RegistrationState::Registered;
    } else if (pack == "unregistered") {
        registrationState_ = Controller::RegistrationState::Unregistered;
    }
    mutex_.unlock();
}

// ### Public methods ###

Controller::Controller()
    : registrationState_{Controller::RegistrationState::Unregistered},
      authState_{Controller::AuthState::Unauthenticated},
      networkManager_{
          context_,
          [this](const std::string &packet) { handlePacket(packet); }},
      screenManager_{this} {};

Controller::~Controller() {
    // TODO: join the iothread
}

Controller::RegistrationState Controller::getRegistrationState() const {
    return registrationState_;
}

Controller::AuthState Controller::getAuthState() const { return authState_; }

void Controller::run() {
    networkManager_.connect();

    ioThread_ = std::thread([this]() { context_.run(); });

    screenManager_.run();

    std::cerr << "before join" << std::endl;

    context_.stop();
    if (ioThread_.joinable()) {
        std::cerr << "joining" << std::endl;
        ioThread_.join();
    }

    std::cerr << "after joining" << std::endl;
}

void Controller::tryRegister(const std::string &username,
                             const std::string &password) {
    // TODO

    // create some json here and send it
    networkManager_.send("trying to register");
}

void Controller::tryLogin(const std::string &username,
                          const std::string &password) { // TODO

    // TODO

    // create some json here and send it
    networkManager_.send("trying to login");
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
