#ifndef TUI_MESSAGING_HPP
#define TUI_MESSAGING_HPP

#include "../../../core/in_game/player_state/player_state_external.hpp"

#include <ftxui/component/component.hpp>
#include <string>
#include <vector>

class Controller;

namespace TUI {

    class MainTui;

    enum class MessagingState {
        BACK,
        NONE,
    };

    class Messaging final {
      private:
        /*
         * @brief The screen to use to render the components
         */
        MainTui &mainTui_;

        /*
         * @brief The controller to ask for the data to show to the user
         */
        Controller &controller_;

        std::vector<std::string> friendNames_;
        int selectedFriend_ = 0;
        std::string newFriendBuffer_;
        std::string newMessageBuffer_;

        MessagingState userState_;

        ftxui::Component friendsMenu_;

        ftxui::Component messageInput_;

        ftxui::Component backButton_;
        ftxui::Component sendButton_;

        ftxui::Component sidebar_;
        ftxui::Component chatDisplay_;

        ftxui::Component displayWindow_;

        // just to simulate a user ID
        int userId = 5;

        /*
         * @brief Create all the buttons needed for the messaging screen
         */
        void createButtons();

        /*
         * @brief Draw the input to write a message
         */
        void drawInputUser();

        /*
         * @brief Draw the menu of the messaging screen
         */
        void drawMenu();

        /*
         * @brief Draw the display of the messaging screen
         */
        void drawDisplay();

        /*
         * @brief Draw the window of the messaging screen
         */
        void drawWindow();

        /*
         * @brief Get the selected friend ID
         *
         * @return std::optional<UserID> The ID of the selected friend
         */
        std::optional<UserID> getSelectedFriendId();

      public:
        /*
         * @brief Construct a new Messaging object
         *
         * @param screenManager The screen manager for asking to render the
         * components
         * @param controller The controller to interact with the server
         */
        Messaging(MainTui &mainTui, Controller &controller);

        /*
         * @brief Destroy the Messaging object
         */
        ~Messaging() = default;

        /*
         * @brief Render the messaging screen with all the components
         */
        void render();
    };

} // namespace TUI

#endif // TUI_MESSAGING_HPP
