#ifndef GUI_MAIN_GUI_HPP
#define GUI_MAIN_GUI_HPP

#include "login/login.hpp"
#include "main_menu/main_menu.hpp"

#include <QMainWindow>
#include <QMessageBox>
#include <QStackedWidget>
#include <memory>
#include <qobjectdefs.h>

class Controller;

enum class UpdateType;

namespace GUI {

    class MainGui : public QMainWindow {
        Q_OBJECT

      private:
        Controller &controller_;

        std::unique_ptr<LoginGui> loginGui_;
        std::unique_ptr<MainMenuGui> mainMenuGui_;

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

        // TODO
        void updateGameState();
    };

} // namespace GUI

#endif // MAIN_GUI_HPP
