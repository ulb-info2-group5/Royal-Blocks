#ifndef GUI_EFFECT_SELECTOR_HPP
#define GUI_EFFECT_SELECTOR_HPP

#include "effect/effect_type.hpp"
#include "effect_price/effect_price.hpp"
#include "graphics/common/abstract_game_display.hpp"
#include "player_state/player_state.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <qchar.h>
#include <qprogressbar.h>
#include <qpushbutton.h>

namespace GUI {

    class EffectSelector : public QFrame {
        Q_OBJECT

      private:
        QVBoxLayout layout_;

      public:
        EffectSelector(QWidget *parent = nullptr);

        void clear();

        void setEffectPrices(
            const std::vector<std::pair<EffectType, Energy>> &effectPrices);

      signals:
        void buyEffect(EffectType);
    };

} // namespace GUI

#endif // GUI_EFFECT_SELECTOR_HPP
