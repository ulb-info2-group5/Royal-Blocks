#ifndef GUI_RANKING_HPP
#define GUI_RANKING_HPP

#include <QTableWidget>
#include <QWidget>

class Controller;

namespace GUI {

    class TetrisWindow;

    class Ranking : public QWidget {
        Q_OBJECT

      private:
        Controller &controller_;

        TetrisWindow &tetrisWindow_;

        QTableWidget rankingTable_;

        /*
         * @brief Setup the UI
         */
        void setupUI();

        /*
         * @brief Setup the ranking Table
         */
        void setupRankingTable();

        /*
         * @brief Update the ranking Table
         */
        void updateRankingTable();

      public:
        Ranking(Controller &controller, TetrisWindow &tetrisWindow,
                QWidget *parent = nullptr);

        ~Ranking() = default;

      signals:
        /*
         * @brief Signal emitted when the user click on the back button
         */
        void backToMainMenu();

      public slots:
        /*
         * @brief Action to perform when the user click on the back button
         */
        void on_BackButtonClicked();
    };

} // namespace GUI

#endif // GUI_RANKING_HPP
