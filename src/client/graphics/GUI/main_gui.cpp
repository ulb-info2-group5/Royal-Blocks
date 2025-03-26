#include "main_gui.hpp"

#include "../../core/controller/controller.hpp"
#include "ui_mainwindow.h"

#include "ranking.hpp"
#include "logingui.hpp"

#include <QMessageBox>
#include <QApplication>
#include <QTableWidget>
#include <QHeaderView>

MainGui::MainGui(QWidget *parent, Controller *controller)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , controller_(controller)
{
    ui->setupUi(this);

    // Créer l'objet LoginGui et l'ajouter au stackedWidget
    LoginGui *loginPage = new LoginGui(controller_);
    
    // Connecter le signal de connexion réussie à l'action de montrer le menu principal
    connect(loginPage, &LoginGui::loginSuccessful, this, &MainGui::showMainMenu);
    
    // Ajouter la page de login au stackedWidget de MainGui
    ui->stackedWidget->addWidget(loginPage);
    ui->stackedWidget->setCurrentWidget(loginPage);  // Afficher la page de login

    this->show();  // Afficher MainGui avec LoginGui comme premier écran

}

MainGui::~MainGui()
{
    delete ui;
}

void MainGui::forceRefresh()
{
    this->update();
}

void MainGui::showMainMenu()
{
    // Afficher le menu principal
    ui->stackedWidget->setCurrentIndex(3); // Main Menu page
}

void MainGui::on_QuitGameButton_clicked()
{
    actionOnExit();
}

void MainGui::on_RankingButton_clicked()
{
    // Créer l'objet Ranking et le connecter au slot
    Ranking *rankingPage = new Ranking(controller_);

    // Connecter le signal backToMainMenu à l'action de retour au menu principal
    connect(rankingPage, &Ranking::backToMainMenu, this, &MainGui::on_BackToMainMenu_clicked);

    // Ajouter la page du classement au stackedWidget et l'afficher
    ui->stackedWidget->addWidget(rankingPage);
    ui->stackedWidget->setCurrentWidget(rankingPage);
}

void MainGui::on_BackToMainMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(3); // Main Menu page
}

/*--------------------------------------------
                PRIVATE METHODS
--------------------------------------------*/

void MainGui::actionOnExit()
{
    QMessageBox::StandardButton confirmExit;
    confirmExit = QMessageBox::question(this, "Quit", "Are you sure you want to qut the game ?",
                                    QMessageBox::Yes | QMessageBox::No);
    if (confirmExit == QMessageBox::Yes) {
        QApplication::quit();
    }
}