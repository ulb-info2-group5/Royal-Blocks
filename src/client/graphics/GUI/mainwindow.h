#ifndef MAINLOGINWINDOW_H
#define MAINLOGINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "core/controller/controller.hpp"
#include "ui_mainwindow.h"

class Controller; // Forward declaration

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, Controller *controller = nullptr);
    ~MainWindow();

private slots:

    void on_ExitButton_clicked();

    void on_LoginButton_clicked();

    void on_RegisterButton_clicked();

    void on_BackButtonLogin_clicked();

    void on_BackButtonRegister_clicked();

    void on_SendButtonRegister_clicked();

    void on_SendButtonLogin_clicked();


private:
    Ui::MainWindow *ui;
    Controller *controller_;
};
#endif // MAINLOGINWINDOW_H
