// Authors: Jonas, Ernest, Rafaou

#ifndef GUI_GAME_MENU_HPP
#define GUI_GAME_MENU_HPP

#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QSlider>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>

#include "../../../../common/tetris_royal_lib/game_mode/game_mode.hpp"
#include "../../../../common/types/types.hpp"
#include "graphics/GUI/game_display/game_display.hpp"

class Controller;

namespace GUI {

    class MainGui;

    class GameMenuGUI : public QWidget {
        Q_OBJECT

      private:
        Controller &controller_;
        MainGui &mainGui_;
        GameDisplay gameDisplay_;

        QStackedWidget *stack_;
        QWidget selectModeWidget_;
        QWidget playerCountWidget_;
        QWidget joinTypeWidget_;
        QWidget friendsListWidget_;
        QWidget waitingWidget_;

        QLabel playerCountLabel_;
        QListWidget friendsList_;

        // Slider
        QSlider *playerCountSlider_;

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
        void changeMinSlider();

      public:
        GameMenuGUI(Controller &controller, MainGui &mainGui,
                    QWidget *parent = nullptr);
        ~GameMenuGUI() = default;

        void run(bool isCreateGame);

      signals:
        void backToMainMenu();
    };

} // namespace GUI

#endif // GUI_GAME_MENU_HPP
