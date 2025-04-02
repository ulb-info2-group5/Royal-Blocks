#ifndef MAIN_MENU_GUI_HPP
#define MAIN_MENU_GUI_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QLabel>

#include "../rankinggui/rankinggui.hpp"
#include "../friends_menu_gui/friends_menu_gui.hpp"
#include "../message_menu_gui/message_menu_gui.hpp"
#include "../game_menu_gui/game_menu_gui.hpp"

class Controller; // Forward declaration

class MainMenuGui : public QWidget {
    Q_OBJECT

    private:
        Controller &controller_;

        QStackedWidget  *stackedWidget_;

        QWidget mainMenu_;

        RankingGui rankingGui_;

        GameMenuGUI gameMenuGui_;

        FriendsMenuGui friendsMenuGui_;

        MessageMenuGui messageMenuGui_;

        QPushButton createGameButton_;
        QPushButton joinGameButton_;
        QPushButton messagesButton_;
        QPushButton rankingButton_;
        QPushButton manageProfileButton_;
        QPushButton manageFriendsListButton_;
        QPushButton quitGameButton_;

        /*
        * @brief Action to perform when exiting the application for the eit at the login or at the main menu to quit the game
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
        * @brief Action to perform when the user click on the manage friendslist button
        */
        void on_ManageFriendsListButton_clicked();

        /*
        * @brief Action to perform when the user click on the messages button
        */
        void on_MessagesButton_clicked();

        /*
        * @brief Action to perform when the user click on the create game button
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

    public:
        MainMenuGui(Controller &controller, MainGui &mainGui, QWidget *parent = nullptr);

        ~MainMenuGui() = default;

        /*
        * @brief Run the Main Menu Gui
        */
        void run();
};

#endif // MAIN_MENU_GUI_HPP
