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

#ifndef GUI_EFFECT_SELECTOR_HPP
#define GUI_EFFECT_SELECTOR_HPP

#include "../../../../common/tetris_royal_lib/effect/effect_type.hpp"
#include "../../../../common/tetris_royal_lib/effect_price/effect_price.hpp"
#include "../../../core/in_game/player_state/player_state_external.hpp"
#include "../../../core/in_game/player_state/player_state_self.hpp"
#include "../../common/abstract_game_display.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QWidget>

namespace GUI {

    /**
     * @brief It allows to see the available effects and which one is selected.
     * The effects an effect is clicked, a signal will be sent (in order to make
     * the user buy the effect).
     */
    class EffectSelector : public QFrame {
        Q_OBJECT

      private:
        QVBoxLayout layout_;

        const QString selectedStyleSheet_{"background-color: blue;"};
        const QString defaultStyleSheet_{""};

      public:
        EffectSelector(QWidget *parent = nullptr);

        void clear();

        void setEffectPrices(
            const std::vector<std::pair<EffectType, Energy>> &effectPrices,
            EffectType selectedEffectType);

        void setSelected();

      signals:
        void buyEffect(EffectType);
    };

} // namespace GUI

#endif // GUI_EFFECT_SELECTOR_HPP
