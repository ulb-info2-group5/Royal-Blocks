#include "controller.hpp"

#include "../in_game/player_state/player_state_external.hpp"
#include "../network/network_manager.hpp"

#include "../../../common/bindings/abort_matchmaking.hpp"
#include "../../../common/bindings/authentication.hpp"
#include "../../../common/bindings/authentication_response.hpp"
#include "../../../common/bindings/change_password.hpp"
#include "../../../common/bindings/change_username.hpp"
#include "../../../common/bindings/conversations.hpp"
#include "../../../common/bindings/create_game.hpp"
#include "../../../common/bindings/friend_request.hpp"
#include "../../../common/bindings/friends_list.hpp"
#include "../../../common/bindings/handle_friend_request.hpp"
#include "../../../common/bindings/in_game/big_drop.hpp"
#include "../../../common/bindings/in_game/buy_bonus.hpp"
#include "../../../common/bindings/in_game/buy_penalty.hpp"
#include "../../../common/bindings/in_game/empty_penalty_stash.hpp"
#include "../../../common/bindings/in_game/game_state_client.hpp"
#include "../../../common/bindings/in_game/hold_active_tetromino.hpp"
#include "../../../common/bindings/in_game/move_active.hpp"
#include "../../../common/bindings/in_game/quit_game.hpp"
#include "../../../common/bindings/in_game/rotate_active.hpp"
#include "../../../common/bindings/join_game.hpp"
#include "../../../common/bindings/message.hpp"
#include "../../../common/bindings/pending_friend_requests.hpp"
#include "../../../common/bindings/registration.hpp"
#include "../../../common/bindings/registration_response.hpp"
#include "../../../common/bindings/remove_friend.hpp"
#include "../../../common/bindings/view_game.hpp"
#include "../../../common/tetris_lib/tetromino/abstract_tetromino.hpp"
#include "../../../common/tetris_royal_lib/effect_price/effect_price.hpp"
#include "../../../common/tetris_royal_lib/game_mode/game_mode.hpp"
#include "../../../common/tetris_royal_lib/player_state/player_state.hpp"
#include "../../core/in_game/game_state/game_state.hpp"
#include "../../graphics/common/abstract_display.hpp"
#include "core/server_info/server_info.hpp"

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <memory>
#include <mutex>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>
#include <thread>
#include <variant>
#include <vector>

// ### Private methods ###

void Controller::updateFriendState(const bindings::User &updatedFriend) {
    auto it = std::find_if(friendsList_.begin(), friendsList_.end(),
                           [&](const bindings::User &u) {
                               return u.userID == updatedFriend.userID;
                           });

    if (it != friendsList_.end()) {
        *it = updatedFriend;
    } else {
        friendsList_.push_back(updatedFriend);
    }
}

void Controller::handlePacket(const std::string_view pack) {
    nlohmann::json j = nlohmann::json::parse(pack);

    std::lock_guard<std::mutex> guard(mutex_);

    UpdateType updateType = UpdateType::OTHER;

    switch (static_cast<bindings::BindingType>(j.at(bindings::PACKET_TYPE_FIELD))) {
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
        friendsList_ = bindings::FriendsList::from_json(j).friendsList;
        updateType = UpdateType::FRIENDS_LIST;
        break;
    }

    case bindings::BindingType::Conversations: {
        conversationsById_ =
            bindings::Conversations::from_json(j).conversationsById;
        updateType = UpdateType::CONVERSATIONS;
        break;
    }

    case bindings::BindingType::User: {
        bindings::User updatedFriend = bindings::User::from_json(j);
        updateFriendState(updatedFriend);
        break;
    }

    case bindings::BindingType::PendingFriendRequests: {
        pendingFriendRequests_ =
            bindings::PendingFriendRequests::from_json(j).requests;
        updateType = UpdateType::FRIEND_REQUESTS;
        break;
    }

    case bindings::BindingType::GameState: {
        gameState_ = bindings::GameStateMessage::deserializeForPlayer(j);
        updateType = UpdateType::GAME_STATE;
        break;
    }

    case bindings::BindingType::GameStateViewer: {
        gameState_ = bindings::GameStateMessage::deserializeForViewer(j);
        updateType = UpdateType::GAME_STATE;
        break;
    }

    case bindings::BindingType::Ranking: {
        ranking_ = bindings::Ranking::from_json(j).ranking;
        updateType = UpdateType::RANKING;
        break;
    }

    default:
        std::cerr << "unknown bindingType " << j.at(bindings::PACKET_TYPE_FIELD) << std::endl;
    }

    pAbstractDisplay_->forceRefresh(updateType);
}

// ### Public methods ###

Controller::Controller(std::unique_ptr<AbstractDisplay> &&pAbstractDisplay)
    : registrationState_{Controller::RegistrationState::Unregistered},
      authState_{Controller::AuthState::Unauthenticated}, gameState_{},
      pAbstractDisplay_(std::move(pAbstractDisplay)),
      networkManager_{context_, [this](const std::string_view packet) {
                          handlePacket(packet);
                      }} {};

Controller::RegistrationState Controller::getRegistrationState() const {
    std::lock_guard<std::mutex> guard(mutex_);
    return registrationState_;
}

Controller::AuthState Controller::getAuthState() const {
    std::lock_guard<std::mutex> guard(mutex_);
    return authState_;
}

void Controller::run() {
    // load initial serverInfo
    serverInfo_ = config::loadServerInfo();
    networkManager_.start(serverInfo_);

    std::thread ioThread([&]() { context_.run(); });

    pAbstractDisplay_->run(*this);

    networkManager_.disconnect();

    context_.stop();

    if (ioThread.joinable()) {
        ioThread.join();
    }
}

const std::string_view Controller::getServerIp() const {
    return serverInfo_.ip;
}

uint16_t Controller::getServerPort() const { return serverInfo_.port; }

bool Controller::isConnected() const { return networkManager_.isConnected(); }

void Controller::setServerInfo(const config::ServerInfo &serverInfo) {
    serverInfo_ = serverInfo;
    networkManager_.setServerInfo(serverInfo_);
    config::saveServerInfo(serverInfo);
}

config::ServerInfo Controller::getServerInfo() const { return serverInfo_; }

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

std::vector<std::pair<std::string, Score>> Controller::getRanking() const {
    std::lock_guard<std::mutex> guard(mutex_);
    return ranking_;
}

void Controller::changeProfile(const std::string &username,
                               const std::string &password) {
    networkManager_.send(bindings::ChangeUsername{username}.to_json().dump());
    networkManager_.send(bindings::ChangePassword{password}.to_json().dump());
}

const std::vector<bindings::User> Controller::getFriendsList() const {
    std::lock_guard<std::mutex> guard(mutex_);
    return friendsList_;
}

std::vector<bindings::User> Controller::getPendingFriendRequests() const {
    std::lock_guard<std::mutex> guard(mutex_);
    return pendingFriendRequests_;
}

void Controller::sendFriendRequest(const std::string &username) {
    networkManager_.send(bindings::FriendRequest{username}.to_json().dump());
}

void Controller::removeFriend(UserID userID) {
    networkManager_.send(bindings::RemoveFriend{userID}.to_json().dump());
}

void Controller::sendMessage(UserID recipientId, const std::string &message) {
    networkManager_.send(
        bindings::Message{recipientId, message}.to_json().dump());
}

const NameConversation Controller::getConversationWith(UserID userID) {
    std::lock_guard<std::mutex> guard(mutex_);
    if (!conversationsById_.contains(userID)) {
        conversationsById_[userID] = {};
    }

    return conversationsById_.at(userID);
}

void Controller::createGame(GameMode gameMode, size_t targetNumPlayers) {
    networkManager_.send(
        bindings::CreateGame{gameMode, targetNumPlayers}.to_json().dump());
    if (gameMode == GameMode::RoyalCompetition) currentEffectIdx_ = 0;
}

void Controller::joinGame(GameMode gameMode, std::optional<UserID> friendID) {
    networkManager_.send(
        bindings::JoinGame{gameMode, friendID}.to_json().dump());
    if (gameMode == GameMode::RoyalCompetition) currentEffectIdx_ = 0;
}

void Controller::joinGameAsViewer(UserID targetId) {
    networkManager_.send(bindings::ViewGame{targetId}.to_json().dump());
}

void Controller::bigDrop() {
    networkManager_.send(bindings::BigDrop{}.to_json().dump());
}

void Controller::moveActive(TetrominoMove tetrominoMove) {
    networkManager_.send(bindings::MoveActive{tetrominoMove}.to_json().dump());
}

void Controller::rotateActive(bool clockwise) {
    networkManager_.send(bindings::RotateActive{clockwise}.to_json().dump());
}

void Controller::emptyPenaltyStash() {
    networkManager_.send(bindings::EmptyPenaltyStash{}.to_json().dump());
}

void Controller::holdActiveTetromino() {
    networkManager_.send(bindings::HoldActiveTetromino{}.to_json().dump());
}

void Controller::selectTarget(UserID userId) {
    networkManager_.send(bindings::SelectTarget{userId}.to_json().dump());
}

void Controller::buyEffect(EffectType effectType, bool stashForLater) {
    std::visit(
        [this, stashForLater](auto &&effectType) {
            using T = std::decay_t<decltype(effectType)>;
            if constexpr (std::is_same_v<T, BonusType>) {
                networkManager_.send(
                    bindings::BuyBonus{effectType}.to_json().dump());
            } else if constexpr (std::is_same_v<T, PenaltyType>) {
                networkManager_.send(
                    bindings::BuyPenalty{effectType, stashForLater}
                        .to_json()
                        .dump());
            }
        },
        effectType);
}

void Controller::quitGame() {
    networkManager_.send(bindings::QuitGame{}.to_json().dump());
    std::visit(
        [](auto &gameState) {
            using T = std::decay_t<decltype(gameState)>;
            if constexpr (std::is_same_v<T, client::GameState>) {
                gameState.self.playerState.isAlive = false;
            }

            gameState.isFinished = true;
        },
        gameState_);
}

void Controller::handleKeyPress(const std::string &pressedKey) {
    if (pressedKey == "q") {
        quitGame();
    } else if (pressedKey == "ArrowLeft") {
        networkManager_.send(
            bindings::MoveActive{TetrominoMove::Left}.to_json().dump());
    } else if (pressedKey == "ArrowRight") {
        networkManager_.send(
            bindings::MoveActive{TetrominoMove::Right}.to_json().dump());
    } else if (pressedKey == "Space") {
        networkManager_.send(bindings::BigDrop{}.to_json().dump());
    } else if (pressedKey == "ArrowDown") {
        networkManager_.send(
            bindings::MoveActive{TetrominoMove::Down}.to_json().dump());
    } else if (pressedKey == "f") {
        networkManager_.send(bindings::RotateActive{false}.to_json().dump());
    } else if (pressedKey == "h") {
        networkManager_.send(bindings::HoldActiveTetromino{}.to_json().dump());
    } else if (pressedKey == "g") {
        networkManager_.send(bindings::RotateActive{true}.to_json().dump());
    } else if (pressedKey == "e") {
        selectPrevEffect();
    } else if (pressedKey == "r") {
        selectNextEffect();
    } else if (pressedKey == "t") {
        emptyPenaltyStash();
    } else if (pressedKey == "y") {
        buyEffect(getSelectedEffectType());
    } else if (pressedKey == "u") {
        buyEffect(getSelectedEffectType(), true);
    }
}

size_t Controller::getNumEffects() const {
    std::lock_guard<std::mutex> guard(mutex_);
    return std::visit(
        [](const auto &gameState) { return gameState.effectsPrice.size(); },
        gameState_);
}

EffectType Controller::getSelectedEffectType() const {
    std::lock_guard<std::mutex> guard(mutex_);
    return std::visit(
        [this](const auto &gameState) {
            return gameState.effectsPrice.at(currentEffectIdx_).first;
        },
        gameState_);
}

void Controller::setSelectedEffectType(EffectType effectType) {
    std::lock_guard<std::mutex> guard(mutex_);
    std::visit(
        [this, effectType](const auto &gameState) {
            auto &effectsPrice = gameState.effectsPrice;

            auto it = std::find_if(
                effectsPrice.begin(), effectsPrice.end(),
                [effectType](auto &pair) { return pair.first == effectType; });

            if (it != effectsPrice.end()) {
                size_t dist = std::distance(effectsPrice.begin(), it);

                currentEffectIdx_ = dist;
            }
        },
        gameState_);
}

void Controller::selectNextEffect() {
    currentEffectIdx_ = (currentEffectIdx_ + 1) % getNumEffects();
}

void Controller::selectPrevEffect() {
    currentEffectIdx_ =
        (currentEffectIdx_ - 1 + getNumEffects()) % getNumEffects();
}

void Controller::acceptFriendRequest(UserID userId) {
    networkManager_.send(bindings::HandleFriendRequest{
        userId, bindings::HandleFriendRequest::Action::Accept}
                             .to_json()
                             .dump());
}

void Controller::declineFriendRequest(UserID userId) {
    networkManager_.send(bindings::HandleFriendRequest{
        userId, bindings::HandleFriendRequest::Action::Decline}
                             .to_json()
                             .dump());
}

void Controller::abortMatchmaking() {
    networkManager_.send(bindings::AbortMatchMaking{}.to_json().dump());
}

std::variant<client::GameState, client::GameStateViewer>
Controller::getGameState() {
    std::lock_guard<std::mutex> guard(mutex_);
    return gameState_;
}

bool Controller::inGame() const {
    return !std::visit(
        [](const auto &gameState) { return gameState.isFinished; }, gameState_);
}

size_t Controller::getCurrEffectIdx() const { return currentEffectIdx_; }
