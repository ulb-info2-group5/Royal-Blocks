#ifndef MAIN_GUI_HPP
#define MAIN_GUI_HPP

#include "main_menu_gui/main_menu_gui.hpp"
#include "logingui/logingui.hpp"

#include <QMainWindow>
#include <QMessageBox>
#include <QStackedWidget>

class Controller; // Forward declaration

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
    */
    void forceRefresh();

public slots:
    /*
    * @brief Show the main menu page
    */
    void showMainMenu();

private:
    Controller *controller_;
};
#endif // MAIN_GUI_HPP
