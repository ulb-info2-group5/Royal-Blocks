#ifndef GUI_QT_CONFIG_HPP
#define GUI_QT_CONFIG_HPP

#include <QLabel>

#include <string_view>

namespace GUI {

    /*
     * @brief Create a centered bold title
     *
     * @param title The title to display
     * @return The QLabel created
     */
    QLabel *createCenterBoldTitle(const std::string_view &title);

} // namespace GUI

#endif // GUI_QT_CONFIG_HPP
