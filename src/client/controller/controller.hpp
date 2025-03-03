/**
 * @file controller.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief Controller class header file
 * @date 2025-02-24
 *
 */

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "../network/network_manager.hpp"
#include "../view/TUI/screen_manager.hpp"

#include <map>
#include <mutex>
#include <string>
#include <vector>

struct Message; // Forward declaration

class Controller {
  public:
    enum class State {
        Connected,
        Disconnected,
    };

  private:
    boost::asio::io_context context_;
    std::thread ioThread_;

    State state_;
    std::mutex stateMutex_;

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

    // TODO
    State getState() const;

    /*
     * @brief Run the controller to manage the game
     */
    void run();

    /*
     * @brief TODO
     *
     * @param username The username of the user
     * @param password The password of the user
     * @return true If the account is created, false otherwise
     */
    void tryRegister(const std::string &username, const std::string &password);

    /*
     * @brief TODO
     *
     * @param username The username of the user
     * @param password The password of the user
     * @return true If the username and password are correct, false otherwise
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
