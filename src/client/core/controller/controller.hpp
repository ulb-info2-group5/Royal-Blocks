#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "../../../common/bindings/conversation.hpp"
#include "../../../common/bindings/ranking.hpp"
#include "../../../common/tetris_royal_lib/game_mode/game_mode.hpp"
#include "../../graphics/common/abstract_display.hpp"
#include "../in_game/game_state/game_state.hpp"
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

/**
 * @brief Controller/driver of the client program.
 *
 * @note Uses NetworkManager to receive/send packets.
 * Stores and keeps up to date the data which gets displayed.
 *
 * @note Controls the keybinds to make the keybindings the same between both TUI
 * and GUI.
 *
 * @note Handles the selected effect index (used for keybinding effect
 * selection).
 */
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
    boost::asio::io_context context_;
    std::thread ioThread_;

    RegistrationState registrationState_;
    AuthState authState_;

    std::variant<client::GameState, client::GameStateViewer> gameState_;

    std::shared_ptr<AbstractDisplay> pAbstractDisplay_;

    size_t currentEffectIdx_;

    mutable std::mutex mutex_;

    std::vector<bindings::User> friendsList_;
    std::unordered_map<UserID, NameConversation> conversationsById_;
    std::vector<std::pair<std::string, Score>> ranking_;
    std::vector<bindings::User> pendingFriendRequests_;

    /**
     * @brief The network manager to manage the connection with the server
     */
    NetworkManager networkManager_;

    /**
     * @brief Handles the received packet
     */
    void handlePacket(const std::string_view pack);

    void updateFriendState(const bindings::User &updatedFriend);

  public:
    /**
     * @brief Construct a new Controller object
     */
    Controller(std::unique_ptr<AbstractDisplay> &&pAbstractDisplay);

    /**
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

    /**
     * @brief Run the controller to manage the game
     */
    void run();

    /**
     * @brief Makes a registration request to the server.
     *
     * @param username The username of the user
     * @param password The password of the user
     */
    void tryRegister(const std::string &username, const std::string &password);

    /**
     * @brief Makes a login request to the server.
     *
     * @param username The username of the user
     * @param password The password of the user
     */
    void tryLogin(const std::string &username, const std::string &password);

    /**
     * @brief Get the ranking of the players of the Endless mode
     */
    std::vector<std::pair<std::string, Score>> getRanking() const;

    /**
     * @brief Change the profile of the user by changing the username and
     * password
     *
     * @param username The new username of the user
     * @param password The new password of the user
     */
    void changeProfile(const std::string &username,
                       const std::string &password);

    /**
     * @brief Get the friends list of the user
     */
    const std::vector<bindings::User> getFriendsList() const;

    /**
     * @brief Returns the pending friend-requests as a vector of users.
     */
    std::vector<bindings::User> getPendingFriendRequests() const;

    /**
     * @brief Add a friend to the friends list of the user
     *
     * @param username The name of the friend to add
     */
    void sendFriendRequest(const std::string &username);

    /**
     * @brief Remove a friend from the friends list of the user
     *
     * @param userID The id of the player to remove.
     */
    void removeFriend(UserID userID);

    /**
     * @brief Send a message to a friend
     *
     * @param recipientId The UserID of the friend to send the message
     * @param message The message to send
     */
    void sendMessage(UserID recipientId, const std::string &message);

    /**
     * @brief Creates a new game in the given game-mode and with the given
     * number of players.
     */
    void createGame(GameMode gameMode, size_t targetNumPlayers);

    /**
     * @brief Joins a game in the given GameMode (optionally join a friend if
     * one specified).
     */
    void joinGame(GameMode gameMode, std::optional<UserID> friendID);

    /**
     * @brief Joins the game that the specified user is playing as a viewer.
     */
    void joinGameAsViewer(UserID targetId);

    /**
     * @brief Returns the name and conversation history with the specified user.
     */
    const NameConversation getConversationWith(UserID userID);

    /**
     * @brief Returns the number of effects in the GameState.
     */
    size_t getNumEffects() const;

    /**
     * @brief Returns the selected effect-type.
     */
    EffectType getSelectedEffectType() const;

    /**
     * @brief Sets the selected effect-type to the given effect-type
     */
    void setSelectedEffectType(EffectType effectType);

    /**
     * @brief Returns the index of the currently selected effect.
     */
    size_t getCurrEffectIdx() const;

    /**
     * @brief Selects the next effect.
     */
    void selectNextEffect();

    /**
     * @brief Selects the previous effect.
     */
    void selectPrevEffect();

    /**
     * @brief BigDrop action.
     * @see Tetris for description.
     */
    void bigDrop();

    /**
     * @brief Moves the active tetromino.
     * @see Tetris for description.
     */
    void moveActive(TetrominoMove tetrominoMove);

    /**
     * @brief Rotates the active tetromino.
     * @see Tetris for description.
     */
    void rotateActive(bool clockwise);

    /**
     * @brief Selects the given user ass target.
     */
    void selectTarget(UserID userId);

    /**
     * @brief Empties the penalty stash on the selected target.
     */
    void emptyPenaltyStash();

    /**
     * @brief Holds the active tetromino.
     */
    void holdNextTetromino();

    /**
     * @brief Buys the given effect (stashes if stashForLater).
     */
    void buyEffect(EffectType effectType, bool stashForLater = false);

    /**
     * @brief Quits the game.
     */
    void quitGame();

    /**
     * @brief Handles the given key.
     */
    void handleKeyPress(const std::string &pressedKey);

    /**
     * @brief Accepts the friend request from userID.
     */
    void acceptFriendRequest(UserID userId);

    /**
     * @brief Decline the friend request from userID.
     */
    void declineFriendRequest(UserID userId);

    /**
     * @brief Aborts the matchmaking process.
     */
    void abortMatchmaking();

    /**
     * @brief Returns a copy of the GameState.
     */
    std::variant<client::GameState, client::GameStateViewer> getGameState();

    /**
     * @brief Returns true if the gamestate indicates that the game is not
     * finished yet.
     */
    bool inGame() const;
};

#endif // CONTROLLER_HPP
