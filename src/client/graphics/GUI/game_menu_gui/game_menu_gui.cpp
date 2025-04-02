#include "game_menu_gui.hpp"
#include "../qt_config/qt_config.hpp"
#include "../../../core/controller/controller.hpp"
#include "../main_gui.hpp"

#include <QMessageBox>

GameMenuGUI::GameMenuGUI(Controller &controller, MainGui &mainGui, QWidget *parent)
    : controller_(controller), mainGui_(mainGui), QWidget(parent),
      isCreateGame_(false)
{
    setup();
}

void GameMenuGUI::run(bool isCreateGame)
{
    isCreateGame_ = isCreateGame;
    showSelectModeScreen();
}

void GameMenuGUI::setup()
{
    stack_ = new QStackedWidget();

    // Configure buttons
    endlessButton_.setText("Endless Mode");
    endlessButton_.setFixedWidth(500);
    duelButton_.setText("Duel Mode");
    duelButton_.setFixedWidth(500);
    classicButton_.setText("Classic Mode");
    classicButton_.setFixedWidth(500);
    royalButton_.setText("Royal Competition Mode");
    royalButton_.setFixedWidth(500);
    backButton_.setText("Back");
    backButton_.setFixedWidth(500);

    // Connect signals
    connect(&endlessButton_, &QPushButton::clicked, this, &GameMenuGUI::onEndlessButtonClicked);
    connect(&duelButton_, &QPushButton::clicked, this, &GameMenuGUI::onDuelButtonClicked);
    connect(&classicButton_, &QPushButton::clicked, this, &GameMenuGUI::onClassicButtonClicked);
    connect(&royalButton_, &QPushButton::clicked, this, &GameMenuGUI::onRoyalButtonClicked);
    connect(&backButton_, &QPushButton::clicked, this, &GameMenuGUI::onBackButtonClicked);

    // Setup select mode screen
    selectModeWidget_ = new QWidget();
    QVBoxLayout *selectModeLayout = new QVBoxLayout(selectModeWidget_);
    selectModeLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    selectModeLayout->addWidget(createCenterBoldTitle("Select Game Mode"));
    selectModeLayout->addWidget(&endlessButton_, 0, Qt::AlignCenter);
    selectModeLayout->addWidget(&duelButton_, 0, Qt::AlignCenter);
    selectModeLayout->addWidget(&classicButton_, 0, Qt::AlignCenter);
    selectModeLayout->addWidget(&royalButton_, 0, Qt::AlignCenter);
    selectModeLayout->addWidget(&backButton_, 0, Qt::AlignCenter);
    selectModeLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // Add widgets to stack
    stack_->addWidget(selectModeWidget_);

    // Set main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stack_);
    setLayout(mainLayout);
}

// Screen display methods
void GameMenuGUI::showSelectModeScreen()
{
    stack_->setCurrentWidget(selectModeWidget_);
}

// Basic slot implementations
void GameMenuGUI::onEndlessButtonClicked()
{
    selectedGameMode_ = GameMode::Endless;
    
    if (isCreateGame_) {
        controller_.createGame(selectedGameMode_, 1);
        // We would show waiting screen here in later stages
    } else {
        controller_.joinGame(selectedGameMode_, std::nullopt);
        // We would show waiting screen here in later stages
    }
}

void GameMenuGUI::onDuelButtonClicked()
{
    selectedGameMode_ = GameMode::Dual;
    
    if (isCreateGame_) {
        // Duel always has 2 players
        controller_.createGame(selectedGameMode_, 2);
        // We would show waiting screen here in later stages
    } else {
        // We would show join type screen here in later stages
    }
}

void GameMenuGUI::onClassicButtonClicked()
{
    selectedGameMode_ = GameMode::Classic;
    
    if (isCreateGame_) {
        // We would show player count screen here in later stages
    } else {
        // We would show join type screen here in later stages
    }
}

void GameMenuGUI::onRoyalButtonClicked()
{
    selectedGameMode_ = GameMode::RoyalCompetition;
    
    if (isCreateGame_) {
        // We would show player count screen here in later stages
    } else {
        // We would show join type screen here in later stages
    }
}

void GameMenuGUI::onBackButtonClicked()
{
    emit backToMainMenu();
}