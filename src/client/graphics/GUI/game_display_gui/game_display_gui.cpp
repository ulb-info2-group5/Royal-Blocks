// #include "game_display_gui.hpp"
// #include "../qt_config/qt_config.hpp"

// #include "board/board.hpp"
// #include "core/in_game/effects/timed_bonus.hpp"
// #include "core/in_game/game_state/game_state.hpp"
// #include "core/in_game/game_state/game_state_viewer.hpp"
// #include "effect/effect_type.hpp"
// #include "effect_price/effect_price.hpp"
// #include "game_mode/game_mode.hpp"

// #include "graphics/common/abstract_game_display.hpp"
// #include "../../../core/controller/controller.hpp"
// #include "../main_tui.hpp"
// #include "player_state/player_state.hpp"
// #include "tetromino/tetromino.hpp"
// #include "vec2/vec2.hpp"

// #include <memory>
// #include <optional>
// #include <stdexcept>
// #include <string>
// #include <type_traits>
// #include <utility>
// #include <variant>
// #include <vector>

// #include <QWidget>
// #include <QPushButton>
// #include <QVBoxLayout>
// #include <QLineEdit>
// #include <QLabel>
// #include <QImage> 
// #include <QColor> 

// QColor getQColor(AbstractGameDisplay::Color col, selfCellType selfCellType) {

//     QColor returnValue = QColor::fromRgb(0,0,255);

//     switch (col) {
//         case AbstractGameDisplay::Color::Black:
//             returnValue = QColor::fromRgb(0,0,0);
//             break;
//         case AbstractGameDisplay::Color::White:
//             returnValue = QColor::fromRgb(255,255,255);
//             break;
//         case AbstractGameDisplay::Color::Grey:
//             returnValue = QColor::fromRgb(160,160,160);
//             break;
//         case AbstractGameDisplay::Color::DarkBlue:
//             returnValue = QColor::fromRgb(0,0,153);
//             break;
//         case AbstractGameDisplay::Color::LightBlue:
//             returnValue = QColor::fromRgb(51,255,255);
//             break;
//         case AbstractGameDisplay::Color::Purple:
//             returnValue = ftQColor::fromRgb(153,0,153);
//             break;
//         case AbstractGameDisplay::Color::Red:
//             returnValue = QColor::fromRgb(255,0,0);
//             break;
//         case AbstractGameDisplay::Color::Orange:
//             returnValue = QColor::fromRgb(255,153,51);
//             break;
//         case AbstractGameDisplay::Color::Pink:
//             returnValue = QColor::fromRgb(255,102,178);
//             break;
//         case AbstractGameDisplay::Color::Green:
//             returnValue = QColor::fromRgb(128,155,0);
//             break;
//         case AbstractGameDisplay::Color::Yellow:
//             returnValue = QColor::fromRgb(255,255,0);
//             break;
//         };
    
//         if (selfCellType == SelfCellType::Preview) {
//             returnValue = QColor::fromRgb(128,128,128,200);
//         }
    
//         return returnValue;
// }

// GameDisplayGUI(Controller &controller, MainGui &mainGui, QWidget *parent = nullptr);