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
