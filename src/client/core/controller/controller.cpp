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
#include "game_mode/game_mode.hpp"
#include "game_state/game_state.hpp"

#include "../../common/bindings/authentication.hpp"
#include "../../common/bindings/authentication_response.hpp"
#include "../../common/bindings/change_password.hpp"
#include "../../common/bindings/change_username.hpp"
#include "../../common/bindings/create_game.hpp"
#include "../../common/bindings/friend_request.hpp"
#include "../../common/bindings/in_game/big_drop.hpp"
#include "../../common/bindings/in_game/empty_penalty_stash.hpp"
#include "../../common/bindings/in_game/game_state_client.hpp"
#include "../../common/bindings/in_game/hold_next_tetromino.hpp"
#include "../../common/bindings/in_game/move_active.hpp"
#include "../../common/bindings/in_game/quit_game.hpp"
#include "../../common/bindings/in_game/rotate_active.hpp"
#include "../../common/bindings/join_game.hpp"
#include "../../common/bindings/message.hpp"
#include "../../common/bindings/registration.hpp"
#include "../../common/bindings/registration_response.hpp"
#include "../../common/bindings/remove_friend.hpp"
#include "player_state/player_state.hpp"
#include "tetromino/tetromino.hpp"

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
        friendsList_ = bindings::FriendsList::from_json(j).friendsList;
        break;
    }

    case bindings::BindingType::Conversations: {
        conversationsById_ =
            bindings::Conversations::from_json(j).conversationsById;
        break;
    }

    case bindings::BindingType::GameState: {
        gameState_ = bindings::GameStateMessage::deserialize(j);
        break;
    }

    case bindings::BindingType::Ranking: {
        ranking_ = bindings::Ranking::from_json(j).ranking;
        break;
    }

    default:
        std::cerr << "unknown bindingType" << std::endl;
    }

    screenManager_.forceRefresh();
}

// ### Public methods ###

Controller::Controller()
    : registrationState_{Controller::RegistrationState::Unregistered},
      authState_{Controller::AuthState::Unauthenticated},
      gameState_(std::nullopt),
      networkManager_{
          context_,
          [this](const std::string &packet) { handlePacket(packet); }},
      screenManager_{*this} {};

Controller::~Controller() {
    // TODO: join the iothread
}

Controller::RegistrationState Controller::getRegistrationState() const {
    std::lock_guard<std::mutex> guard(mutex_);
    return registrationState_;
}

Controller::AuthState Controller::getAuthState() const {
    std::lock_guard<std::mutex> guard(mutex_);
    return authState_;
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

const std::vector<std::pair<std::string, Score>> &
Controller::getRanking() const {
    std::lock_guard<std::mutex> guard(mutex_);
    return ranking_;
}

void Controller::changeProfile(const std::string &username,
                               const std::string &password) {
    networkManager_.send(bindings::ChangeUsername{username}.to_json().dump());
    networkManager_.send(bindings::ChangePassword{password}.to_json().dump());
}

const std::vector<bindings::User> &Controller::getFriendsList() const {
    std::lock_guard<std::mutex> guard(mutex_);
    return friendsList_;
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

const NameConversation &Controller::getConversationWith(UserID userID) {
    std::lock_guard<std::mutex> guard(mutex_);
    if (!conversationsById_.contains(userID)) {
        conversationsById_[userID] = {};
    }

    return conversationsById_.at(userID);
}

void Controller::createGame(GameMode gameMode, size_t targetNumPlayers) {
    networkManager_.send(
        bindings::CreateGame{gameMode, targetNumPlayers}.to_json().dump());
}

void Controller::joinGame(GameMode gameMode, std::optional<UserID> friendID) {
    networkManager_.send(
        bindings::JoinGame{gameMode, friendID}.to_json().dump());
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

void Controller::holdNextTetromino() {
    networkManager_.send(bindings::HoldNextTetromino{}.to_json().dump());
}

void Controller::quitGame() {
    networkManager_.send(bindings::QuitGame{}.to_json().dump());
}

void Controller::handleKeypress(const std::string &pressedKey) {
    if (pressedKey == "q") {
        quitGame();
    } else if (pressedKey == "ArrowLeft") {
        networkManager_.send(
            bindings::MoveActive{TetrominoMove::Left}.to_json().dump());
    } else if (pressedKey == "ArrowRight") {
        networkManager_.send(
            bindings::MoveActive{TetrominoMove::Right}.to_json().dump());
    } else if (pressedKey == "ArrowUp") {
        networkManager_.send(bindings::BigDrop{}.to_json().dump());
    } else if (pressedKey == "ArrowDown") {
        networkManager_.send(
            bindings::MoveActive{TetrominoMove::Down}.to_json().dump());
    }
}

Score Controller::getSelfScore() const {
    std::lock_guard<std::mutex> guard(mutex_);
    return gameState_->self.playerState_.score_;
}

Score Controller::getSelfEnergy() const {
    std::lock_guard<std::mutex> guard(mutex_);
    return gameState_->self.playerState_.energy_.value_or(0);
}

GameMode Controller::getGameMode() const {
    std::lock_guard<std::mutex> guard(mutex_);
    return gameState_->gameMode;
}

std::optional<std::pair<unsigned, Controller::SelfCellType>>
Controller::selfCellInfoAt(int x, int y) const {
    std::lock_guard<std::mutex> guard(mutex_);

    if (gameState_->self.tetris_.board_.get(x, y).getColorId().has_value()) {
        return std::make_pair(
            gameState_->self.tetris_.board_.get(x, y).getColorId().value(),
            Controller::SelfCellType::Placed);
    }

    auto &activeTetromino = gameState_->self.tetris_.activeTetromino_;
    if (activeTetromino.has_value()) {
        for (auto &vec : activeTetromino->body_) {
            if (activeTetromino->anchorPoint_ + vec == Vec2{x, y}) {
                return std::make_optional(
                    std::make_pair(activeTetromino->colorId,
                                   Controller::SelfCellType::Active));
            }
        }
    }

    auto &previewTetromino = gameState_->self.tetris_.previewTetromino_;
    if (previewTetromino.has_value()) {
        for (auto &vec : previewTetromino->body_) {
            if (previewTetromino->anchorPoint_ + vec == Vec2{x, y}) {
                return std::make_optional(
                    std::make_pair(previewTetromino->colorId,
                                   Controller::SelfCellType::Preview));
            }
        }
    }

    return std::nullopt;
}

std::optional<unsigned>
Controller::opponentsBoardGetColorIdAt(size_t opponentIdx, int x, int y) const {
    std::lock_guard<std::mutex> guard(mutex_);
    return gameState_->externals.at(opponentIdx)
        .tetris_.board_.get(x, y)
        .getColorId();
}

size_t Controller::getNumOpponents() const {
    std::lock_guard<std::mutex> guard(mutex_);
    return gameState_->externals.size();
}

bool Controller::gameHasStarted() const {
    std::lock_guard<std::mutex> guard(mutex_);
    return gameState_.has_value();
}
