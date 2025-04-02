#ifndef GAME_MENU_GUI_HPP
#define GAME_MENU_GUI_HPP

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QListWidget>
#include <QSlider>

#include "../../../../common/tetris_royal_lib/game_mode/game_mode.hpp"
#include "../../../../common/types/types.hpp"

class Controller;
class MainGui;

class GameMenuGUI : public QWidget {
    Q_OBJECT

private:
    Controller &controller_;
    MainGui &mainGui_;

    QStackedWidget *stack_;
    QWidget *selectModeWidget_;
    QWidget *playerCountWidget_;
    QWidget *joinTypeWidget_;
    QWidget *friendsListWidget_;
    QWidget *waitingWidget_;

    QPushButton endlessButton_;
    QPushButton duelButton_;
    QPushButton classicButton_;
    QPushButton royalButton_;
    QPushButton backButton_;
    QPushButton confirmButton_;
    QPushButton joinRandomButton_;
    QPushButton joinFriendButton_;

    QSlider *playerCountSlider_;
    QLabel *playerCountLabel_;
    QListWidget friendsList_;

    GameMode selectedGameMode_;
    int playerCount_;
    bool isCreateGame_;

    void setup();
    void showSelectModeScreen();
    void showPlayerCountScreen();
    void showJoinTypeScreen();
    void showFriendsListScreen();
    void showWaitingScreen();
    void updateFriendsList();

private slots:
    void onEndlessButtonClicked();
    void onDuelButtonClicked();
    void onClassicButtonClicked();
    void onRoyalButtonClicked();
    void onBackButtonClicked();
    void onConfirmButtonClicked();
    void onJoinRandomButtonClicked();
    void onJoinFriendButtonClicked();
    void onPlayerCountChanged(int value);
    void onFriendSelected(QListWidgetItem *item);
    
public:
    GameMenuGUI(Controller &controller, MainGui &mainGui, QWidget *parent = nullptr);
    ~GameMenuGUI() = default;

    void run(bool isCreateGame);

signals:
    void backToMainMenu();
};

#endif // GAME_MENU_GUI_HPP