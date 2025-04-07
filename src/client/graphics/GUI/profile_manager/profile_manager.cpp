/*Authors : Ernest Jonas Rafaou*/

#include "profile_manager.hpp"

#include "../../../core/controller/controller.hpp"
#include "../main_gui.hpp"

namespace GUI {

    ProfileManagerGui::ProfileManagerGui(Controller &controller,
                                         MainGui &mainGui, QWidget *parent)
        : QWidget(parent), controller_(controller), mainGui_(mainGui) {
        basicSetup();
    }

    void ProfileManagerGui::basicSetup() {
        submit_.setText("Submit");
        back_.setText("Back");

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
        layout->addWidget(new QLabel("Change Username and Password"));
        layout->addWidget(&newUserName_);
        layout->addWidget(&newPassWord_);
        layout->addWidget(showPasswordCheckBox, 0, Qt::AlignHCenter);
        layout->addWidget(&submit_);
        layout->addWidget(&back_);

        setLayout(layout);
    }

    void ProfileManagerGui::onBack() { emit backToMainMenu(); }

    void ProfileManagerGui::changePasswordUsername() {
        QString newUsername = newUserName_.text();
        QString newPassword = newPassWord_.text();

        // Verify if the fields are empty
        if (newUsername.isEmpty() || newPassword.isEmpty()) {
            QMessageBox::warning(this, "Error",
                                 "Please fill in all fields");
            return;
        }

        std::string newUsernameStd = newUsername.toStdString();
        std::string newPasswordStd = newPassword.toStdString();


        controller_.changeProfile(newUsernameStd, newPasswordStd);

        QMessageBox::information(this, "Info",
                                 "Your username and password have been changed");
                                 
        newUserName_.clear();
        newPassWord_.clear();
    }

} // namespace GUI
