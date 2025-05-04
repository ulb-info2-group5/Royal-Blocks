#include "login.hpp"

#include "../../../core/controller/controller.hpp"
#include "../../../core/server_info/server_info.hpp"
#include "../qt_config/qt_config.hpp"

#include <QApplication>
#include <QCheckBox>
#include <QMessageBox>
#include <QTimer>
#include <QVBoxLayout>
#include <QValidator>

namespace GUI {

    const std::string invalidChars = "!@#$%^&*()+=[]{}|\\\"'<>?/°;,~:²³§_£";
    constexpr int INPUT_BUTTON_WIDTH = 500;
    constexpr char NO_CONNECTED_CHAR_NORMAL[] =
        "<span style='color: red; font-weight: "
        "bold;'>Connection to the server failed.</span><br>"
        "Please enter a valid IP address and port in the <span "
        "style='color: #007acc;'><b>Choose IP and Port</b></span> menu "
        "or make sure that the server is currently online.";
    constexpr char NO_CONNECTED_CHAR_MAINPAGE[] =
        "<span style='color: red; font-weight: "
        "bold;'>Connection to the server failed.</span><br>"
        "Please enter a valid <strong>IP address</strong> and <strong>port</strong> in the <span "
        "style='color: #007acc;'><b>Choose IP and Port</b></span> menu<br>"
        "or make sure that the server is currently online";
    constexpr char CONNECTED_CHAR[] =
        "<span style='color: green; font-weight: bold;'>Connection made to the "
        "server</span> "
        "with IP address : <span style='color: #007acc;'><b>";

    Login::Login(Controller &controller, QWidget *parent)
        : QWidget(parent), controller_(controller), loginSuccess_(false) {}

    void Login::run() {
        setup();

        QVBoxLayout *layout = new QVBoxLayout();
        layout->addWidget(&stackedWidget_);
        setLayout(layout);

        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [this, timer]() {
            if (loginSuccess_) {
                timer->stop();
                timer->deleteLater();
            } else {
                updateConnectedMessage();
            }
        });
        timer->start(1000); // 3000 ms
    }

    void Login::on_ExitButton_clicked() { actionOnExit(); }

    void Login::on_LoginButton_clicked() {
        stackedWidget_.setCurrentIndex(2); // Login page
    }

    void Login::on_RegisterButton_clicked() {
        stackedWidget_.setCurrentIndex(1); // Register page
    }

    void Login::on_BackButton_clicked() {
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

        // Thread to check if registration is successful
        std::thread loginThread = std::thread([&]() {
            for (int i = 0; i < 10; ++i) { // 1 seconds limit (20 * 100ms)
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                if (controller_.getAuthState()
                    == Controller::AuthState::Authenticated) {
                    loginSuccess_ = true;
                    return;
                }
            }
        });

        if (loginThread.joinable()) {
            loginThread.join();
        }

        clearInputs();

        if (loginSuccess_) {
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

    void Login::on_ChooseIpPortButton_clicked() {
        config::ServerInfo serverInfo = controller_.getServerInfo();
        ipInput_.setText(QString::fromStdString(serverInfo.ip));
        portInput_.setText(QString::number(serverInfo.port));
        stackedWidget_.setCurrentIndex(3); // Choose IP and port page
    }

    void Login::on_ConnectButton_clicked() {
        QString ip = ipInput_.text();
        QString port = portInput_.text();

        if (ip.isEmpty() || port.isEmpty()) {
            QMessageBox::warning(this, "Connection failed",
                                 "Please enter a valid IP and Port.");
            return;
        }

        bool ok;
        int portInt = port.toInt(&ok);
        if (!ok || portInt < 1
            || portInt > std::numeric_limits<uint16_t>::max()) {
            QMessageBox::warning(this, "Connection failed",
                                 "Please enter a valid port (1 - 65535).");
            return;
        }

        config::ServerInfo serverInfo;
        serverInfo.ip = ip.toStdString();
        serverInfo.port = portInt;
        controller_.setServerInfo(serverInfo);

        std::thread waitThread([&]() {
            const int maxWaitTimeMs = 2000;
            const int checkIntervalMs = 100;
            int waited = 0;
            while (waited < maxWaitTimeMs) {
                std::this_thread::sleep_for(
                    std::chrono::milliseconds(checkIntervalMs));
                waited += checkIntervalMs;
                if (controller_.isConnected()) {
                    break;
                }
            }
        });
        waitThread.join();
        if (controller_.isConnected()) {
            connectionToServerLabel_.setText(getConnectedMessage());
        } else {
            connectionToServerLabel_.setText(NO_CONNECTED_CHAR_MAINPAGE);
            QMessageBox::warning(this, "Connection failed",
                                 NO_CONNECTED_CHAR_NORMAL);
            return;
        }

        QMessageBox::information(
            this, "Connection successful",
            "<span style='color: green; font-weight: bold;'>Connection "
            "successful !</span><br>\nYou are now connected to the Royal "
            "Tetris Server with the IP : "
                + ip + " and the Port : " + port + ".");

        updateConnectedMessage();
        stackedWidget_.setCurrentIndex(0); // Main page
    }

    void Login::setup() {
        QWidget *mainPage = new QWidget(&stackedWidget_);
        QWidget *loginPage = new QWidget(&stackedWidget_);
        QWidget *registerPage = new QWidget(&stackedWidget_);
        QWidget *chooseIpPortPage = new QWidget(&stackedWidget_);

        QPushButton *registerButton = new QPushButton(mainPage);
        registerButton->setAutoDefault(true);
        QPushButton *loginButton = new QPushButton(mainPage);
        loginButton->setAutoDefault(true);
        QPushButton *chooseIpPortButton = new QPushButton(mainPage);
        chooseIpPortButton->setAutoDefault(true);
        QPushButton *exitButton = new QPushButton(mainPage);
        exitButton->setAutoDefault(true);

        usernameInputLogin_.setParent(loginPage);
        passwordInputLogin_.setParent(loginPage);
        QCheckBox *showPasswordLogin = new QCheckBox(loginPage);
        sendButtonLogin_.setParent(loginPage);
        sendButtonLogin_.setAutoDefault(true);
        QPushButton *backButtonLogin = new QPushButton(loginPage);
        backButtonLogin->setAutoDefault(true);

        usernameInputRegister_.setParent(registerPage);
        passwordInputRegister_.setParent(registerPage);
        QCheckBox *showPasswordRegister = new QCheckBox(registerPage);
        sendButtonRegister_.setParent(registerPage);
        sendButtonRegister_.setAutoDefault(true);
        QPushButton *backButtonRegister = new QPushButton(registerPage);
        backButtonRegister->setAutoDefault(true);

        ipInput_.setParent(chooseIpPortPage);
        portInput_.setParent(chooseIpPortPage);
        QPushButton *connectButton = new QPushButton(chooseIpPortPage);
        connectButton->setAutoDefault(true);
        QPushButton *backButtonIpPortMenu = new QPushButton(chooseIpPortPage);
        backButtonIpPortMenu->setAutoDefault(true);

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

        /*---------CHOOSE IP AND PORT MENU---------*/
        backButtonIpPortMenu->setText("Back");
        backButtonIpPortMenu->setFixedWidth(INPUT_BUTTON_WIDTH);
        connectButton->setText("Connect to server");
        connectButton->setFixedWidth(INPUT_BUTTON_WIDTH);
        chooseIpPortButton->setText("Choose IP and Port");
        chooseIpPortButton->setFixedWidth(INPUT_BUTTON_WIDTH);

        ipInput_.setAlignment(Qt::AlignCenter);
        ipInput_.setFixedWidth(INPUT_BUTTON_WIDTH);
        portInput_.setAlignment(Qt::AlignCenter);
        portInput_.setFixedWidth(INPUT_BUTTON_WIDTH);
        QValidator *validator =
            new QIntValidator(1, std::numeric_limits<uint16_t>::max(), this);
        portInput_.setValidator(validator);

        connect(backButtonIpPortMenu, &QPushButton::clicked, this,
                &Login::on_BackButton_clicked);
        connect(connectButton, &QPushButton::clicked, this,
                &Login::on_ConnectButton_clicked);
        connect(chooseIpPortButton, &QPushButton::clicked, this,
                &Login::on_ChooseIpPortButton_clicked);

        QVBoxLayout *chooseIpPortPageLayout = new QVBoxLayout();
        chooseIpPortPageLayout->addItem(new QSpacerItem(
            20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
        chooseIpPortPageLayout->addWidget(
            createCenterBoldTitle("Choose IP and Port of the server"));
        chooseIpPortPageLayout->addWidget(new QLabel("IP : "), 0,
                                          Qt::AlignCenter);
        chooseIpPortPageLayout->addWidget(&ipInput_, 0, Qt::AlignCenter);
        chooseIpPortPageLayout->addWidget(new QLabel("Port : "), 0,
                                          Qt::AlignCenter);
        chooseIpPortPageLayout->addWidget(&portInput_, 0, Qt::AlignCenter);
        chooseIpPortPageLayout->addWidget(connectButton, 0, Qt::AlignCenter);
        chooseIpPortPageLayout->addWidget(backButtonIpPortMenu, 0,
                                          Qt::AlignCenter);
        chooseIpPortPageLayout->addItem(new QSpacerItem(
            20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
        chooseIpPortPage->setLayout(chooseIpPortPageLayout);

        /*-------------------------------------------------------------------------*/

        connect(exitButton, &QPushButton::clicked, this,
                &Login::on_ExitButton_clicked);
        connect(loginButton, &QPushButton::clicked, this,
                &Login::on_LoginButton_clicked);
        connect(registerButton, &QPushButton::clicked, this,
                &Login::on_RegisterButton_clicked);
        connect(backButtonLogin, &QPushButton::clicked, this,
                &Login::on_BackButton_clicked);
        connect(backButtonRegister, &QPushButton::clicked, this,
                &Login::on_BackButton_clicked);
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
        connect(showPasswordRegister, &QCheckBox::stateChanged, [&](int state) {
            if (state == Qt::Checked) {
                passwordInputRegister_.setEchoMode(QLineEdit::Normal);
            } else {
                passwordInputRegister_.setEchoMode(QLineEdit::Password);
            }
        });

        // Create the main page
        connectionToServerLabel_.setAlignment(Qt::AlignHCenter);

        QVBoxLayout *mainLayout = new QVBoxLayout();
        mainLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                            QSizePolicy::Expanding));
        mainLayout->addWidget(
            createCenterBoldTitle("Welcome to Royal Tetris !"));
        mainLayout->addWidget(&connectionToServerLabel_, 0, Qt::AlignCenter);
        mainLayout->addWidget(registerButton, 0, Qt::AlignCenter);
        mainLayout->addWidget(loginButton, 0, Qt::AlignCenter);
        mainLayout->addWidget(chooseIpPortButton, 0, Qt::AlignCenter);
        mainLayout->addWidget(exitButton, 0, Qt::AlignCenter);
        mainLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                            QSizePolicy::Expanding));
        mainPage->setLayout(mainLayout);

        // Create the register page
        QVBoxLayout *registerPageLayout = new QVBoxLayout();
        registerPageLayout->addItem(new QSpacerItem(
            20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
        registerPageLayout->addWidget(createCenterBoldTitle("Register"));
        registerPageLayout->addWidget(&usernameInputRegister_, 0,
                                      Qt::AlignCenter);
        registerPageLayout->addWidget(&passwordInputRegister_, 0,
                                      Qt::AlignCenter);
        registerPageLayout->addWidget(showPasswordRegister, 0, Qt::AlignCenter);
        registerPageLayout->addWidget(&sendButtonRegister_, 0, Qt::AlignCenter);
        registerPageLayout->addWidget(backButtonRegister, 0, Qt::AlignCenter);
        registerPageLayout->addItem(new QSpacerItem(
            20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
        registerPage->setLayout(registerPageLayout);

        // Create the login page
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

        stackedWidget_.addWidget(mainPage);         // O
        stackedWidget_.addWidget(registerPage);     // 1
        stackedWidget_.addWidget(loginPage);        // 2
        stackedWidget_.addWidget(chooseIpPortPage); // 3

        updateConnectedMessage();
    }

    QString Login::getConnectedMessage() const {
        QString message =
            CONNECTED_CHAR
            + QString::fromStdString(std::string(controller_.getServerIp()))
            + "</b></span> and Port : <span style='color: #007acc;'><b>"
            + QString::number(controller_.getServerPort()) + "</b></span>";
        return message;
    }

    void Login::updateConnectedMessage() {
        if (controller_.isConnected()) {
            connectionToServerLabel_.setText(getConnectedMessage());
        } else {
            connectionToServerLabel_.setText(NO_CONNECTED_CHAR_MAINPAGE);
        }
    }

} // namespace GUI

