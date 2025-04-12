#ifndef GUI_OPPONENTS_GRID
#define GUI_OPPONENTS_GRID

#include <QFrame>
#include <QGridLayout>
#include <qwidget.h>

namespace GUI {

    class OpponentsGrid : public QFrame {
        Q_OBJECT

      private:
        QGridLayout layout_;

      public:
        OpponentsGrid(QWidget *parent = nullptr);

        void setNthOpponent(size_t index, QPixmap *boardMap,
                            const QString &name, bool isSelected);

        void setNumOpponents(size_t numOpponents);

      signals:
        void selectTarget(size_t targetNum);
    };

}; // namespace GUI

#endif // GUI_OPPONENTS_GRID
