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

public slots:
    void showMainMenu();

private slots:
    void on_QuitGameButton_clicked();

    void on_RankingButton_clicked();

    void on_BackToMainMenu_clicked();

private:
    Ui::MainWindow *ui;
    Controller *controller_;

    /*
    * @brief Action to perform when exiting the application for the eit at the login or at the main menu to quit the game
    */
    void actionOnExit();
};
#endif // MAIN_GUI_HPP
