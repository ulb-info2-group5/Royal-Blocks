/*
 * This file is part of Royal Blocks.
 *
 * Royal Blocks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Royal Blocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Royal Blocks.  If not, see <https://www.gnu.org/licenses/>.
 */

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
    class MainTui final : public AbstractDisplay {
      private:
        ftxui::ScreenInteractive screen_;

        LoginMenu loginMenu_;
        
        MainMenu mainMenu_;

        /**
         * @brief The current window to show to the user
         */
        ftxui::Component currentWindow_;

        bool shouldStop_;

        bool restartRequested_;

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
        MainTui(Controller &controller);

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
        void run() override;

        /**
         * @brief Forces the screen to refresh the things related to the given
         * updateType.
         */
        void forceRefresh(UpdateType updateType) override;

        /**
         * @brief Simulate the tab key press
         */
        void simulateTab();

        void onDisconnected() override;
    };

} // namespace TUI

#endif // TUI_MAIN_TUI_HPP
