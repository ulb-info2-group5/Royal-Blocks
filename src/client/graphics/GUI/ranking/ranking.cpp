#include "ranking.hpp"
#include <QHeaderView>
#include <QMessageBox>
#include <QScrollArea>
#include <QVBoxLayout>
#include <qnamespace.h>

#include "../../../core/controller/controller.hpp"

namespace GUI {

    Ranking::Ranking(Controller &controller, MainGui &mainGui,
                           QWidget *parent)
        : QWidget(parent), controller_(controller), mainGui_(mainGui) {
        setupUI();
    }

    void Ranking::on_BackButtonClicked() { emit backToMainMenu(); }

    /*--------------------------------------------------------
                        Private Methods
    ---------------------------------------------------------*/

    void Ranking::setupUI() {
        QPushButton *backButton = new QPushButton(this);

        connect(&mainGui_, &MainGui::updateRanking, this,
                &Ranking::updateRankingGuiTable);

        backButton->setText("Back");
        backButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        backButton->setFixedWidth(500);

        setupRankingGuiTable();
        updateRankingGuiTable();

        connect(backButton, &QPushButton::clicked, this,
                &Ranking::on_BackButtonClicked);

        QWidget *scrollWidget = new QWidget();
        QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
        scrollLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                              QSizePolicy::Expanding));
        scrollLayout->addWidget(&RankingGuiTable, 0, Qt::AlignCenter);
        scrollLayout->addWidget(backButton, 0, Qt::AlignCenter);
        scrollLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                              QSizePolicy::Expanding));
        scrollWidget->setLayout(scrollLayout);

        QScrollArea *scrollArea = new QScrollArea();
        scrollArea->setWidgetResizable(true);
        scrollArea->setWidget(scrollWidget);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        QVBoxLayout *layout = new QVBoxLayout();
        layout->addWidget(scrollArea, 1);
        layout->setAlignment(Qt::AlignCenter);

        setLayout(layout);
    }

    void Ranking::setupRankingGuiTable() {
        std::vector<std::pair<std::string, Score>> RankingGuiData =
            controller_.getRanking();

        RankingGuiTable.setRowCount(RankingGuiData.size());
        RankingGuiTable.setColumnCount(2);
        RankingGuiTable.setEditTriggers(QAbstractItemView::NoEditTriggers);
        RankingGuiTable.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        RankingGuiTable.setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        RankingGuiTable.setFixedSize(500, 500);
        RankingGuiTable.horizontalHeader()->setSectionResizeMode(
            QHeaderView::Fixed);
        RankingGuiTable.verticalHeader()->setSectionResizeMode(
            QHeaderView::Fixed);

        QStringList headers;
        headers << "Player" << "Score";
        RankingGuiTable.setHorizontalHeaderLabels(headers);

        RankingGuiTable.horizontalHeader()->setSectionResizeMode(
            0, QHeaderView::Stretch);
        RankingGuiTable.horizontalHeader()->setSectionResizeMode(
            1, QHeaderView::Stretch);
    }

    void Ranking::updateRankingGuiTable() {
        std::vector<std::pair<std::string, Score>> RankingGuiData =
            controller_.getRanking();

        RankingGuiTable.setRowCount(RankingGuiData.size());

        for (size_t i = 0; i < RankingGuiData.size(); ++i) {
            QTableWidgetItem *playerItem = new QTableWidgetItem(
                QString::fromStdString(RankingGuiData[i].first));
            QTableWidgetItem *scoreItem =
                new QTableWidgetItem(QString::number(RankingGuiData[i].second));

            RankingGuiTable.setItem(i, 0, playerItem);
            RankingGuiTable.setItem(i, 1, scoreItem);
        }
    }

} // namespace GUI
