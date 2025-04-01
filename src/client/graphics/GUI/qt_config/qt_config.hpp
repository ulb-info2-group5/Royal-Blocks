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

// enum class Color {
//     Black,
//     White,
//     Grey,
//     DarkBlue,
//     LightBlue,
//     Purple,
//     Red,
//     Orange,
//     Pink,
//     Green,
//     Yellow
// };

// enum class SelfCellType {
//     Active, 
//     Preview, 
//     Placed,
// };

// enum class CellSize : size_t {
//     Small = 4,
//     Big = 8,
// };

// constexpr size_t WIDTH_CANVAS_BIG = static_cast<size_t>(CellSize::Big) * 10,
//                  HEIGHT_CANVAS_BIG = static_cast<size_t>(CellSize::Big) * 20,
//                  WIDTH_CANVAS_SMALL = static_cast<size_t>(CellSize::Small) * 10,
//                  HEIGHT_CANVAS_SMALL =
//                      static_cast<size_t>(CellSize::Small) * 20;

// QColor getQColor(Color col, selfCellType selfCellType = SelfCellType::Placed);

#endif // QT_CONFIG_HPP