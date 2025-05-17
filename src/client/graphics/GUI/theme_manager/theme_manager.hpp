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

#ifndef THEME_MANAGER_HPP
#define THEME_MANAGER_HPP

#include <QWidget>

namespace GUI {

    /**
     * @brief Allows to switch between light theme and dark theme.
     */
    class ThemeManager : public QWidget {
        Q_OBJECT

      private:
        /*
         * @brief Setup the Theme Manager Gui
         */
        void setup();

      public:
        ThemeManager(QWidget *parent = nullptr);

        ~ThemeManager() = default;

      signals:
        /*
         * @brief Signal emitted when the user click on the back button
         */
        void backToMainMenu();

        /*
         * @brief Signal emitted when the user click on the dark theme button
         */
        void applyDarkTheme();

        /*
         * @brief Signal emitted when the user click on the light theme button
         */
        void applyLightTheme();
    };
} // namespace GUI

#endif // THEME_MANAGER_HPP
