/*Authors : Ernest Jonas Rafaou*/

#include <profile_manager_gui.hpp>

#include "../../../core/controller/controller.hpp"
#include "../main_gui.hpp"
#include "../qt_config/qt_config.hpp"

ProfileManagerGui::ProfileManagerGui(Controller &controller, MainGui &mainGui, QWidget *parent) : controller_(controller), mainGui_(mainGui),  QWidget(parent)
{
    basicSetup();
}

ProfileManagerGui::basicSetup() {
    newUserName_ = new QLineEdit(this);
    newPassWord_ = new QLineEdit(this);

    submit_ = new QPushButton("Submit", this);
    back_ = new QPushButton("Back", this);

    layout->addWidget(newUserName_)
    layout->addWidget(newPassWord_)
    layout->addWidget(submit_)
    layout->addWidget(back_)

    setLayout(layout)
}

void ProfileManagerGui::onBack() {
    emit backToMainMenu();
}