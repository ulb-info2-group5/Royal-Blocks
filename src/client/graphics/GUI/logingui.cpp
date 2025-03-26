#include "logingui.hpp"

#include <QLabel>
#include <qlabel.h>
#include <string_view>

#include "../../core/controller/controller.hpp"

const std::string invalidChars = "!@#$%^&*()+=[]{}|\\\"'<>?/°;,~:²³§_£";


LoginGui::LoginGui(Controller *controller, QWidget *parent)
    : QWidget(parent), controller_(controller) {
    stackedWidget_ = new QStackedWidget();

    QPushButton *exitButton = new QPushButton("Exit");
    QPushButton *loginButton = new QPushButton("Login");
    QPushButton *registerButton = new QPushButton("Register");
    QPushButton *backButtonLogin = new QPushButton("Back");
    QPushButton *backButtonRegister = new QPushButton("Back");
    QPushButton *sendButtonRegister = new QPushButton("Send");
    QPushButton *sendButtonLogin = new QPushButton("Send");

    connect(exitButton, &QPushButton::clicked, this, &LoginGui::on_ExitButton_clicked);
    connect(loginButton, &QPushButton::clicked, this, &LoginGui::on_LoginButton_clicked);
    connect(registerButton, &QPushButton::clicked, this, &LoginGui::on_RegisterButton_clicked);
    connect(backButtonLogin, &QPushButton::clicked, this, &LoginGui::on_BackButtonLogin_clicked);
    connect(backButtonRegister, &QPushButton::clicked, this, &LoginGui::on_BackButtonRegister_clicked);
    connect(sendButtonRegister, &QPushButton::clicked, this, &LoginGui::on_SendButtonRegister_clicked);
    connect(sendButtonLogin, &QPushButton::clicked, this, &LoginGui::on_SendButtonLogin_clicked);

    
    usernameInputRegister_ = new QLineEdit();
    passwordInputRegister_ = new QLineEdit();
    usernameInputLogin_ = new QLineEdit();
    passwordInputLogin_ = new QLineEdit();

    usernameInputRegister_->setAlignment(Qt::AlignCenter);
    passwordInputRegister_->setAlignment(Qt::AlignCenter);
    passwordInputRegister_->setEchoMode(QLineEdit::Password);
    usernameInputLogin_->setAlignment(Qt::AlignCenter);
    passwordInputLogin_->setAlignment(Qt::AlignCenter);
    passwordInputLogin_->setEchoMode(QLineEdit::Password);

    usernameInputRegister_->setPlaceholderText("Enter a username");
    passwordInputRegister_->setPlaceholderText("Enter a password");
    usernameInputLogin_->setPlaceholderText("Enter your username");
    passwordInputLogin_->setPlaceholderText("Enter your password");


    // Create the main page
    mainPage_ = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addWidget(createCenterBoldTitle("Welcome to Royal Tetris !"));
    mainLayout->addWidget(registerButton);
    mainLayout->addWidget(loginButton);
    mainLayout->addWidget(exitButton);
    mainLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainPage_->setLayout(mainLayout);


    // Create the register page
    registerPage_ = new QWidget();
    QVBoxLayout *registerPageLayout = new QVBoxLayout();
    registerPageLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    registerPageLayout->addWidget(createCenterBoldTitle("Register"));
    registerPageLayout->addWidget(usernameInputRegister_);
    registerPageLayout->addWidget(passwordInputRegister_);
    registerPageLayout->addWidget(sendButtonRegister);
    registerPageLayout->addWidget(backButtonRegister);
    registerPageLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    registerPage_->setLayout(registerPageLayout);


    // Create the login page
    loginPage_ = new QWidget();
    QVBoxLayout *loginPageLayout = new QVBoxLayout();
    loginPageLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    loginPageLayout->addWidget(createCenterBoldTitle("Login"));
    loginPageLayout->addWidget(usernameInputLogin_);
    loginPageLayout->addWidget(passwordInputLogin_);
    loginPageLayout->addWidget(sendButtonLogin);
    loginPageLayout->addWidget(backButtonLogin);
    loginPageLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    loginPage_->setLayout(loginPageLayout);


    stackedWidget_->addWidget(mainPage_);
    stackedWidget_->addWidget(registerPage_);   
    stackedWidget_->addWidget(loginPage_);


    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(stackedWidget_);
    setLayout(layout);
}

void LoginGui::on_ExitButton_clicked()
{
    actionOnExit();
}


void LoginGui::on_LoginButton_clicked()
{
    stackedWidget_->setCurrentWidget(loginPage_);
}


void LoginGui::on_RegisterButton_clicked()
{
    stackedWidget_->setCurrentWidget(registerPage_);
}


void LoginGui::on_BackButtonLogin_clicked()
{
    stackedWidget_->setCurrentWidget(mainPage_);
}


void LoginGui::on_BackButtonRegister_clicked()
{
    stackedWidget_->setCurrentWidget(mainPage_);
}


void LoginGui::on_SendButtonRegister_clicked()
{
    QString username = usernameInputRegister_->text();
    QString password = passwordInputRegister_->text();

    if (!isValidRegister()) {
        clearInputs();
        QMessageBox::warning(this, "Register failed", errorMessage_.c_str());
        return;
    }

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
        stackedWidget_->setCurrentWidget(loginPage_);

    }

    else {
        QMessageBox::warning(this, "Register failed", "This username is already taken.");
    }
}

void LoginGui::on_SendButtonLogin_clicked()
{
    QString username = usernameInputLogin_->text();
    QString password = passwordInputLogin_->text();

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
        emit loginSuccessful();
    }

    else {
        QMessageBox::warning(this, "Login failed", "Your username or password is incorrect.");
    }
}


/*-------------------------------------------------------
                    Private Methods
-------------------------------------------------------*/


void LoginGui::clearInputs()
{
    usernameInputRegister_->clear();
    passwordInputRegister_->clear();

    usernameInputLogin_->clear();
    passwordInputLogin_->clear();
}

void LoginGui::actionOnExit()
{
    QMessageBox::StandardButton confirmExit;
    confirmExit = QMessageBox::question(this, "Quit", "Are you sure you want to qut the game ?",
                                    QMessageBox::Yes | QMessageBox::No);
    if (confirmExit == QMessageBox::Yes) {
        QApplication::quit();
    }
}

QLabel *LoginGui::createCenterBoldTitle(const std::string_view &title)
{
    QLabel *titleLabel = new QLabel(title.data());
    QFont boldFont = titleLabel->font();
    boldFont.setBold(true);
    boldFont.setPointSize(20);
    titleLabel->setFont(boldFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    return titleLabel;
}

bool LoginGui::isValidRegister() {
    errorMessage_.clear();

    if (usernameInputRegister_->text().length() < 4) {
        errorMessage_ = "The lenght of your username is too short ! The username must have at least 4 characters";
        return false;
    }

    if (usernameInputRegister_->text().length() > 20) {
        errorMessage_ = "The lenght of your username is too long ! It must have less than 20 characters";
    }

    for (const char c : usernameInputRegister_->text().toStdString()) {
        if (invalidChars.find(c) != std::string::npos || isspace(c)) {
            if (isprint(c)) {
                errorMessage_ = "Your username contains an invalid character : '" + std::string(1, c) + "'";
            } else  {
                errorMessage_ = "Your username contains an invalid character with ASCII value " + std::to_string(static_cast<int>(c)) + " !";
            }
            return false;
        }
    }

    if (passwordInputRegister_->text().isEmpty()) {
        errorMessage_ = "Your password is empty ! You must enter a valid password";
        return false;
    }

    return true;
}