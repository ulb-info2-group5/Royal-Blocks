#include "main_gui.hpp"

#include "../../core/controller/controller.hpp"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QApplication>
#include <qmainwindow.h>

MainGui::MainGui(QWidget *parent, Controller *controller)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , controller_(controller)
{
    ui->setupUi(this);

    ui->UsernameInputRegister->setAlignment(Qt::AlignCenter);
    ui->UsernameInputLogin->setAlignment(Qt::AlignCenter);

    ui->PasswordInputRegister->setAlignment(Qt::AlignCenter);
    ui->PasswordInputRegister->setEchoMode(QLineEdit::Password);

    ui->PasswordInputLogin->setAlignment(Qt::AlignCenter);
    ui->PasswordInputLogin->setEchoMode(QLineEdit::Password);

    ui->stackedWidget->setCurrentIndex(0); // MainMenuLogin page
}

MainGui::~MainGui()
{
    delete ui;
}

void MainGui::forceRefresh()
{
    this->update();
}

void MainGui::on_ExitButton_clicked()
{
    actionOnExit();
}


void MainGui::on_LoginButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2); // Login page
}


void MainGui::on_RegisterButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1); // Register page
}


void MainGui::on_BackButtonLogin_clicked()
{
    ui->stackedWidget->setCurrentIndex(0); // Main page
}


void MainGui::on_BackButtonRegister_clicked()
{
    ui->stackedWidget->setCurrentIndex(0); // Main page
}


void MainGui::on_SendButtonRegister_clicked()
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

    clearInputs();

    if (registerSuccess) {
        QMessageBox::information(this, "Register successful", "You have successfully registered.");
        ui->stackedWidget->setCurrentIndex(2); // Login page
    }

    else {
        QMessageBox::warning(this, "Register failed", "This username is already taken.");
    }
}

void MainGui::on_SendButtonLogin_clicked()
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

    clearInputs();

    if (loginSuccess) {
        ui->stackedWidget->setCurrentIndex(3); // Main Menu page
    }

    else {
        QMessageBox::warning(this, "Login failed", "Your username or password is incorrect.");
    }
}

void MainGui::on_QuitGameButton_clicked()
{
    actionOnExit();
}

/*--------------------------------------------
                PRIVATE METHODS
--------------------------------------------*/

void MainGui::actionOnExit()
{
    QMessageBox::StandardButton confirmExit;
    confirmExit = QMessageBox::question(this, "Quit", "Are you sure you want to qut the game ?",
                                    QMessageBox::Yes | QMessageBox::No);
    if (confirmExit == QMessageBox::Yes) {
        QApplication::quit();
    }
}

void MainGui::clearInputs()
{
    ui->UsernameInputRegister->clear();
    ui->PasswordInputRegister->clear();

    ui->UsernameInputLogin->clear();
    ui->PasswordInputLogin->clear();
}