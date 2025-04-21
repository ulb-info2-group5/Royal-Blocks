#ifndef TUI_MAIN_TUI_HPP
#define TUI_MAIN_TUI_HPP

#include <ftxui/component/screen_interactive.hpp>

#include "../../core/controller/update_type.hpp"
#include "../common/abstract_display.hpp"
#include "login_menu/login_menu.hpp"
#include "main_menu/main_menu.hpp"

namespace TUI {

    /**
     * @brief TUI component of the program.
     */
    class MainTui : public AbstractDisplay {
      private:
        ftxui::ScreenInteractive screen_;

        /**
         * @brief The current window to show to the user
         */
        ftxui::Component currentWindow_;

        /**
         * @brief Draw the start screen of the game with the title of the game
         */
        void drawStartScreen();

        /**
         * @brief Draw the end screen of the game with a goodbye message
         */
        void drawEndScreen();

        /**
         * @brief Handle the Ctrl+C and Ctrl+Z event to prevent the application
         * from closing
         *
         * @param component The component to handle the Ctrl+C and Ctrl+Z event
         * @return ftxui::Component The component with the Ctrl+C and Ctrl+Z
         * event handled
         */
        ftxui::Component handleCtrl(ftxui::Component &component);

      public:
        /**
         * @brief Construct a new Main Tui object
         *
         * @param controller The controller to use to interact with the game
         */
        MainTui();

        ~MainTui() = default;

        /**
         * @brief Render the component in the screen
         *
         * @param component The component to render
         */
        void render(ftxui::Component &component);

        /**
         * @brief Stop the rendering of the screen
         */
        void stopRender();

        /**
         * @biref Runs the TUI.
         */
        virtual void run(Controller &controller) override;

        /**
         * @brief Forces the screen to refresh the things related to the given
         * updateType.
         */
        virtual void forceRefresh(UpdateType updateType) override;

        /**
         * @brief Simulate the tab key press
         */
        void simulateTab();
    };

} // namespace TUI

#endif // TUI_MAIN_TUI_HPP
