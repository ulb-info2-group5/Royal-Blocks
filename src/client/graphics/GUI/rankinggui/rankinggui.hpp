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
    ~RankingGui() {}

signals:
    void backToMainMenu();

public slots:
    void on_BackButtonClicked();

private:
    Controller *controller_;
    QTableWidget *RankingGuiTable;
    QPushButton *backButton;
    void setupRankingGuiTable();
};

#endif // RANKINGGUI_HPP
