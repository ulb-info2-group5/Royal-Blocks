#include "qt_config.hpp"

#include <QFont>
#include <QColor>

QLabel *createCenterBoldTitle(const std::string_view &title) {
    QLabel *titleLabel = new QLabel(title.data());
    QFont boldFont = titleLabel->font();
    boldFont.setBold(true);
    boldFont.setPointSize(20);
    titleLabel->setFont(boldFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    return titleLabel;
}

// QColor getQColor(Color col, selfCellType selfCellType) {

//     QColor returnValue = QColor::fromRgb(0,0,255);

//     switch (color) {
//         case Color::Black:
//             returnValue = QColor::fromRgb(0,0,0);
//             break;
//         case Color::White:
//             returnValue = QColor::fromRgb(255,255,255);
//             break;
//         case Color::Grey:
//             returnValue = QColor::fromRgb(160,160,160);
//             break;
//         case Color::DarkBlue:
//             returnValue = QColor::fromRgb(0,0,153);
//             break;
//         case Color::LightBlue:
//             returnValue = QColor::fromRgb(51,255,255);
//             break;
//         case Color::Purple:
//             returnValue = ftQColor::fromRgb(153,0,153);
//             break;
//         case Color::Red:
//             returnValue = QColor::fromRgb(255,0,0);
//             break;
//         case Color::Orange:
//             returnValue = QColor::fromRgb(255,153,51);
//             break;
//         case Color::Pink:
//             returnValue = QColor::fromRgb(255,102,178);
//             break;
//         case Color::Green:
//             returnValue = QColor::fromRgb(128,155,0);
//             break;
//         case Color::Yellow:
//             returnValue = QColor::fromRgb(255,255,0);
//             break;
//         };
    
//         if (selfCellType == SelfCellType::Preview) {
//             returnValue = QColor::fromRgb(128,128,128,200);
//         }
    
//         return returnValue;
// }