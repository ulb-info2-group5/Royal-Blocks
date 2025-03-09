/**
 * @file controller.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Controller class definition file
 * @date 2025-02-24
 *
 */

#include "controller.hpp"
#include "../../graphics/TUI/screen_manager.hpp"
#include "../network/network_manager.hpp"
#include "core/in_game/player_state/player_state_external.hpp"
#include "game_state/game_state.hpp"

#include "../../common/bindings/authentication.hpp"
#include "../../common/bindings/authentication_response.hpp"
#include "../../common/bindings/friend_request.hpp"
#include "../../common/bindings/in_game/game_state_client.hpp"
#include "../../common/bindings/message.hpp"
#include "../../common/bindings/registration.hpp"
#include "../../common/bindings/registration_response.hpp"
#include "player_state/player_state.hpp"

#include <algorithm>
#include <mutex>
#include <optional>
#include <string>
#include <thread>
#include <vector>

// ### Private methods ###

void Controller::handlePacket(const std::string &pack) {
    nlohmann::json j = nlohmann::json::parse(pack);

    std::lock_guard<std::mutex> guard(mutex_);

    switch (static_cast<bindings::BindingType>(j.at("type"))) {
    case bindings::BindingType::AuthenticationResponse: {
        bool success = bindings::AuthenticationResponse::from_json(j).success;
        authState_ = success ? Controller::AuthState::Authenticated
                             : Controller::AuthState::Unauthenticated;
        break;
    }

    case bindings::BindingType::RegistrationResponse: {
        bool success = bindings::RegistrationResponse::from_json(j).success;
        registrationState_ = success
                                 ? Controller::RegistrationState::Registered
                                 : Controller::RegistrationState::Unregistered;
        break;
    }

    case bindings::BindingType::FriendsList: {
        friendsList_ = bindings::FriendsList::from_json(j);
        break;
    }

    case bindings::BindingType::Conversations: {
        conversations_ = bindings::Conversations::from_json(j);
        break;
    }

    case bindings::BindingType::GameState: {
        std::lock_guard<std::mutex> guard(pGameState_->mutex);
        pGameState_->gameState = bindings::GameStateMessage::deserialize(j);
        break;
    }

    case bindings::BindingType::Ranking: {
        ranking_ = bindings::Ranking::from_json(j);
        break;
    }

    default:
        std::cerr << "unknown bindingType" << std::endl;
    }
}

// ### Public methods ###

Controller::Controller()
    : registrationState_{Controller::RegistrationState::Unregistered},
      authState_{Controller::AuthState::Unauthenticated},
      pGameState_{std::make_shared<client::GameStateWrapper>()},
      networkManager_{
          context_,
          [this](const std::string &packet) { handlePacket(packet); }},

      screenManager_{*this}

{

    // ---------------------------------
    // TODO: remove this
    GameState gameState{GameMode::Endless, {PlayerState{0}}};

    pGameState_->gameState.deserialize(gameState.serializeFor(0));
    // ---------------------------------
};

Controller::~Controller() {
    // TODO: join the iothread
}

Controller::RegistrationState Controller::getRegistrationState() const {
    return registrationState_;
}

Controller::AuthState Controller::getAuthState() const { return authState_; }

std::shared_ptr<client::GameStateWrapper> &Controller::getGameState() {
    return pGameState_;
}

void Controller::run() {
    networkManager_.connect();

    ioThread_ = std::thread([this]() { context_.run(); });

    screenManager_.run();

    context_.stop();
    if (ioThread_.joinable()) {
        ioThread_.join();
    }
}

void Controller::tryRegister(const std::string &username,
                             const std::string &password) {
    networkManager_.send(
        bindings::Registration{username, password}.to_json().dump());
}

void Controller::tryLogin(const std::string &username,
                          const std::string &password) {
    networkManager_.send(
        bindings::Authentication{username, password}.to_json().dump());
}

const bindings::Ranking &Controller::getRanking() const { return ranking_; }

void Controller::changeProfile(const std::string &username,
                               const std::string &password) const {
    // TODO
}

const bindings::FriendsList &Controller::getFriendsList() const {
    return friendsList_;
}

void Controller::sendFriendRequest(const std::string &username) {
    networkManager_.send(bindings::FriendRequest{
        username, bindings::FriendRequest::FriendRequestType::Add}
                             .to_json()
                             .dump());
}

void Controller::removeFriend(const std::string &username) {
    networkManager_.send(bindings::FriendRequest{
        username, bindings::FriendRequest::FriendRequestType::Remove}
                             .to_json()
                             .dump());
}

void Controller::sendMessage(PlayerID recipientId, const std::string &message) {
    networkManager_.send(
        bindings::Message{recipientId, message}.to_json().dump());
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

// std::shared_ptr<std::vector<std::array<std::array<Color, WIDTH>,
// HEIGHT>>> Controller::getBoards() const {
//     // TODO: communicate with the server to get the boards
//     // TODO: remove this because it's an example
//     std::vector<std::array<std::array<Color, WIDTH>, HEIGHT>> boards;
//     boards.push_back(std::array<std::array<Color, WIDTH>, HEIGHT>());
//     return std::make_shared<
//         std::vector<std::array<std::array<Color, WIDTH>,
//         HEIGHT>>>(boards);
// }

const NameConversation &Controller::getConversationWith(PlayerID playerID) {
    if (!conversations_.conversationsById.contains(playerID)) {
        conversations_.conversationsById[playerID] = {};
    }

    return conversations_.conversationsById.at(playerID);
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
