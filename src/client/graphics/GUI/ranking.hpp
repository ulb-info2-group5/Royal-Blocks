#ifndef RANKING_HPP
#define RANKING_HPP

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHeaderView>

class Controller; // Forward declaration

class Ranking : public QWidget {
    Q_OBJECT

public:
    Ranking(Controller *controller, QWidget *parent = nullptr);
    ~Ranking() {}

signals:
    void backToMainMenu();

public slots:
    void on_BackButtonClicked();

private:
    Controller *controller_;
    QTableWidget *rankingTable;
    QPushButton *backButton;
    void setupRankingTable();
};

#endif // RANKING_HPP
