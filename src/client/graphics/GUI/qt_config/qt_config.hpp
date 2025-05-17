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

#ifndef GUI_QT_CONFIG_HPP
#define GUI_QT_CONFIG_HPP

#include <QLabel>
#include <QPalette>

#include <string_view>

namespace GUI {

    /*
     * @brief Create a centered bold title
     *
     * @param title The title to display
     * @return The QLabel created
     */
    QLabel *createCenterBoldTitle(const std::string_view &title);

    /*
     * @brief Create a dark palette for the qt window
     *
     * @return QPalette The dark palette
     */
    QPalette createDarkPalette();

    /*
     * @brief Create a light palette for the qt window
     *
     * @return QPalette The light palette
     */
    QPalette createLightPalette();

} // namespace GUI

#endif // GUI_QT_CONFIG_HPP
