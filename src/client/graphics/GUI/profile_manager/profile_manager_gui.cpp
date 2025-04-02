/*Authors : Ernest Jonas Rafaou*/

#include "profile_manager_gui.hpp"

#include "../../../core/controller/controller.hpp"
#include "../main_gui.hpp"

ProfileManagerGui::ProfileManagerGui(Controller &controller, MainGui &mainGui, QWidget *parent) : controller_(controller), mainGui_(mainGui),  QWidget(parent)
{
    basicSetup();
}

void ProfileManagerGui::basicSetup() {
    submit_.setText("Submit");
    back_ .setText("Back");

    connect(&back_, &QPushButton::clicked, this, &ProfileManagerGui::onBack);

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
}

void ProfileManagerGui::onBack() {
    emit backToMainMenu();
}