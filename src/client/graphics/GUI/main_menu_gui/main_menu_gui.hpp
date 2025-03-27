#ifndef MAIN_MENU_GUI_HPP
#define MAIN_MENU_GUI_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QLabel>

#include "../rankinggui/rankinggui.hpp"
#include "../friends_menu_gui/friends_menu_gui.hpp"

class Controller; // Forward declaration

class MainMenuGui : public QWidget {
    Q_OBJECT

public:
    explicit MainMenuGui(Controller &controller, MainGui *mainGui = nullptr, QWidget *parent = nullptr);
    ~MainMenuGui() = default;

    /*
    * @brief Run the Main Menu Gui
    */
    void run();

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

    void showMainMenu();

private:
    Controller &controller_;

    QStackedWidget  *stackedWidget_;

    QWidget mainMenu_;

    RankingGui rankingGui_;
    FriendsMenuGui friendsMenuGui_;

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

};

#endif // MAIN_MENU_GUI_HPP
