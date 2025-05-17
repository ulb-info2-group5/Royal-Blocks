/*
 * This file is part of Royal Blocks.
 *
 * Royal Blocks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Royal Blocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Royal Blocks.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "theme_manager.hpp"

#include "../qt_config/qt_config.hpp"

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QTimer>

namespace GUI { 
    ThemeManager::ThemeManager(QWidget *parent)
        : QWidget(parent) {
        setup();
    }

    void ThemeManager::setup() {
        QPushButton *lightThemeButton = new QPushButton("Light Theme", this);
        lightThemeButton->setFixedWidth(500);
        lightThemeButton->setAutoDefault(true);
        QPushButton *darkThemeButton = new QPushButton("Dark Theme", this);
        darkThemeButton->setFixedWidth(500);
        darkThemeButton->setAutoDefault(true);
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
                QTimer::singleShot(0, this, [this]() {
                    emit applyDarkTheme();
            }); 
            });
        connect(lightThemeButton, &QPushButton::clicked, this,
            [this]() {
                QTimer::singleShot(0, this, [this]() {
                    emit applyLightTheme();
            }); 
            });
        connect(backButton, &QPushButton::clicked, this,
            &ThemeManager::backToMainMenu);
    }
}