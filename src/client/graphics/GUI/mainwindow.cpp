#include "mainwindow.h"

#include "../../core/controller/controller.hpp"

#include <QMessageBox>
#include <QApplication>

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

    ui->stackedWidget->setCurrentIndex(0); // MainMenuLogin page
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ExitButton_clicked()
{
    QApplication::quit();
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

    ui->UsernameInputRegister->clear();
    ui->PasswordInputRegister->clear();

    if (registerSuccess) {
        QMessageBox::information(this, "Register successful", "You have successfully registered.");
        ui->stackedWidget->setCurrentIndex(2); // Login page
    }

    else {
        QMessageBox::warning(this, "Register failed", "This username is already taken.");
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
            if (controller_->getAuthState()
                == Controller::AuthState::Authenticated) {
                loginSuccess = true;
                return;
            }
        }
    });

    if (loginThread.joinable()) {
        loginThread.join();
    }

    ui->UsernameInputLogin->clear();
    ui->PasswordInputLogin->clear();

    if (loginSuccess) {
        ui->stackedWidget->setCurrentIndex(3); // Main Menu page
    }

    else {
        QMessageBox::warning(this, "Login failed", "Your username or password is incorrect.");
    }
}

void MainWindow::on_QuitGameButton_clicked()
{
    QApplication::quit();
}