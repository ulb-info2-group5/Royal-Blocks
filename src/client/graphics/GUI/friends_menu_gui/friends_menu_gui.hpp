#ifndef FRIENDS_MENU_GUI_HPP
#define FRIENDS_MENU_GUI_HPP

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QStackedWidget>
#include <QListWidget>

class Controller; // Forward declaration

class MainGui; // Forward declaration

class FriendsMenuGui : public QWidget {
    Q_OBJECT

    private:
        Controller &controller_;
        MainGui &mainGui_;

        QStackedWidget *stack_;
        QWidget *mainWidget_;
        QWidget *addFriendWidget_;
        QWidget *friendRequestsWidget_;

        QListWidget friendsList_;
        QListWidget friendRequestsList_;

        QPushButton addFriendButton_;
        QPushButton manageRequestsButton_;
        QPushButton backToMainMenuButton_;
        QPushButton submitAdd_;
        QPushButton backFromAdd_;
        QPushButton acceptButton_;
        QPushButton declineButton_;
        QPushButton backFromReqButton_;

        QLineEdit friendNameInput_;
        QLabel addFriendMsgLabel_;
        QLabel noFriendsLabel_;
        QLabel noRequestsLabel_;

        /*
        * @brief Setup the friends list gui
        */
        void setup();

        /*
        * @brief Update the friends list
        */
        void updateFriendsList();

        /*
        * @brief Update the friend requests list
        */
        void updateFriendRequestsList();

    private slots:
        void showMainFriendsMenu();
        void showAddFriendScreen();
        void showFriendRequestsScreen();
        void sendFriendRequest();
        void removeFriend();
        void acceptRequest();
        void declineRequest();

        /*
        * @brief Refresh the friends list by calling the updateFriendsList method
        */
        void refreshFriendsList();

        /*
        * @brief Refresh the friend requests list by calling the updateFriendRequestsList method
        */
        void refreshFriendRequestsList();

    public:
        FriendsMenuGui(Controller &controller, MainGui &mainGui, QWidget *parent = nullptr);

        ~FriendsMenuGui() = default;

    signals:
        /*
        * @brief Signal emitted when the user click on the back button to return to the main menu
        */
        void backToMainMenu();
};

#endif // FRIENDS_MENU_GUI_HPP
