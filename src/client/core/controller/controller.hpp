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
#include "../../../common/tetris_royal_lib//game_mode/game_mode.hpp"
#include "../../graphics/TUI/screen_manager.hpp"
#include "../in_game/game_state/game_state.hpp"
#include "../in_game/player_state/player_state_external.hpp"
#include "../network/network_manager.hpp"

#include <mutex>
#include <optional>
#include <string>
#include <utility>
#include <vector>

using NameConversation = std::pair<std::string, bindings::Conversation>;

struct Message;

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

    // Returned by selfCellInfoAt.
    // Tells us whether the cell at (x,y) is the part of the active or preview
    // or a placed Tetromino.
    enum class SelfCellType {
        Active,
        Preview,
        Placed,
    };

  private:
    boost::asio::io_context context_;
    std::thread ioThread_;

    RegistrationState registrationState_;
    AuthState authState_;

    std::optional<client::GameState> gameState_;

    mutable std::mutex mutex_;

    std::vector<bindings::User> friendsList_;
    std::unordered_map<UserID, NameConversation> conversationsById_;
    std::vector<std::pair<std::string, Score>> ranking_;

    /*
     * @brief The network manager to manage the connection with the server
     */
    NetworkManager networkManager_;

    /*
     * @brief The screen manager to manage the screens to show to the user
     */
    ScreenManager screenManager_;

    /**
     * @brief Handles the received packet
     */
    void handlePacket(const std::string_view pack);

  public:
    /*
     * @brief Construct a new Controller object
     */
    Controller();

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
     */
    void run();

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
    const std::vector<std::pair<std::string, Score>> &getRanking() const;

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
    const std::vector<bindings::User> &getFriendsList() const;

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

    const NameConversation &getConversationWith(UserID userID);

    void bigDrop();

    void moveActive(TetrominoMove tetrominoMove);

    void rotateActive(bool clockwise);

    void emptyPenaltyStash();

    void holdNextTetromino();

    void quitGame();

    void handleKeypress(const std::string &pressedKey);

    size_t getBoardHeight();

    size_t getBoardWidth();

    Score getSelfScore() const;

    Score getSelfEnergy() const;

    GameMode getGameMode() const;

    std::optional<std::pair<unsigned, Controller::SelfCellType>>
    selfCellInfoAt(int x, int y) const;

    std::string getSelfUsername() const;

    std::optional<unsigned> opponentsBoardGetColorIdAt(size_t opponentIdx,
                                                       int x, int y) const;

    std::string getOpponentUsername(size_t opponentIdx) const;

    size_t getNumOpponents() const;

    bool gameHasStarted() const;

    bool noGame() const;
};

#endif // CONTROLLER_HPP
