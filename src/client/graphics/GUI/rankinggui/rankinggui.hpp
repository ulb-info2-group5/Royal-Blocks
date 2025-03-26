#ifndef RANKINGGUI_HPP
#define RANKINGGUI_HPP

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHeaderView>

class Controller; // Forward declaration

class RankingGui : public QWidget {
    Q_OBJECT

public:
    RankingGui(Controller *controller, QWidget *parent = nullptr);
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

private:
    Controller *controller_;
    QTableWidget *RankingGuiTable;
    QPushButton *backButton;

    /*
    * @brief Setup the ranking Table
    */
    void setupRankingGuiTable();
};

#endif // RANKINGGUI_HPP
