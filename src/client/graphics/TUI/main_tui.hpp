#ifndef TUI_MAIN_TUI_HPP
#define TUI_MAIN_TUI_HPP

#include <ftxui/component/screen_interactive.hpp>

#include "login_menu/login_menu.hpp"
#include "main_menu/main_menu.hpp"

namespace TUI {

    class MainTui {
      private:
        Controller &controller_;

        ftxui::ScreenInteractive screen_;

        /*
         * @brief The login menu to show to the user
         */
        LoginMenu loginMenu_;

        /*
         * @brief The main menu to show to the user
         */
        MainMenu mainMenu_;

        /*
         * @brief The current window to show to the user
         */
        ftxui::Component currentWindow_;

        /*
         * @brief Draw the start screen of the game with the title of the game
         */
        void drawStartScreen();

        /*
         * @brief Draw the end screen of the game with a goodbye message
         */
        void drawEndScreen();

        /*
         * @brief Handle the Ctrl+C and Ctrl+Z event to prevent the application
         * from closing
         *
         * @param component The component to handle the Ctrl+C and Ctrl+Z event
         * @return ftxui::Component The component with the Ctrl+C and Ctrl+Z
         * event handled
         */
        ftxui::Component handleCtrl(ftxui::Component &component);

      public:
        MainTui(Controller &controller);

        ~MainTui() = default;

        void run();

        /*
         * @brief Render the component in the screen
         *
         * @param component The component to render
         */
        void render(ftxui::Component &component);

        /*
         * @brief Stop the rendering of the screen
         */
        void stopRender();

        /*
         * @brief Force the screen to refresh
         */
        void forceRefresh();

        /*
         * @brief Simulate the tab key press
         */
        void simulateTab();
    };

} // namespace TUI

#endif // TUI_MAIN_TUI_HPP
