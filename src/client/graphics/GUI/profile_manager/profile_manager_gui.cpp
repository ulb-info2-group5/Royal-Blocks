/*Authors : Ernest Jonas Rafaou*/

#include "profile_manager_gui.hpp"

#include "../../../core/controller/controller.hpp"
#include "../main_gui.hpp"
#include "../qt_config/qt_config.hpp"

ProfileManagerGui::ProfileManagerGui(Controller &controller, MainGui &mainGui, QWidget *parent) : controller_(controller), mainGui_(mainGui),  QWidget(parent)
{
    basicSetup();
}

void ProfileManagerGui::basicSetup() {
<<<<<<< HEAD
    submit_.setText("Submit");
    back_ .setText("Back");
=======
    QVBoxLayout *layout = new QVBoxLayout(this);

    newUserName_ = new QLineEdit(this);
    newPassWord_ = new QLineEdit(this);
>>>>>>> 5174def (profile manager)

    connect(&submit_, &QPushButton::clicked, this, &ProfileManagerGui::changeName);
    connect(&back_  , &QPushButton::clicked, this, &ProfileManagerGui::onBack);

<<<<<<< HEAD
    newUserName_.setPlaceholderText("New Username");
    newPassWord_.setPlaceholderText("New Password");
    newUserName_.setMaxLength(20);
    newPassWord_.setMaxLength(20);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Change Username and Password"));
    layout->addWidget(&newUserName_);
    layout->addWidget(&newPassWord_);
    layout->addWidget(&submit_);
    layout->addWidget(&back_);

    setLayout(layout);
=======
    layout->addWidget(newUserName_);
    layout->addWidget(newPassWord_);
    layout->addWidget(submit_);
    layout->addWidget(back_);

    setLayout(layout);

    connect(back_, &QPushButton::clicked, this, &ProfileManagerGui::onBack);
    
>>>>>>> 5174def (profile manager)
}

void ProfileManagerGui::onBack() {
    emit backToMainMenu();
}