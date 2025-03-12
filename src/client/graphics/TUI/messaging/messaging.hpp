#ifndef MESSAGING_HPP
#define MESSAGING_HPP

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/mouse.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <cstdlib>
#include <optional>
#include <string>
#include <vector>

#include "../../IMessage.hpp"
#include "../../../core/in_game/player_state/player_state_external.hpp"

class Controller; // Forward declaration

class ScreenManager; // Forward declaration

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

class Messaging final : public IMessage {
  private:
    /*
     * @brief The screen to use to render the components
     */
    ScreenManager &screenManager_;

    /*
     * @brief The controller to ask for the data to show to the user
     */
    Controller &controller_;

    // std::map<std::string, std::vector<Message>> conversations_;
    std::vector<std::string> friendNames_;
    int selectedFriend_ = 0;
    std::string newFriendBuffer_;
    std::string newMessageBuffer_;

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

    void createButtons() override;

    void drawInputUser() override;

    void drawMenu() override;

    void drawDisplay() override;

    void drawWindow() override;

    std::optional<PlayerID> getSelectedFriendId();

  public:
    /*
     * @brief Construct a new Messaging object
     *
     * @param screen The screen to use to render the components
     * @param friends The list of friends to display in the messaging screen
     */
    Messaging(ScreenManager &screenManager, Controller &controller);

    /*
     * @brief Destroy the Messaging object
     */
    ~Messaging() = default;

    /*
     * @brief Render the messaging screen with all the components
     */
    void render() override;
};

#endif
