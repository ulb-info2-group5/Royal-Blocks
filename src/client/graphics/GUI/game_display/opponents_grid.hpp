#ifndef GUI_OPPONENTS_GRID
#define GUI_OPPONENTS_GRID

#include <QFrame>
#include <QGridLayout>
#include <QWidget>

namespace GUI {

    /**
    * @brief 
    * Display during the game the opponents grids.
    * Allows to select an opponent like target.
    */

    class OpponentsGrid : public QFrame {
        Q_OBJECT

      private:
        QHBoxLayout layout_;

      public:
        OpponentsGrid(QWidget *parent = nullptr);

        void setNthOpponent(size_t index, QPixmap *boardMap,
                            const QString &name);

        void setSelectedTarget(int selectedOppIdx);

        void setNumOpponents(size_t numOpponents);

      signals:
        void selectTarget(size_t targetNum);
    };

}; // namespace GUI

#endif // GUI_OPPONENTS_GRID
