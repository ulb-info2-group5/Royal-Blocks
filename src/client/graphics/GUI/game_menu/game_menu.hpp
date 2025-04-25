// Authors: Jonas, Ernest, Rafaou

#ifndef GUI_GAME_MENU_HPP
#define GUI_GAME_MENU_HPP

#include "../../../../common/tetris_royal_lib/game_mode/game_mode.hpp"
#include "../../../../common/types/types.hpp"
#include "../game_display/game_display.hpp"

#include <memory>

#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QSlider>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>

class Controller;

namespace GUI {

    class TetrisWindow;

    enum class JoinFriendType {
        JoinFriend,
        SpectateFriend,
    };

    /**
    * @brief Display all options in the main game menu
    */

    class GameMenu : public QWidget {
        Q_OBJECT

      private:
        Controller &controller_;
        TetrisWindow &tetrisWindow_;
        std::unique_ptr<GameDisplay> gameDisplay_;

        QStackedWidget *stack_;
        QWidget selectModeWidget_;
        QWidget playerCountWidget_;
        QWidget joinTypeWidget_;
        QWidget friendsListWidget_;
        QWidget waitingWidget_;

        QLabel playerCountLabel_;
        QListWidget friendsList_;

        QSlider *playerCountSlider_;

        GameMode selectedGameMode_;
        int playerCount_;
        bool isCreateGame_;
        JoinFriendType joinFriendType_;

        static constexpr size_t MAX_NUM_PLAYERS_CLASSIC_ROYAL = 9;
        static constexpr size_t MIN_NUM_PLAYERS_CLASSIC_ROYAL = 3;

        void setup();
        void showSelectModeScreen();
        void showPlayerCountScreen();
        void showJoinTypeScreen();
        void showFriendsListScreen();
        void showWaitingScreen();
        void updateFriendsList();
        void createAndShowGameDisplay();

      private slots:
        void onEndlessButtonClicked();
        void onDualButtonClicked();
        void onClassicButtonClicked();
        void onRoyalButtonClicked();
        void onBackButtonClicked();
        void onConfirmButtonClicked();
        void onJoinRandomButtonClicked();
        void onJoinFriendButtonClicked();
        void onSpectateFriendButtonClicked();
        void onPlayerCountChanged(int value);
        void onFriendSelected(QListWidgetItem *item);

      public:
        GameMenu(Controller &controller, TetrisWindow &tetrisWindow,
                 QWidget *parent = nullptr);
        ~GameMenu() = default;

        void run(bool isCreateGame);

      signals:
        void backToMainMenu();
    };

} // namespace GUI

#endif // GUI_GAME_MENU_HPP
