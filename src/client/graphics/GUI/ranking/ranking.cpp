#include "ranking.hpp"

#include "graphics/GUI/tetris_window.hpp"

#include <QHeaderView>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>

#include "../../../core/controller/controller.hpp"

namespace GUI {

    Ranking::Ranking(Controller &controller, TetrisWindow &tetrisWindow,
                     QWidget *parent)
        : QWidget(parent), controller_(controller),
          tetrisWindow_(tetrisWindow) {
        setupUI();
    }

    void Ranking::on_BackButtonClicked() { emit backToMainMenu(); }

    /*--------------------------------------------------------
                        Private Methods
    ---------------------------------------------------------*/

    void Ranking::setupUI() {
        QPushButton *backButton = new QPushButton(this);
        backButton->setAutoDefault(true);

        connect(&tetrisWindow_, &TetrisWindow::updateRanking, this,
                &Ranking::updateRankingTable);

        backButton->setText("Back");
        backButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        backButton->setFixedWidth(500);

        setupRankingTable();
        updateRankingTable();

        connect(backButton, &QPushButton::clicked, this,
                &Ranking::on_BackButtonClicked);

        QWidget *scrollWidget = new QWidget(this);
        QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
        scrollLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                              QSizePolicy::Expanding));
        scrollLayout->addWidget(&rankingTable_, 0, Qt::AlignCenter);
        scrollLayout->addWidget(backButton, 0, Qt::AlignCenter);
        scrollLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                              QSizePolicy::Expanding));
        scrollWidget->setLayout(scrollLayout);

        QScrollArea *scrollArea = new QScrollArea(this);
        scrollArea->setWidgetResizable(true);
        scrollArea->setWidget(scrollWidget);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(scrollArea, 1);
        layout->setAlignment(Qt::AlignCenter);

        setLayout(layout);
    }

    void Ranking::setupRankingTable() {
        std::vector<std::pair<std::string, Score>> RankingGuiData =
            controller_.getRanking();

        rankingTable_.setRowCount(RankingGuiData.size());
        rankingTable_.setColumnCount(2);
        rankingTable_.setEditTriggers(QAbstractItemView::NoEditTriggers);
        rankingTable_.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        rankingTable_.setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        rankingTable_.setFixedSize(500, 500);
        rankingTable_.horizontalHeader()->setSectionResizeMode(
            QHeaderView::Fixed);
        rankingTable_.verticalHeader()->setSectionResizeMode(
            QHeaderView::Fixed);

        QStringList headers;
        headers << "Player" << "Score";
        rankingTable_.setHorizontalHeaderLabels(headers);

        rankingTable_.horizontalHeader()->setSectionResizeMode(
            0, QHeaderView::Stretch);
        rankingTable_.horizontalHeader()->setSectionResizeMode(
            1, QHeaderView::Stretch);
    }

    void Ranking::updateRankingTable() {
        std::vector<std::pair<std::string, Score>> RankingGuiData =
            controller_.getRanking();

        rankingTable_.setRowCount(RankingGuiData.size());

        for (size_t i = 0; i < RankingGuiData.size(); ++i) {
            QTableWidgetItem *playerItem = new QTableWidgetItem(
                QString::fromStdString(RankingGuiData[i].first));
            playerItem->setTextAlignment(Qt::AlignCenter);
            QTableWidgetItem *scoreItem =
                new QTableWidgetItem(QString::number(RankingGuiData[i].second));
            scoreItem->setTextAlignment(Qt::AlignCenter);

            rankingTable_.setItem(i, 0, playerItem);
            rankingTable_.setItem(i, 1, scoreItem);
        }
    }

} // namespace GUI
