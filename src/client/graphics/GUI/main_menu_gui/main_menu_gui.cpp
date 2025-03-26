#include "main_menu_gui.hpp"

#include <QApplication>
#include <QMessageBox>
#include <QPushButton>
#include <qpushbutton.h>
#include <qwidget.h>


MainMenuGui::MainMenuGui(Controller *controller, QWidget *parent)
    : QWidget(parent), controller_(controller) {}


void MainMenuGui::run() {
    setup();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(stackedWidget_);
    setLayout(layout);

    show();
}

void MainMenuGui::on_QuitGameButton_clicked()
{
    actionOnExit();
}

/*---------------------------------------------
                Private Methods
----------------------------------------------*/


void MainMenuGui::actionOnExit()
{
    QMessageBox::StandardButton confirmExit;
    confirmExit = QMessageBox::question(this, "Quit", "Are you sure you want to qut the game ?",
                                    QMessageBox::Yes | QMessageBox::No);
    if (confirmExit == QMessageBox::Yes) {
        QApplication::quit();
    }
}

void MainMenuGui::setup() {
    stackedWidget_ = new QStackedWidget();

    QPushButton *quitGameButton = new QPushButton("Quit Game");
    quitGameButton->setFixedWidth(500);

    connect(quitGameButton, &QPushButton::clicked, this, &MainMenuGui::on_QuitGameButton_clicked);

    QVBoxLayout *menu = new QVBoxLayout();
    menu->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    menu->addWidget(quitGameButton, 0, Qt::AlignCenter);
    menu->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    QWidget *layout = new QWidget();
    layout->setLayout(menu);

    stackedWidget_->addWidget(layout);
}

