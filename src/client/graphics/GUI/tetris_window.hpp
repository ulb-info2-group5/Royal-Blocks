#ifndef GUI_TETRIS_WINDOW_HPP
#define GUI_TETRIS_WINDOW_HPP

#include "../../core/controller/update_type.hpp"
#include "login/login.hpp"
#include "main_menu/main_menu.hpp"

#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QStackedWidget>
#include <QStyleFactory>

enum class UpdateType;

namespace GUI {

    class TetrisWindow : public QMainWindow {
        Q_OBJECT

      private:
        Login *login_;

        MainMenu *mainMenu_;

        QSettings settings_;

        /**
         * @brief Sets theme to dark mode.
         */
        void setDarkMode();

        /**
         * @brief Sets theme to light mode.
         */
        void setLightMode();

      public:
        /**
         * @brief Constructor.
         */
        TetrisWindow(QWidget *parent = nullptr);

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
        void run(Controller &controller);

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
