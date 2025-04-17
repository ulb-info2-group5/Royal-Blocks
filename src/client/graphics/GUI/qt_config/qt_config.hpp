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
