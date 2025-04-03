#include "logingui.hpp"

#include "../qt_config/qt_config.hpp"
#include "../../../core/controller/controller.hpp"

#include <QVBoxLayout>
#include <QCheckBox>

const std::string invalidChars = "!@#$%^&*()+=[]{}|\\\"'<>?/°;,~:²³§_£";
constexpr int INPUT_BUTTON_WIDTH = 500;

LoginGui::LoginGui(Controller &controller, QWidget *parent)
    : controller_(controller), QWidget(parent) {}

void LoginGui::run() {
    setup();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(&stackedWidget_);
    setLayout(layout);

    show();
}

void LoginGui::on_ExitButton_clicked() {
    actionOnExit();
}


void LoginGui::on_LoginButton_clicked() {
    stackedWidget_.setCurrentIndex(2); // Login page
}


void LoginGui::on_RegisterButton_clicked() {
    stackedWidget_.setCurrentIndex(1); // Register page
}


void LoginGui::on_BackButtonLogin_clicked() {
    clearInputs();
    stackedWidget_.setCurrentIndex(0); // Main page
}


void LoginGui::on_BackButtonRegister_clicked() {
    clearInputs();
    stackedWidget_.setCurrentIndex(0); // Main page
}


void LoginGui::on_SendButtonRegister_clicked() {
    QString username = usernameInputRegister_.text();
    QString password = passwordInputRegister_.text();

    if (!isValidRegister()) {
        clearInputs();
        QMessageBox::warning(this, "Register failed", errorMessage_.c_str());
        return;
    }

    controller_.tryRegister(username.toStdString(), password.toStdString());

    bool registerSuccess = false;

    // Thread to check if registration is successful
    std::thread loginThread = std::thread([&]() {
        for (int i = 0; i < 20;
            ++i) { // 2 seconds limit (20 * 100ms)
            std::this_thread::sleep_for(
                std::chrono::milliseconds(100));
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
        QMessageBox::information(this, "Register successful", "You have successfully registered.");
        stackedWidget_.setCurrentIndex(2); // Login page

    }

    else {
        QMessageBox::warning(this, "Register failed", "This username is already taken.");
    }
}

void LoginGui::on_SendButtonLogin_clicked() {
    QString username = usernameInputLogin_.text();
    QString password = passwordInputLogin_.text();

    controller_.tryLogin(username.toStdString(), password.toStdString());

    bool loginSuccess = false;

    // Thread to check if registration is successful
    std::thread loginThread = std::thread([&]() {
        for (int i = 0; i < 20;
            ++i) { // 2 seconds limit (20 * 100ms)
            std::this_thread::sleep_for(
                std::chrono::milliseconds(100));
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
        QMessageBox::warning(this, "Login failed", "Your username or password is incorrect.");
    }
}

void LoginGui::on_UsernameInputRegister_EnterPressed() {
    if (usernameInputRegister_.hasFocus()) {
        passwordInputRegister_.setFocus();
    }
}

void LoginGui::on_UsernameInputLogin_EnterPressed() {
    if (usernameInputLogin_.hasFocus()) {
        passwordInputLogin_.setFocus();
    }
}

void LoginGui::on_PasswordInputRegister_EnterPressed() {
    if (passwordInputRegister_.hasFocus()) {
        if (!passwordInputRegister_.text().isEmpty() && !usernameInputRegister_.text().isEmpty()) {
            sendButtonRegister_.click();
        }
    }
}

void LoginGui::on_PasswordInputLogin_EnterPressed() {
    if (passwordInputLogin_.hasFocus()) {
        if (!passwordInputLogin_.text().isEmpty() && !usernameInputLogin_.text().isEmpty()) {
            sendButtonLogin_.click();
        }
    }
}


/*-------------------------------------------------------
                    Private Methods
-------------------------------------------------------*/


void LoginGui::clearInputs(){
    usernameInputRegister_.clear();
    passwordInputRegister_.clear();

    usernameInputLogin_.clear();
    passwordInputLogin_.clear();
}

void LoginGui::actionOnExit() {
    QMessageBox::StandardButton confirmExit;
    confirmExit = QMessageBox::question(this, "Quit", "Are you sure you want to qut the game ?",
                                    QMessageBox::Yes | QMessageBox::No);
    if (confirmExit == QMessageBox::Yes) {
        QApplication::quit();
    }
}

bool LoginGui::isValidRegister() {
    errorMessage_.clear();

    if (usernameInputRegister_.text().length() < 4) {
        errorMessage_ = "The lenght of your username is too short ! The username must have at least 4 characters";
        return false;
    }

    if (usernameInputRegister_.text().length() > 20) {
        errorMessage_ = "The lenght of your username is too long ! It must have less than 20 characters";
    }

    for (const char c : usernameInputRegister_.text().toStdString()) {
        if (invalidChars.find(c) != std::string::npos || isspace(c)) {
            if (isprint(c)) {
                errorMessage_ = "Your username contains an invalid character : '" + std::string(1, c) + "'";
            } else  {
                errorMessage_ = "Your username contains an invalid character with ASCII value " + std::to_string(static_cast<int>(c)) + " !";
            }
            return false;
        }
    }

    if (passwordInputRegister_.text().isEmpty()) {
        errorMessage_ = "Your password is empty ! You must enter a valid password";
        return false;
    }

    return true;
}

void LoginGui::setup() {
    QWidget *mainPage_ = new QWidget();
    QWidget *loginPage_ = new QWidget();
    QWidget *registerPage_ = new QWidget();

    QPushButton *exitButton_ = new QPushButton();
    QPushButton *loginButton_ = new QPushButton();
    QPushButton *registerButton_ = new QPushButton();
    QPushButton *backButtonLogin_ = new QPushButton();
    QPushButton *backButtonRegister_ = new QPushButton();

    QCheckBox *showPasswordLogin_ = new QCheckBox();
    QCheckBox *showPasswordRegister_ = new QCheckBox();

    exitButton_->setText("Exit");
    exitButton_->setFixedWidth(INPUT_BUTTON_WIDTH);
    loginButton_->setText("Login");
    loginButton_->setFixedWidth(INPUT_BUTTON_WIDTH);
    registerButton_->setText("Register");
    registerButton_->setFixedWidth(INPUT_BUTTON_WIDTH);
    backButtonLogin_->setText("Back");
    backButtonLogin_->setFixedWidth(INPUT_BUTTON_WIDTH);
    backButtonRegister_->setText("Back");
    backButtonRegister_->setFixedWidth(INPUT_BUTTON_WIDTH);
    sendButtonRegister_.setText("Send");
    sendButtonRegister_.setFixedWidth(INPUT_BUTTON_WIDTH);
    sendButtonLogin_.setText("Send");
    sendButtonLogin_.setFixedWidth(INPUT_BUTTON_WIDTH);

    connect(exitButton_, &QPushButton::clicked, this, &LoginGui::on_ExitButton_clicked);
    connect(loginButton_, &QPushButton::clicked, this, &LoginGui::on_LoginButton_clicked);
    connect(registerButton_, &QPushButton::clicked, this, &LoginGui::on_RegisterButton_clicked);
    connect(backButtonLogin_, &QPushButton::clicked, this, &LoginGui::on_BackButtonLogin_clicked);
    connect(backButtonRegister_, &QPushButton::clicked, this, &LoginGui::on_BackButtonRegister_clicked);
    connect(&sendButtonRegister_, &QPushButton::clicked, this, &LoginGui::on_SendButtonRegister_clicked);
    connect(&sendButtonLogin_, &QPushButton::clicked, this, &LoginGui::on_SendButtonLogin_clicked);
    connect(&usernameInputRegister_, &QLineEdit::returnPressed, this, &LoginGui::on_UsernameInputRegister_EnterPressed);
    connect(&usernameInputLogin_, &QLineEdit::returnPressed, this, &LoginGui::on_UsernameInputLogin_EnterPressed);
    connect(&passwordInputRegister_, &QLineEdit::returnPressed, this, &LoginGui::on_PasswordInputRegister_EnterPressed);
    connect(&passwordInputLogin_, &QLineEdit::returnPressed, this, &LoginGui::on_PasswordInputLogin_EnterPressed);

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

    showPasswordLogin_->setText("Show password");
    showPasswordRegister_->setText("Show password");
    connect(showPasswordLogin_, &QCheckBox::stateChanged, [&](int state) {
        if (state == Qt::Checked) {
            passwordInputLogin_.setEchoMode(QLineEdit::Normal);
        } else {
            passwordInputLogin_.setEchoMode(QLineEdit::Password);
        }
    });
    connect(showPasswordRegister_, &QCheckBox::stateChanged, [&](int state) {
        if (state == Qt::Checked) {
            passwordInputRegister_.setEchoMode(QLineEdit::Normal);
        } else {
            passwordInputRegister_.setEchoMode(QLineEdit::Password);
        }
    });


    // Create the main page
    mainPage_ = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addWidget(createCenterBoldTitle("Welcome to Royal Tetris !"));
    mainLayout->addWidget(registerButton_, 0, Qt::AlignCenter);
    mainLayout->addWidget(loginButton_, 0, Qt::AlignCenter);
    mainLayout->addWidget(exitButton_, 0, Qt::AlignCenter);
    mainLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainPage_->setLayout(mainLayout);


    // Create the register page
    registerPage_ = new QWidget();
    QVBoxLayout *registerPageLayout = new QVBoxLayout();
    registerPageLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    registerPageLayout->addWidget(createCenterBoldTitle("Register"));
    registerPageLayout->addWidget(&usernameInputRegister_, 0, Qt::AlignCenter);
    registerPageLayout->addWidget(&passwordInputRegister_, 0, Qt::AlignCenter);
    registerPageLayout->addWidget(showPasswordRegister_, 0, Qt::AlignCenter);
    registerPageLayout->addWidget(&sendButtonRegister_, 0, Qt::AlignCenter);
    registerPageLayout->addWidget(backButtonRegister_, 0, Qt::AlignCenter);
    registerPageLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    registerPage_->setLayout(registerPageLayout);


    // Create the login page
    loginPage_ = new QWidget();
    QVBoxLayout *loginPageLayout = new QVBoxLayout();
    loginPageLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    loginPageLayout->addWidget(createCenterBoldTitle("Login"));
    loginPageLayout->addWidget(&usernameInputLogin_, 0, Qt::AlignCenter);
    loginPageLayout->addWidget(&passwordInputLogin_, 0, Qt::AlignCenter);
    loginPageLayout->addWidget(showPasswordLogin_, 0, Qt::AlignCenter);
    loginPageLayout->addWidget(&sendButtonLogin_, 0, Qt::AlignCenter);
    loginPageLayout->addWidget(backButtonLogin_, 0, Qt::AlignCenter);
    loginPageLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    loginPage_->setLayout(loginPageLayout);


    stackedWidget_.addWidget(mainPage_); // O 
    stackedWidget_.addWidget(registerPage_); // 1 
    stackedWidget_.addWidget(loginPage_); // 2
}
