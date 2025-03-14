#ifndef MESSAGING_HPP
#define MESSAGING_HPP

#include "../../../core/in_game/player_state/player_state_external.hpp"
#include "../../IMessage.hpp"

#include <ftxui/component/component.hpp>
#include <string>
#include <vector>

class Controller; // Forward declaration

class ScreenManager; // Forward declaration

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

    std::optional<UserID> getSelectedFriendId();

  public:
    /*
     * @brief Construct a new Messaging object
     *
     * @param screenManager The screen manager for asking to render the
     * components
     * @param controller The controller to interact with the server
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
