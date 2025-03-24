/**
 * @file controller.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Controller class definition file
 * @date 2025-02-24
 *
 */

#include "controller.hpp"
#include "../../graphics/screen_manager.hpp"
#include "..//in_game/player_state/player_state_external.hpp"
#include "../network/network_manager.hpp"

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
#include "../../../common/bindings/in_game/hold_next_tetromino.hpp"
#include "../../../common/bindings/in_game/move_active.hpp"
#include "../../../common/bindings/in_game/quit_game.hpp"
#include "../../../common/bindings/in_game/rotate_active.hpp"
#include "../../../common/bindings/join_game.hpp"
#include "../../../common/bindings/message.hpp"
#include "../../../common/bindings/pending_friend_requests.hpp"
#include "../../../common/bindings/registration.hpp"
#include "../../../common/bindings/registration_response.hpp"
#include "../../../common/bindings/remove_friend.hpp"
#include "../../../common/tetris_lib/tetromino/tetromino.hpp"
#include "../../../common/tetris_royal_lib/player_state/player_state.hpp"
#include "core/in_game/game_state/game_state.hpp"
#include "game_mode/game_mode.hpp"

#include <mutex>
#include <optional>
#include <string>
#include <thread>
#include <vector>

// ### Private methods ###

void Controller::handlePacket(const std::string_view pack) {
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

    case bindings::BindingType::PendingFriendRequests: {
        pendingFriendRequests_ =
            bindings::PendingFriendRequests::from_json(j).requests;
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

        // TODO: remove this as it is not useful anymore now that we have the
        // isFinished flag in GameState
        //
        // case bindings::BindingType::GameOver: {
        //     gameState_ = std::nullopt;
        //     break;
        // }

    default:
        std::cerr << "unknown bindingType" << std::endl;
    }

    screenManager_->forceRefresh();
}

// ### Public methods ###

Controller::Controller(UiChoice uiChoice, std::tuple<int, char **> args)
    : uiChoice_(uiChoice), args_(args),
      registrationState_{Controller::RegistrationState::Unregistered},
      authState_{Controller::AuthState::Unauthenticated}, gameState_{},
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

int Controller::run() {
    if (!networkManager_.connect()) {
        std::cerr << "Failed to connect to server" << std::endl;
        return -1; // We failed to connect to the server so we can't do anything
                   // so we end the program
    };

    screenManager_ = std::make_unique<ScreenManager>(*this, uiChoice_, args_);

    ioThread_ = std::thread([this]() { context_.run(); });

    int result = screenManager_->run();

    context_.stop();
    if (ioThread_.joinable()) {
        ioThread_.join();
    }

    return result;
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

void Controller::buyEffect(EffectType effectType, bool stashForLater) {

    std::visit(
        [this, stashForLater](auto &&effectType) {
            using T = std::decay_t<decltype(effectType)>;
            if constexpr (std::is_same_v<T, BonusType>) {
                std::cerr << "buying effect : " << effectType << std::endl;
                networkManager_.send(
                    bindings::BuyBonus{effectType}.to_json().dump());
            } else if constexpr (std::is_same_v<T, PenaltyType>) {
                std::cerr << "buying effect : " << effectType << std::endl;
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
    } else if (pressedKey == "Space") {
        networkManager_.send(bindings::BigDrop{}.to_json().dump());
    } else if (pressedKey == "ArrowDown") {
        networkManager_.send(
            bindings::MoveActive{TetrominoMove::Down}.to_json().dump());
    } else if (pressedKey == "f") {
        networkManager_.send(bindings::RotateActive{false}.to_json().dump());
    } else if (pressedKey == "g") {
        networkManager_.send(bindings::RotateActive{true}.to_json().dump());
    }
}

size_t Controller::getNumEffects() const {
    std::lock_guard<std::mutex> guard(mutex_);
    return gameState_.effectsPrice.size();
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

client::GameState Controller::getGameState() {
    std::lock_guard<std::mutex> guard(mutex_);
    return gameState_;
}

bool Controller::inGame() const { return !gameState_.isFinished; }
