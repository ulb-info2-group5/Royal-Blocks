/**
 * @file controller.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief Controller class header file
 * @date 2025-02-24
 *
 */

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "../core/game_state/game_state.hpp"
#include "../network/network_manager.hpp"
#include "../view/TUI/screen_manager.hpp"

#include <map>
#include <mutex>
#include <string>
#include <vector>

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

    std::mutex mutex_;

    client::GameState gameState;

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
     *
     * @return std::vector<std::tuple<int, std::string, int>> The ranking of the
     * players of the Endless mode
     */
    std::vector<std::tuple<int, std::string, int>> getRanking() const;

    /*
     * @brief Change the profile of the user by changing the username and
     * password
     *
     * @param username The new username of the user
     * @param password The new password of the user
     * @return true If the profile is changed, false otherwise
     */
    bool changeProfile(const std::string &username,
                       const std::string &password) const;

    /*
     * @brief Get the friends list of the user
     *
     * @return std::vector<std::string> The friends list of the user
     */
    std::vector<std::string> getFriendsList() const;

    /*
     * @brief Add a friend to the friends list of the user
     *
     * @param friendName The name of the friend to add
     * @return true If the friend is added, false otherwise
     */
    bool addFriend(const std::string &friendName) const;

    /*
     * @brief Remove a friend from the friends list of the user
     *
     * @param friendName The name of the friend to remove
     * @return true If the friend is removed, false otherwise
     */
    bool removeFriend(const std::string &friendName) const;

    /*
     * @brief Send a message to a friend
     *
     * @param friendName The name of the friend to send the message
     * @param message The message to send
     * @return true If the message is sent, false otherwise
     */
    bool sendMessage(const std::string &friendName,
                     const std::string &message) const;

    /*
     * @brief Get the messages of all the conversations of the user
     *
     * @return std::map<std::string, std::vector<std::string>> The messages of
     * all the conversations of the user
     */
    std::map<std::string, std::vector<Message>> getMessages() const;

    /*
     * @brief Get the boards of the players
     *
     * @return std::shared_ptr<std::vector<std::array<std::array<colors, WIDTH>,
     * HEIGHT>>> The boards of the players
     */
    std::shared_ptr<std::vector<std::array<std::array<colors, WIDTH>, HEIGHT>>>
    getBoards() const;

    /*
     * @brief Get the friends online of the user
     *
     * @return std::vector<std::string> The friends online of the user
     */
    std::vector<std::string> getFriendsOnline() const;
};

#endif // CONTROLLER_HPP
