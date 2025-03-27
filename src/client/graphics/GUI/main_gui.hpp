#ifndef MAIN_GUI_HPP
#define MAIN_GUI_HPP

#include "main_menu_gui/main_menu_gui.hpp"
#include "logingui/logingui.hpp"

#include <QMainWindow>
#include <QMessageBox>
#include <QStackedWidget>
#include <qobjectdefs.h>

class Controller; // Forward declaration

enum class UpdateType; // Forward declaration

class MainGui : public QMainWindow
{
    Q_OBJECT

public:
    MainGui(QWidget *parent = nullptr, Controller *controller = nullptr);
    
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

private:
    Controller *controller_;
};
#endif // MAIN_GUI_HPP
