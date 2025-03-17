#include "mainwindow.h"

#include "../../core/controller/controller.hpp"

#include <QMessageBox>
#include <cstdlib>
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget *parent, Controller *controller)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , controller_(controller)
{
    ui->setupUi(this);
    ui->UsernameInputRegister->setAlignment(Qt::AlignCenter);
    ui->PasswordInputRegister->setAlignment(Qt::AlignCenter);
    ui->UsernameInputLogin->setAlignment(Qt::AlignCenter);
    ui->PasswordInputLogin->setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ExitButton_clicked()
{
    std::exit(0);
}


void MainWindow::on_LoginButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2); // Login page
}


void MainWindow::on_RegisterButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1); // Register page
}


void MainWindow::on_BackButtonLogin_clicked()
{
    ui->stackedWidget->setCurrentIndex(0); // Main page
}


void MainWindow::on_BackButtonRegister_clicked()
{
    ui->stackedWidget->setCurrentIndex(0); // Main page
}


void MainWindow::on_SendButtonRegister_clicked()
{
    QString username = ui->UsernameInputRegister->text();
    QString password = ui->PasswordInputRegister->text();

    controller_->tryRegister(username.toStdString(), password.toStdString());

    bool registerSuccess = false;

    // Thread to check if registration is successful
    std::thread loginThread = std::thread([&]() {
        for (int i = 0; i < 20;
            ++i) { // 2 seconds limit (20 * 100ms)
            std::this_thread::sleep_for(
                std::chrono::milliseconds(100));
            if (controller_->getRegistrationState()
                == Controller::RegistrationState::Registered) {
                registerSuccess = true;
                return;
            }
        }
    });

    if (loginThread.joinable()) {
        loginThread.join();
    }

    if (registerSuccess) {
        QMessageBox::information(this, "Register successful", "You have successfully registered.");
        ui->stackedWidget->setCurrentIndex(2); // Login page
    }

    else {
        QMessageBox::warning(this, "Register failed", "This username is already taken.");
            ui->UsernameInputRegister->clear();
            ui->PasswordInputRegister->clear();
    }
}

void MainWindow::on_SendButtonLogin_clicked()
{
    QString username = ui->UsernameInputLogin->text();
    QString password = ui->PasswordInputLogin->text();

    controller_->tryLogin(username.toStdString(), password.toStdString());

    bool loginSuccess = false;

    // Thread to check if registration is successful
    std::thread loginThread = std::thread([&]() {
        for (int i = 0; i < 20;
            ++i) { // 2 seconds limit (20 * 100ms)
            std::this_thread::sleep_for(
                std::chrono::milliseconds(100));
            if (controller_->getRegistrationState()
                == Controller::RegistrationState::Registered) {
                loginSuccess = true;
                return;
            }
        }
    });

    if (loginThread.joinable()) {
        loginThread.join();
    }

    if (loginSuccess) {
        std::exit(0); // TODO: change it to go to the MainMenu
    }

    else {
        ui->UsernameInputLogin->clear();
        ui->PasswordInputLogin->clear();
        QMessageBox::warning(this, "Login failed", "Your username or password is incorrect.");
    }
}
