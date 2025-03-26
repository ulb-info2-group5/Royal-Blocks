#ifndef MAIN_MENU_GUI_HPP
#define MAIN_MENU_GUI_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QLabel>

class Controller; // Forward declaration

class MainMenuGui : public QWidget {
    Q_OBJECT

public:
    explicit MainMenuGui(Controller *controller, QWidget *parent = nullptr);
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

private:
    Controller *controller_;

    QStackedWidget  *stackedWidget_;

    QWidget *mainMenu_;

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
