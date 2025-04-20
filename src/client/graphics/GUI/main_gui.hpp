#ifndef GUI_MAIN_GUI_HPP
#define GUI_MAIN_GUI_HPP

#include "../common/abstract_display.hpp"
#include "login/login.hpp"
#include "main_menu/main_menu.hpp"

#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QStackedWidget>
#include <qapplication.h>

class Controller;

enum class UpdateType;

namespace GUI {

    class MainGui : public QMainWindow, public AbstractDisplay {
        Q_OBJECT

      private:
        QApplication &app_;

        Login *login_;

        MainMenu *mainMenu_;

        QSettings settings_;

        void setDarkMode();
        void setLightMode();

      public:
        MainGui(QApplication &app, QWidget *parent = nullptr);

        ~MainGui() = default;

        /*
         * @brief Run the main Gui
         */
        virtual void run(Controller &controller) override;

        /*
         * @brief Update the screen manager with the new data
         *
         * @param updateType The type of update to do (needed for the GUI with
         * Qt)
         */
        virtual void forceRefresh(UpdateType updateType) override;

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
