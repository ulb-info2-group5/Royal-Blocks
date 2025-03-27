#ifndef RANKINGGUI_HPP
#define RANKINGGUI_HPP

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QResizeEvent>
#include <qstackedwidget.h>

class Controller; // Forward declaration

class MainGui; // Forward declaration

class RankingGui : public QWidget {
    Q_OBJECT

    private:
        Controller &controller_;
        
        MainGui &mainGui_;

        QStackedWidget *stack_;

        QTableWidget RankingGuiTable;

        QPushButton backButton;

        /*
        * @brief Setup the ranking Table
        */
        void setupRankingGuiTable();

        /*
        * @brief Update the ranking Table
        */
        void updateRankingGuiTable();

    public:
        RankingGui(Controller &controller, MainGui &mainGui, QWidget *parent = nullptr);
        
        ~RankingGui() = default;

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

#endif // RANKINGGUI_HPP
