#ifndef GUI_MAIN_GUI_HPP
#define GUI_MAIN_GUI_HPP

#include "login/login.hpp"
#include "main_menu/main_menu.hpp"

#include <memory>

#include <QMainWindow>
#include <QMessageBox>
#include <QStackedWidget>

class Controller;

enum class UpdateType;

namespace GUI {

    class MainGui : public QMainWindow {
        Q_OBJECT

      private:
        Controller &controller_;

        Login *login_;

        MainMenu *mainMenu_;

      public:
        MainGui(Controller &controller, QWidget *parent = nullptr);

        ~MainGui() = default;

        /*
         * @brief Run the main Gui
         */
        void run();

        /*
         * @brief Force the refresh of the GUI (QT)
         *
         * @param updateType The type of the update
         */
        void forceRefresh(UpdateType updateType);

        /*
          * @brief Action to perform when exiting the gui
         */
        void quitGui();

      public slots:
        /*
         * @brief Show the main menu page
         */
        void showMainMenu();

      signals:
        /*
         * @brief Signal to update the friends list
         */
        void updateFriendsList();

        /*
         * @brief Signal to update the friend requests list
         */
        void updateFriendRequestsList();

        /*
         * @brief Signal to update the ranking
         */
        void updateRanking();

        /*
         * @brief Signal to update the conversations
         */
        void updateConversations();

        /*
         * @brief Signal to update the game state
         */
        void updateGameState();
    };

} // namespace GUI

#endif // MAIN_GUI_HPP
