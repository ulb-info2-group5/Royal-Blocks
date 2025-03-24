#ifndef MAIN_GUI_HPP
#define MAIN_GUI_HPP

#include <QMainWindow>
#include <QMessageBox>

class Controller; // Forward declaration

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainGui : public QMainWindow
{
    Q_OBJECT

public:
    MainGui(QWidget *parent = nullptr, Controller *controller = nullptr);
    
    ~MainGui();

    void forceRefresh();

private slots:

    void on_ExitButton_clicked();

    void on_LoginButton_clicked();

    void on_RegisterButton_clicked();

    void on_BackButtonLogin_clicked();

    void on_BackButtonRegister_clicked();

    void on_SendButtonRegister_clicked();

    void on_SendButtonLogin_clicked();

    void on_QuitGameButton_clicked();

private:
    Ui::MainWindow *ui;
    Controller *controller_;

    /*
    * @brief Action to perform when exiting the application for the eit at the login or at the main menu to quit the game
    */
    void actionOnExit();

    /*
    * @brief Clear the inputs of the user
    */
    void clearInputs();
};
#endif // MAIN_GUI_HPP
