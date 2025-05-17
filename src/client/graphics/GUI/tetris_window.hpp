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

#ifndef GUI_TETRIS_WINDOW_HPP
#define GUI_TETRIS_WINDOW_HPP

#include "../../core/controller/update_type.hpp"
#include "login/login.hpp"
#include "main_menu/main_menu.hpp"

#include <QMainWindow>
#include <QSettings>
#include <QPointer>


enum class UpdateType; // Forward declaration
 
class Controller; // Forward declaration

namespace GUI {
    class MainGui; // Forward declaration

    /**
     * @brief MainWindow of the GUI tetris client.
     */
    class TetrisWindow : public QMainWindow {
        Q_OBJECT

      private:
        Controller &controller_;

        QPointer<Login> login_;

        QPointer<MainMenu> mainMenu_;

        QSettings settings_;

        /**
         * @brief Sets theme to dark mode.
         */
        void setDarkMode();

        /**
         * @brief Sets theme to light mode.
         */
        void setLightMode();

        /**
         * @brief Create Login and MainMenu widgets and run Login.
         */
        void start();

      private slots:
        /**
         * @brief Action to perform when we receive the clientDisconnected signal from MainGui
         */
        void backToLoginMenu();

      public:
        /**
         * @brief Constructor.
         */
        TetrisWindow(Controller &Controller, MainGui &mainGui, QWidget *parent = nullptr);

        /**
         * @brief Forces the screen to refresh the things related to the given
         * updateType.
         */
        void forceRefresh(UpdateType updateType);

        /**
         * @brief Show the main menu page
         */
        void showMainMenu();

        /**
         * @brief Runs the GUI.
         */
        void run();

        /**
         * @brief Action to perform when exiting the gui
         */
        void quitGui();

      signals:
        /**
         * @brief Signal to update the friends list
         */
        void updateFriendsList();

        /**
         * @brief Signal to update the friend requests list
         */
        void updateFriendRequestsList();

        /**
         * @brief Signal to update the ranking
         */
        void updateRanking();

        /**
         * @brief Signal to update the conversations
         */
        void updateConversations();

        /**
         * @brief Signal to update the game state
         */
        void updateGameState();
    };

} // namespace GUI

#endif // GUI_TETRIS_WINDOW_HPP
