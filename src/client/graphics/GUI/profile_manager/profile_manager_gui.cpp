/*Authors : Ernest Jonas Rafaou*/

#include "profile_manager_gui.hpp"

#include "../../../core/controller/controller.hpp"
#include "../main_gui.hpp"

ProfileManagerGui::ProfileManagerGui(Controller &controller, MainGui &mainGui, QWidget *parent) 
    : controller_(controller), mainGui_(mainGui),  QWidget(parent)
{
    basicSetup();
}

void ProfileManagerGui::basicSetup() {
    submit_.setText("Submit");
    back_ .setText("Back");

    connect(&submit_, &QPushButton::clicked, this, &ProfileManagerGui::changePasswordUsername);
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

void ProfileManagerGui::changePasswordUsername(){
    QString newUsername = newUserName_.text();
    QString newPassword = newPassWord_.text();

    // Vérifier que les champs ne sont pas vides
    if (newUsername.isEmpty() || newPassword.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }

    // Conversion de QString en std::string
    std::string newUsernameStd = newUsername.toStdString();
    std::string newPasswordStd = newPassword.toStdString();

    // Passer les informations au contrôleur (par exemple, à une méthode de mise à jour du profil)
    controller_.changeProfile(newUsernameStd, newPasswordStd);

    // Affiche le message de confirmation
    QMessageBox::information(this, "Info", "Votre nom d'utilisateur et votre mot de passe ont été changés avec succès");
}