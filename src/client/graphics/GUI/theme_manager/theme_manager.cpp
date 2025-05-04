#include "theme_manager.hpp"

#include "../qt_config/qt_config.hpp"

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <qpushbutton.h>

namespace GUI { 
    ThemeManager::ThemeManager(QWidget *parent)
        : QWidget(parent) {
        setup();
    }

    void ThemeManager::setup() {
        QPushButton *darkThemeButton = new QPushButton("Dark Theme", this);
        darkThemeButton->setFixedWidth(500);
        darkThemeButton->setAutoDefault(true);
        QPushButton *lightThemeButton = new QPushButton("Light Theme", this);
        lightThemeButton->setFixedWidth(500);
        lightThemeButton->setAutoDefault(true);
        QPushButton *backButton = new QPushButton("Back", this);
        backButton->setFixedWidth(500);
        backButton->setAutoDefault(true);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
            QSizePolicy::Expanding));   
        layout->addWidget(createCenterBoldTitle("Theme Manager"));
        layout->addWidget(lightThemeButton, 0, Qt::AlignCenter);
        layout->addWidget(darkThemeButton, 0, Qt::AlignCenter);
        layout->addWidget(backButton, 0, Qt::AlignCenter);
        layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
            QSizePolicy::Expanding));

        this->setLayout(layout);

        connect(darkThemeButton, &QPushButton::clicked, this,
            [this]() {
                emit applyDarkTheme();
            });
        connect(lightThemeButton, &QPushButton::clicked, this,
            [this]() {
                emit applyLightTheme();
            });
        connect(backButton, &QPushButton::clicked, this,
            &ThemeManager::backToMainMenu);
    }
}