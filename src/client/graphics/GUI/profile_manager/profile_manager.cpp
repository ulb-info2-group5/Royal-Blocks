/*Authors : Ernest Jonas Rafaou*/

#include "profile_manager.hpp"

#include "../../../core/controller/controller.hpp"
#include "../main_gui.hpp"
#include "../qt_config/qt_config.hpp"

namespace GUI {
    const std::string invalidChars = "!@#$%^&*()+=[]{}|\\\"'<>?/°;,~:²³§_£";
    constexpr int INPUT_BUTTON_WIDTH = 500;

    ProfileManagerGui::ProfileManagerGui(Controller &controller,
                                         MainGui &mainGui, QWidget *parent)
        : QWidget(parent), controller_(controller), mainGui_(mainGui) {
        basicSetup();
    }

    void ProfileManagerGui::basicSetup() {
        submit_.setText("Submit");
        back_.setText("Back");
        submit_.setFixedWidth(INPUT_BUTTON_WIDTH);
        back_.setFixedWidth(INPUT_BUTTON_WIDTH);

        connect(&submit_, &QPushButton::clicked, this,
                &ProfileManagerGui::changePasswordUsername);
        connect(&back_, &QPushButton::clicked, this,
                &ProfileManagerGui::onBack);

        newUserName_.setPlaceholderText("New Username");
        newPassWord_.setPlaceholderText("New Password");
        newPassWord_.setEchoMode(
            QLineEdit::Password); // Hide the password by default
        newUserName_.setMaxLength(20);
        newPassWord_.setMaxLength(20);
        newUserName_.setAlignment(Qt::AlignCenter);
        newPassWord_.setAlignment(Qt::AlignCenter);
        newUserName_.setFixedWidth(INPUT_BUTTON_WIDTH);
        newPassWord_.setFixedWidth(INPUT_BUTTON_WIDTH);

        connect(&newUserName_, &QLineEdit::returnPressed, this,
                [&]() { newPassWord_.setFocus(); });
        connect(&newPassWord_, &QLineEdit::returnPressed, this,
                [&]() { 
                    if (!newPassWord_.text().isEmpty() && !newUserName_.text().isEmpty()) {
                        submit_.click();
                    }});

        // Create a checkbox to show/hide the password
        QCheckBox *showPasswordCheckBox = new QCheckBox("Show Password", this);

        // Connect the checkbox to the password field
        connect(showPasswordCheckBox, &QCheckBox::toggled, this,
                [this](bool checked) {
                    if (checked) {
                        newPassWord_.setEchoMode(
                            QLineEdit::Normal); // Show the password
                    } else {
                        newPassWord_.setEchoMode(
                            QLineEdit::Password); // Hide the password
                    }
                });

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                        QSizePolicy::Expanding));
        layout->addWidget(createCenterBoldTitle("Change Username and Password"), 0,
                          Qt::AlignHCenter);
        layout->addWidget(&newUserName_, 0, Qt::AlignHCenter);
        layout->addWidget(&newPassWord_, 0, Qt::AlignHCenter);
        layout->addWidget(showPasswordCheckBox, 0, Qt::AlignHCenter);
        layout->addWidget(&submit_, 0, Qt::AlignHCenter);
        layout->addWidget(&back_, 0, Qt::AlignHCenter);
        layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                        QSizePolicy::Expanding));

        setLayout(layout);
    }

    void ProfileManagerGui::onBack() { emit backToMainMenu(); }

    void ProfileManagerGui::changePasswordUsername() {
        if (!isValidUsernamePassword()) {
            QMessageBox::warning(this, "NAccount Update Failed", errorMessage_.c_str());
            return;
        }

        std::string newUsernameStd = newUserName_.text().toStdString();
        std::string newPasswordStd = newPassWord_.text().toStdString();

        controller_.changeProfile(newUsernameStd, newPasswordStd);

        QMessageBox::information(this, "Info",
                                 "Your username and password have been changed");

        newUserName_.clear();
        newPassWord_.clear();
    }

    bool ProfileManagerGui::isValidUsernamePassword() {
        errorMessage_.clear();

        if (newUserName_.text().length() < 4) {
            errorMessage_ = "The lenght of your username is too short ! The "
                            "username must have at least 4 characters";
            return false;
        }

        if (newUserName_.text().length() > 20) {
            errorMessage_ = "The lenght of your username is too long ! It must "
                            "have less than 20 characters";
        }

        for (const char c : newUserName_.text().toStdString()) {
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

        if (newPassWord_.text().isEmpty()) {
            errorMessage_ =
                "Your password is empty ! You must enter a valid password";
            return false;
        }

        return true;
    }

} // namespace GUI
