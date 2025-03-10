/**
 * @file controller.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief Controller class header file
 * @date 2025-02-24
 *
 */

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "../../graphics/TUI/screen_manager.hpp"
#include "../common/bindings/conversations.hpp"
#include "../common/bindings/friends_list.hpp"
#include "../common/bindings/ranking.hpp"
#include "../in_game/game_state_wrapper.hpp"
#include "../network/network_manager.hpp"
#include "core/in_game/player_state/player_state_external.hpp"
#include "game_mode/game_mode.hpp"

#include <memory>
#include <mutex>
#include <string>
#include <vector>

using Score = size_t;

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

  private:
    boost::asio::io_context context_;
    std::thread ioThread_;

    RegistrationState registrationState_;
    AuthState authState_;

    std::shared_ptr<client::GameStateWrapper> pGameState_;

    std::mutex mutex_;

    bindings::FriendsList friendsList_;
    bindings::Conversations conversations_;
    bindings::Ranking ranking_;

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
    void handlePacket(const std::string &pack);

  public:
    /*
     * @brief Construct a new Controller object
     */
    Controller();

    /*
     * @brief Destroy the Controller object
     */
    ~Controller();

    /**
     * @brief Returns the registration-state.
     */
    RegistrationState getRegistrationState() const;

    /**
     * @brief Returns the authentication-state.
     */
    AuthState getAuthState() const;

    // TODO
    std::shared_ptr<client::GameStateWrapper> &getGameState();

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
    const bindings::Ranking &getRanking() const;

    /*
     * @brief Change the profile of the user by changing the username and
     * password
     *
     * @param username The new username of the user
     * @param password The new password of the user
     */
    void changeProfile(const std::string &username,
                       const std::string &password) const;

    /*
     * @brief Get the friends list of the user
     */
    const bindings::FriendsList &getFriendsList() const;

    /*
     * @brief Add a friend to the friends list of the user
     *
     * @param username The name of the friend to add
     */
    void sendFriendRequest(const std::string &username);

    /*
     * @brief Remove a friend from the friends list of the user
     *
     * @param username The name of the friend to remove
     */
    void removeFriend(const std::string &username);

    /*
     * @brief Send a message to a friend
     *
     * @param recipientId The PlayerID of the friend to send the message
     * @param message The message to send
     */
    void sendMessage(PlayerID recipientId, const std::string &message);

    void createGame(GameMode gameMode, size_t targetNumPlayers);

    void joinGame(GameMode gameMode, std::optional<PlayerID> friendID);

    // TODO
    const NameConversation &getConversationWith(PlayerID playerID);
};

#endif // CONTROLLER_HPP
