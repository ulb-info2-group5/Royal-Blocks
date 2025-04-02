#include "game_menu_gui.hpp"
#include "../qt_config/qt_config.hpp"
#include "../../../core/controller/controller.hpp"
#include "../main_gui.hpp"

#include <QMessageBox>

GameMenuGUI::GameMenuGUI(Controller &controller, MainGui &mainGui, QWidget *parent)
    : controller_(controller), mainGui_(mainGui), QWidget(parent),
      playerCount_(4), isCreateGame_(false)
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
    confirmButton_.setText("Confirm");
    confirmButton_.setFixedWidth(500);
    joinRandomButton_.setText("Join Random Game");
    joinRandomButton_.setFixedWidth(500);
    joinFriendButton_.setText("Join Friend's Game");
    joinFriendButton_.setFixedWidth(500);

    // Connect signals
    connect(&endlessButton_, &QPushButton::clicked, this, &GameMenuGUI::onEndlessButtonClicked);
    connect(&duelButton_, &QPushButton::clicked, this, &GameMenuGUI::onDuelButtonClicked);
    connect(&classicButton_, &QPushButton::clicked, this, &GameMenuGUI::onClassicButtonClicked);
    connect(&royalButton_, &QPushButton::clicked, this, &GameMenuGUI::onRoyalButtonClicked);
    connect(&backButton_, &QPushButton::clicked, this, &GameMenuGUI::onBackButtonClicked);
    connect(&confirmButton_, &QPushButton::clicked, this, &GameMenuGUI::onConfirmButtonClicked);
    connect(&joinRandomButton_, &QPushButton::clicked, this, &GameMenuGUI::onJoinRandomButtonClicked);
    connect(&joinFriendButton_, &QPushButton::clicked, this, &GameMenuGUI::onJoinFriendButtonClicked);

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

    // Setup player count screen
    playerCountWidget_ = new QWidget();
    QVBoxLayout *playerCountLayout = new QVBoxLayout(playerCountWidget_);
    playerCountSlider_ = new QSlider(Qt::Horizontal);
    playerCountSlider_->setMinimum(2);
    playerCountSlider_->setMaximum(9);
    playerCountSlider_->setValue(4);
    playerCountSlider_->setFixedWidth(500);
    playerCountLabel_ = new QLabel("Player Count: 4");
    playerCountLabel_->setAlignment(Qt::AlignCenter);
    connect(playerCountSlider_, &QSlider::valueChanged, this, &GameMenuGUI::onPlayerCountChanged);
    
    playerCountLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    playerCountLayout->addWidget(createCenterBoldTitle("Select Player Count"));
    playerCountLayout->addWidget(playerCountLabel_, 0, Qt::AlignCenter);
    playerCountLayout->addWidget(playerCountSlider_, 0, Qt::AlignCenter);
    playerCountLayout->addWidget(&confirmButton_, 0, Qt::AlignCenter);
    playerCountLayout->addWidget(&backButton_, 0, Qt::AlignCenter);
    playerCountLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // Setup join type screen
    joinTypeWidget_ = new QWidget();
    QVBoxLayout *joinTypeLayout = new QVBoxLayout(joinTypeWidget_);
    joinTypeLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    joinTypeLayout->addWidget(createCenterBoldTitle("Join Game"));
    joinTypeLayout->addWidget(&joinRandomButton_, 0, Qt::AlignCenter);
    joinTypeLayout->addWidget(&joinFriendButton_, 0, Qt::AlignCenter);
    joinTypeLayout->addWidget(&backButton_, 0, Qt::AlignCenter);
    joinTypeLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // Setup friends list screen
    friendsListWidget_ = new QWidget();
    QVBoxLayout *friendsListLayout = new QVBoxLayout(friendsListWidget_);
    friendsList_.setFixedWidth(500);
    friendsListLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    friendsListLayout->addWidget(createCenterBoldTitle("Select a Friend"));
    friendsListLayout->addWidget(&friendsList_, 0, Qt::AlignCenter);
    friendsListLayout->addWidget(&backButton_, 0, Qt::AlignCenter);
    friendsListLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    connect(&friendsList_, &QListWidget::itemDoubleClicked, this, &GameMenuGUI::onFriendSelected);

    // Add widgets to stack
    stack_->addWidget(selectModeWidget_);
    stack_->addWidget(playerCountWidget_);
    stack_->addWidget(joinTypeWidget_);
    stack_->addWidget(friendsListWidget_);

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

void GameMenuGUI::showPlayerCountScreen()
{
    stack_->setCurrentWidget(playerCountWidget_);
}

void GameMenuGUI::showJoinTypeScreen()
{
    stack_->setCurrentWidget(joinTypeWidget_);
}

void GameMenuGUI::showFriendsListScreen()
{
    updateFriendsList();
    stack_->setCurrentWidget(friendsListWidget_);
}

void GameMenuGUI::updateFriendsList()
{
    friendsList_.clear();
    
    const std::vector<bindings::User> friendsList = controller_.getFriendsList();
    for (const auto &friendUser : friendsList) {
        if (friendUser.isJoinable() && friendUser.gameMode == selectedGameMode_) {
            QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(friendUser.username));
            item->setData(Qt::UserRole, QVariant::fromValue(friendUser.userID));
            item->setTextAlignment(Qt::AlignCenter);
            friendsList_.addItem(item);
        }
    }
    
    if (friendsList_.count() == 0) {
        QListWidgetItem *noFriendsItem = new QListWidgetItem("No friends available to join");
        noFriendsItem->setFlags(noFriendsItem->flags() & ~Qt::ItemIsEnabled);
        noFriendsItem->setTextAlignment(Qt::AlignCenter);
        friendsList_.addItem(noFriendsItem);
    }
}

// Slot implementations
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
        showJoinTypeScreen();
    }
}

void GameMenuGUI::onClassicButtonClicked()
{
    selectedGameMode_ = GameMode::Classic;
    
    if (isCreateGame_) {
        showPlayerCountScreen();
    } else {
        showJoinTypeScreen();
    }
}

void GameMenuGUI::onRoyalButtonClicked()
{
    selectedGameMode_ = GameMode::RoyalCompetition;
    
    if (isCreateGame_) {
        showPlayerCountScreen();
    } else {
        showJoinTypeScreen();
    }
}

void GameMenuGUI::onBackButtonClicked()
{
    if (stack_->currentWidget() == selectModeWidget_) {
        emit backToMainMenu();
    } else if (stack_->currentWidget() == playerCountWidget_) {
        showSelectModeScreen();
    } else if (stack_->currentWidget() == joinTypeWidget_) {
        showSelectModeScreen();
    } else if (stack_->currentWidget() == friendsListWidget_) {
        showJoinTypeScreen();
    }
}

void GameMenuGUI::onConfirmButtonClicked()
{
    controller_.createGame(selectedGameMode_, playerCount_);
    // We would show waiting screen here in later stages
}

void GameMenuGUI::onJoinRandomButtonClicked()
{
    controller_.joinGame(selectedGameMode_, std::nullopt);
    // We would show waiting screen here in later stages
}

void GameMenuGUI::onJoinFriendButtonClicked()
{
    showFriendsListScreen();
}

void GameMenuGUI::onPlayerCountChanged(int value)
{
    playerCount_ = value;
    playerCountLabel_->setText(QString("Player Count: %1").arg(value));
}

void GameMenuGUI::onFriendSelected(QListWidgetItem *item)
{
    if (item && item->flags() & Qt::ItemIsEnabled) {
        UserID friendId = item->data(Qt::UserRole).toULongLong();
        controller_.joinGame(selectedGameMode_, friendId);
        // We would show waiting screen here in later stages
    }
}