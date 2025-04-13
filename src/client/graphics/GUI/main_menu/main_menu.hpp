#ifndef GUI_MAIN_MENU_HPP
#define GUI_MAIN_MENU_HPP

#include <QLabel>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>

#include "../friends_menu/friends_menu.hpp"
#include "../game_menu/game_menu.hpp"
#include "../message_menu/message_menu.hpp"
#include "../profile_manager/profile_manager.hpp"
#include "../ranking/ranking.hpp"

class Controller;

namespace GUI {

    class MainMenuGui : public QWidget {
        Q_OBJECT

      private:
        Controller &controller_;

        QStackedWidget stackedWidget_;

        QWidget mainMenu_;

        RankingGui rankingGui_;

        GameMenu gameMenu_;

        FriendsMenuGui friendsMenuGui_;

        MessageMenuGui messageMenuGui_;

        ProfileManagerGui profileManagerGui_;

        /*
         * @brief Action to perform when exiting the application for the eit at
         * the login or at the main menu to quit the game
         */
        void actionOnExit();

        /*
         * @brief Setup the Login Gui
         */
        void setup();

      private slots:
        /*
         * @brief Action to perform when the user click on the quit game button
         */
        void on_QuitGameButton_clicked();

        /*
         * @brief Action to perform when the user click on the ranking button
         */
        void on_RankingButton_clicked();

        /*
         * @brief Action to perform when the user click on the manage
         * friendslist button
         */
        void on_ManageFriendsListButton_clicked();

        /*
         * @brief Action to perform when the user click on the messages button
         */
        void on_MessagesButton_clicked();

        /*
         * @brief Action to perform when the user click on the create game
         * button
         */
        void on_CreateGameButton_clicked();

        /*
         * @brief Action to perform when the user click on the join game button
         */
        void on_JoinGameButton_clicked();

        /*
         * @brief Action to perform to show the main menu
         */
        void showMainMenu();

        /*
         * @brief Action to perform show profile manager
         */
        void on_ProfileManagerBouton_clicked();

      public:
        MainMenuGui(Controller &controller, MainGui &mainGui,
                    QWidget *parent = nullptr);

        ~MainMenuGui() = default;

        /*
         * @brief Run the Main Menu Gui
         */
        void run();
    };

} // namespace GUI

#endif // GUI_MAIN_MENU_HPP
