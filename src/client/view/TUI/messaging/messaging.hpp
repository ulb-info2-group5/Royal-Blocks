#ifndef MESSAGING_HPP
#define MESSAGING_HPP

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/mouse.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../../IMessage.hpp"

class Controller; // Forward declaration

/**
 * @brief Enum class to represent the state of the messaging
 *
 */
// enum class MessagingState {
//     BACK,
//     NONE,
// };

// struct Message {
//     int idSender;
//     std::string message;
// };

class Messaging : public IMessage {
  private:
    /*
     * @brief The screen to use to render the components
     */
    std::shared_ptr<ftxui::ScreenInteractive> screen_;

    /*
     * @brief The controller to ask for the data to show to the user
     */
    Controller *controller_;

    std::map<std::string, std::vector<Message>> conversations_;
    std::vector<std::string> friends_;
    int selectedFriend = 0;
    std::string newFriend_;
    std::string newMessage_;

    MessagingState userState_;

    ftxui::Component friendsMenu_;
    ftxui::Component addMenu_;

    ftxui::Component addFriendInput_;
    ftxui::Component messageInput_;

    ftxui::Component backButton_;
    ftxui::Component sendButton_;
    ftxui::Component addFriendButton_;

    ftxui::Component sidebar_;
    ftxui::Component chatDisplay_;

    ftxui::Component displayWindow_;

    // just to simulate a user ID
    int userId = 5;
    void initMessaging();

  protected:
    void drawButtons() override;

    void drawInputUSer() override;

    void drawMenu() override;

    void drawDisplay() override;

    void drawWindow() override;

  public:
    /*
     * @brief Construct a new Messaging object
     *
     * @param screen The screen to use to render the components
     * @param friends The list of friends to display in the messaging screen
     */
    Messaging(std::shared_ptr<ftxui::ScreenInteractive> screen,
              Controller *controller);

    /*
     * @brief Destroy the Messaging object
     */
    ~Messaging() = default;

    /*
     * @brief Render the messaging screen with all the components
     */
    void render() override;

    // void addFriends(std::string friendName) override;

    /*
     * @brief add a message to a discussion
     */
    void addMessage(const std::string &message) override;
};

#endif