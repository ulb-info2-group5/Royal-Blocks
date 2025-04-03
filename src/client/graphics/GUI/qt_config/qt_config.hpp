#ifndef QT_CONFIG_HPP
#define QT_CONFIG_HPP

#include <QLabel>
#include <QColor> 

#include <string_view>


/*
* @brief Create a centered bold title
* 
* @param title The title to display
* @return The QLabel created
*/
QLabel *createCenterBoldTitle(const std::string_view &title);


#endif // QT_CONFIG_HPP