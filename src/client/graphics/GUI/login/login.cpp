#include "login.hpp"

#include "../../../core/controller/controller.hpp"
#include "../qt_config/qt_config.hpp"

#include <QCheckBox>
#include <QVBoxLayout>

namespace GUI {

    const std::string invalidChars = "!@#$%^&*()+=[]{}|\\\"'<>?/°;,~:²³§_£";
    constexpr int INPUT_BUTTON_WIDTH = 500;

    Login::Login(Controller &controller, QWidget *parent)
        : QWidget(parent), controller_(controller) {}

    void Login::run() {
        setup();

        QVBoxLayout *layout = new QVBoxLayout();
        layout->addWidget(&stackedWidget_);
        setLayout(layout);

        show();
    }

    void Login::on_ExitButton_clicked() { actionOnExit(); }

    void Login::on_LoginButton_clicked() {
        stackedWidget_.setCurrentIndex(2); // Login page
    }

    void Login::on_RegisterButton_clicked() {
        stackedWidget_.setCurrentIndex(1); // Register page
    }

    void Login::on_BackButtonLogin_clicked() {
        clearInputs();
        stackedWidget_.setCurrentIndex(0); // Main page
    }

    void Login::on_BackButtonRegister_clicked() {
        clearInputs();
        stackedWidget_.setCurrentIndex(0); // Main page
    }

    void Login::on_SendButtonRegister_clicked() {
        QString username = usernameInputRegister_.text();
        QString password = passwordInputRegister_.text();

        if (!isValidRegister()) {
            clearInputs();
            QMessageBox::warning(this, "Register failed",
                                 errorMessage_.c_str());
            return;
        }

        controller_.tryRegister(username.toStdString(), password.toStdString());

        bool registerSuccess = false;

        // Thread to check if registration is successful
        std::thread loginThread = std::thread([&]() {
            for (int i = 0; i < 20; ++i) { // 2 seconds limit (20 * 100ms)
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                if (controller_.getRegistrationState()
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
            QMessageBox::information(this, "Register successful",
                                     "You have successfully registered.");
            stackedWidget_.setCurrentIndex(2); // Login page

        }

        else {
            QMessageBox::warning(this, "Register failed",
                                 "This username is already taken.");
            usernameInputRegister_.setFocus();
        }
    }

    void Login::on_SendButtonLogin_clicked() {
        QString username = usernameInputLogin_.text();
        QString password = passwordInputLogin_.text();

        controller_.tryLogin(username.toStdString(), password.toStdString());

        bool loginSuccess = false;

        // Thread to check if registration is successful
        std::thread loginThread = std::thread([&]() {
            for (int i = 0; i < 20; ++i) { // 2 seconds limit (20 * 100ms)
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                if (controller_.getAuthState()
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
            QMessageBox::warning(this, "Login failed",
                                 "Your username or password is incorrect.");
            usernameInputLogin_.setFocus();
        }
    }

    void Login::on_UsernameInputRegister_EnterPressed() {
        if (usernameInputRegister_.hasFocus()) {
            passwordInputRegister_.setFocus();
        }
    }

    void Login::on_UsernameInputLogin_EnterPressed() {
        if (usernameInputLogin_.hasFocus()) {
            passwordInputLogin_.setFocus();
        }
    }

    void Login::on_PasswordInputRegister_EnterPressed() {
        if (passwordInputRegister_.hasFocus()) {
            if (!passwordInputRegister_.text().isEmpty()
                && !usernameInputRegister_.text().isEmpty()) {
                sendButtonRegister_.click();
            }
        }
    }

    void Login::on_PasswordInputLogin_EnterPressed() {
        if (passwordInputLogin_.hasFocus()) {
            if (!passwordInputLogin_.text().isEmpty()
                && !usernameInputLogin_.text().isEmpty()) {
                sendButtonLogin_.click();
            }
        }
    }

    /*-------------------------------------------------------
                        Private Methods
    -------------------------------------------------------*/

    void Login::clearInputs() {
        usernameInputRegister_.clear();
        passwordInputRegister_.clear();

        usernameInputLogin_.clear();
        passwordInputLogin_.clear();
    }

    void Login::actionOnExit() {
        QMessageBox::StandardButton confirmExit;
        confirmExit = QMessageBox::question(
            this, "Quit", "Are you sure you want to qut the game ?",
            QMessageBox::Yes | QMessageBox::No);
        if (confirmExit == QMessageBox::Yes) {
            QApplication::quit();
        }
    }

    bool Login::isValidRegister() {
        errorMessage_.clear();

        if (usernameInputRegister_.text().length() < 4) {
            errorMessage_ = "The lenght of your username is too short ! The "
                            "username must have at least 4 characters";
            return false;
        }

        if (usernameInputRegister_.text().length() > 20) {
            errorMessage_ = "The lenght of your username is too long ! It must "
                            "have less than 20 characters";
        }

        for (const char c : usernameInputRegister_.text().toStdString()) {
            if (invalidChars.find(c) != std::string::npos || isspace(c)) {
                if (isprint(c)) {
                    errorMessage_ =
                        "Your username contains an invalid character : '"
                        + std::string(1, c) + "'";
                } else {
                    errorMessage_ =
                        "Your username contains an invalid character "
                        "with ASCII value "
                        + std::to_string(static_cast<int>(c)) + " !";
                }
                return false;
            }
        }

        if (passwordInputRegister_.text().isEmpty()) {
            errorMessage_ =
                "Your password is empty ! You must enter a valid password";
            return false;
        }

        return true;
    }

    void Login::setup() {
        QWidget *mainPage = new QWidget();
        QWidget *loginPage = new QWidget();
        QWidget *registerPage = new QWidget();

        QPushButton *exitButton = new QPushButton();
        exitButton->setAutoDefault(true);
        QPushButton *loginButton = new QPushButton();
        loginButton->setAutoDefault(true);
        QPushButton *registerButton = new QPushButton();
        registerButton->setAutoDefault(true);
        QPushButton *backButtonLogin = new QPushButton();
        backButtonLogin->setAutoDefault(true);
        QPushButton *backButtonRegister = new QPushButton();
        backButtonRegister->setAutoDefault(true);

        sendButtonRegister_.setAutoDefault(true);
        sendButtonLogin_.setAutoDefault(true);

        QCheckBox *showPasswordLogin = new QCheckBox();
        QCheckBox *showPasswordRegister = new QCheckBox();

        exitButton->setText("Exit");
        exitButton->setFixedWidth(INPUT_BUTTON_WIDTH);
        loginButton->setText("Login");
        loginButton->setFixedWidth(INPUT_BUTTON_WIDTH);
        registerButton->setText("Register");
        registerButton->setFixedWidth(INPUT_BUTTON_WIDTH);
        backButtonLogin->setText("Back");
        backButtonLogin->setFixedWidth(INPUT_BUTTON_WIDTH);
        backButtonRegister->setText("Back");
        backButtonRegister->setFixedWidth(INPUT_BUTTON_WIDTH);
        sendButtonRegister_.setText("Send");
        sendButtonRegister_.setFixedWidth(INPUT_BUTTON_WIDTH);
        sendButtonLogin_.setText("Send");
        sendButtonLogin_.setFixedWidth(INPUT_BUTTON_WIDTH);

        connect(exitButton, &QPushButton::clicked, this,
                &Login::on_ExitButton_clicked);
        connect(loginButton, &QPushButton::clicked, this,
                &Login::on_LoginButton_clicked);
        connect(registerButton, &QPushButton::clicked, this,
                &Login::on_RegisterButton_clicked);
        connect(backButtonLogin, &QPushButton::clicked, this,
                &Login::on_BackButtonLogin_clicked);
        connect(backButtonRegister, &QPushButton::clicked, this,
                &Login::on_BackButtonRegister_clicked);
        connect(&sendButtonRegister_, &QPushButton::clicked, this,
                &Login::on_SendButtonRegister_clicked);
        connect(&sendButtonLogin_, &QPushButton::clicked, this,
                &Login::on_SendButtonLogin_clicked);
        connect(&usernameInputRegister_, &QLineEdit::returnPressed, this,
                &Login::on_UsernameInputRegister_EnterPressed);
        connect(&usernameInputLogin_, &QLineEdit::returnPressed, this,
                &Login::on_UsernameInputLogin_EnterPressed);
        connect(&passwordInputRegister_, &QLineEdit::returnPressed, this,
                &Login::on_PasswordInputRegister_EnterPressed);
        connect(&passwordInputLogin_, &QLineEdit::returnPressed, this,
                &Login::on_PasswordInputLogin_EnterPressed);

        usernameInputRegister_.setAlignment(Qt::AlignCenter);
        usernameInputRegister_.setFixedWidth(INPUT_BUTTON_WIDTH);
        passwordInputRegister_.setAlignment(Qt::AlignCenter);
        passwordInputRegister_.setFixedWidth(INPUT_BUTTON_WIDTH);
        passwordInputRegister_.setEchoMode(QLineEdit::Password);
        usernameInputLogin_.setAlignment(Qt::AlignCenter);
        usernameInputLogin_.setFixedWidth(INPUT_BUTTON_WIDTH);
        passwordInputLogin_.setAlignment(Qt::AlignCenter);
        passwordInputLogin_.setFixedWidth(INPUT_BUTTON_WIDTH);
        passwordInputLogin_.setEchoMode(QLineEdit::Password);

        usernameInputRegister_.setPlaceholderText("Enter a username");
        passwordInputRegister_.setPlaceholderText("Enter a password");
        usernameInputLogin_.setPlaceholderText("Enter your username");
        passwordInputLogin_.setPlaceholderText("Enter your password");

        showPasswordLogin->setText("Show password");
        showPasswordRegister->setText("Show password");
        connect(showPasswordLogin, &QCheckBox::stateChanged, [&](int state) {
            if (state == Qt::Checked) {
                passwordInputLogin_.setEchoMode(QLineEdit::Normal);
            } else {
                passwordInputLogin_.setEchoMode(QLineEdit::Password);
            }
        });
        connect(showPasswordRegister, &QCheckBox::stateChanged,
                [&](int state) {
                    if (state == Qt::Checked) {
                        passwordInputRegister_.setEchoMode(QLineEdit::Normal);
                    } else {
                        passwordInputRegister_.setEchoMode(QLineEdit::Password);
                    }
                });

        // Create the main page
        mainPage = new QWidget();
        QVBoxLayout *mainLayout = new QVBoxLayout();
        mainLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                            QSizePolicy::Expanding));
        mainLayout->addWidget(
            createCenterBoldTitle("Welcome to Royal Tetris !"));
        mainLayout->addWidget(registerButton, 0, Qt::AlignCenter);
        mainLayout->addWidget(loginButton, 0, Qt::AlignCenter);
        mainLayout->addWidget(exitButton, 0, Qt::AlignCenter);
        mainLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                            QSizePolicy::Expanding));
        mainPage->setLayout(mainLayout);

        // Create the register page
        registerPage = new QWidget();
        QVBoxLayout *registerPageLayout = new QVBoxLayout();
        registerPageLayout->addItem(new QSpacerItem(
            20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
        registerPageLayout->addWidget(createCenterBoldTitle("Register"));
        registerPageLayout->addWidget(&usernameInputRegister_, 0,
                                      Qt::AlignCenter);
        registerPageLayout->addWidget(&passwordInputRegister_, 0,
                                      Qt::AlignCenter);
        registerPageLayout->addWidget(showPasswordRegister, 0,
                                      Qt::AlignCenter);
        registerPageLayout->addWidget(&sendButtonRegister_, 0, Qt::AlignCenter);
        registerPageLayout->addWidget(backButtonRegister, 0, Qt::AlignCenter);
        registerPageLayout->addItem(new QSpacerItem(
            20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
        registerPage->setLayout(registerPageLayout);

        // Create the login page
        loginPage = new QWidget();
        QVBoxLayout *loginPageLayout = new QVBoxLayout();
        loginPageLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                                 QSizePolicy::Expanding));
        loginPageLayout->addWidget(createCenterBoldTitle("Login"));
        loginPageLayout->addWidget(&usernameInputLogin_, 0, Qt::AlignCenter);
        loginPageLayout->addWidget(&passwordInputLogin_, 0, Qt::AlignCenter);
        loginPageLayout->addWidget(showPasswordLogin, 0, Qt::AlignCenter);
        loginPageLayout->addWidget(&sendButtonLogin_, 0, Qt::AlignCenter);
        loginPageLayout->addWidget(backButtonLogin, 0, Qt::AlignCenter);
        loginPageLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                                 QSizePolicy::Expanding));
        loginPage->setLayout(loginPageLayout);

        stackedWidget_.addWidget(mainPage);     // O
        stackedWidget_.addWidget(registerPage); // 1
        stackedWidget_.addWidget(loginPage);    // 2
    }

} // namespace GUI
