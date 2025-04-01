/**
 * @file controller.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief Controller class header file
 * @date 2025-02-24
 *
 */

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "../../../common/bindings/conversation.hpp"
#include "../../../common/bindings/ranking.hpp"
#include "../../../common/tetris_royal_lib/game_mode/game_mode.hpp"
#include "../../graphics/screen_manager.hpp"
#include "../in_game/game_state/game_state_viewer.hpp"
#include "../in_game/player_state/player_state_external.hpp"
#include "../network/network_manager.hpp"

#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <utility>
#include <vector>

using NameConversation = std::pair<std::string, bindings::Conversation>;

struct Message;

enum class UiChoice {
    GUI,
    TUI,
    NONE,
};

enum class UpdateType {
    FRIENDS_LIST,
    FRIEND_REQUESTS,
    RANKING,
    OTHER,
};

class Controller {
  public:
    enum class AuthState {
        Unauthenticated,
        Authenticated,
        Failed,
    };

    enum class RegistrationState {
        Unregistered,
        Registered,
        Failed,
    };

  private:
    UiChoice uiChoice_;
    std::pair<int, char **> args_;

    boost::asio::io_context context_;
    std::thread ioThread_;

    RegistrationState registrationState_;
    AuthState authState_;

    std::variant<client::GameState, client::GameStateViewer> gameState_;

    size_t currentEffectIdx_;

    mutable std::mutex mutex_;

    std::vector<bindings::User> friendsList_;
    std::unordered_map<UserID, NameConversation> conversationsById_;
    std::vector<std::pair<std::string, Score>> ranking_;
    std::vector<bindings::User> pendingFriendRequests_;

    /*
     * @brief The network manager to manage the connection with the server
     */
    NetworkManager networkManager_;

    /*
     * @brief The screen manager to manage the screens to show to the user
     */
    std::unique_ptr<ScreenManager> screenManager_;

    /**
     * @brief Handles the received packet
     */
    void handlePacket(const std::string_view pack);

    void updateFriendState(const bindings::User &updatedFriend);

  public:
    /*
     * @brief Construct a new Controller object
     */
    Controller(UiChoice uiChoice, std::pair<int, char **> args);

    /*
     * @brief Destroy the Controller object
     */
    ~Controller() = default;

    /**
     * @brief Returns the registration-state.
     */
    RegistrationState getRegistrationState() const;

    /**
     * @brief Returns the authentication-state.
     */
    AuthState getAuthState() const;

    /*
     * @brief Run the controller to manage the game
     *
     * @return The exit code of the program of the tui or gui
     */
    int run();

    /*
     * @brief Makes a registration request to the server.
     *
     * @param username The username of the user
     * @param password The password of the user
     */
    void tryRegister(const std::string &username, const std::string &password);

    /*
     * @brief Makes a login request to the server.
     *
     * @param username The username of the user
     * @param password The password of the user
     */
    void tryLogin(const std::string &username, const std::string &password);

    /*
     * @brief Get the ranking of the players of the Endless mode
     */
    std::vector<std::pair<std::string, Score>> getRanking() const;

    /*
     * @brief Change the profile of the user by changing the username and
     * password
     *
     * @param username The new username of the user
     * @param password The new password of the user
     */
    void changeProfile(const std::string &username,
                       const std::string &password);

    /*
     * @brief Get the friends list of the user
     */
    const std::vector<bindings::User> getFriendsList() const;

    std::vector<bindings::User> getPendingFriendRequests() const;

    /*
     * @brief Add a friend to the friends list of the user
     *
     * @param username The name of the friend to add
     */
    void sendFriendRequest(const std::string &username);

    /*
     * @brief Remove a friend from the friends list of the user
     *
     * @param userID The id of the player to remove.
     */
    void removeFriend(UserID userID);

    /*
     * @brief Send a message to a friend
     *
     * @param recipientId The UserID of the friend to send the message
     * @param message The message to send
     */
    void sendMessage(UserID recipientId, const std::string &message);

    void createGame(GameMode gameMode, size_t targetNumPlayers);

    void joinGame(GameMode gameMode, std::optional<UserID> friendID);

    const NameConversation getConversationWith(UserID userID);

    size_t getNumEffects() const;

    EffectType getEffectType();

    size_t getCurrEffectIdx();

    void selectNextEffect();

    void selectPrevEffect();

    void bigDrop();

    void moveActive(TetrominoMove tetrominoMove);

    void rotateActive(bool clockwise);

    void selectTarget(UserID userId);

    void emptyPenaltyStash();

    void holdNextTetromino();

    void buyEffect(EffectType effectType, bool stashForLater = false);

    void quitGame();

    void handleKeypress(const std::string &pressedKey);

    void acceptFriendRequest(UserID userId);

    void declineFriendRequest(UserID userId);

    std::variant<client::GameState, client::GameStateViewer> getGameState();

    bool inGame() const;
};

#endif // CONTROLLER_HPP
