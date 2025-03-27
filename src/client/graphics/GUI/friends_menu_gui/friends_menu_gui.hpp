#ifndef FRIENDS_MENU_GUI_HPP
#define FRIENDS_MENU_GUI_HPP

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QStackedWidget>
#include <QListWidget>
#include <qlabel.h>

class Controller; // Forward declaration

class MainGui; // Forward declaration

class FriendsMenuGui : public QWidget {
    Q_OBJECT

public:
    FriendsMenuGui(Controller &controller, MainGui *mainGui = nullptr, QWidget *parent = nullptr);

signals:
    void backToMainMenu();

private slots:
    void showMainFriendsMenu();
    void showAddFriendScreen();
    void showFriendRequestsScreen();
    void sendFriendRequest();
    void removeFriend();
    void acceptRequest();
    void declineRequest();

    void refreshFriendsList();
    void refreshFriendRequestsList();

private:
    Controller &controller_;
    MainGui *mainGui_;

    QStackedWidget *stack_;
    QWidget *mainWidget_;
    QWidget *addFriendWidget_;
    QWidget *friendRequestsWidget_;

    QListWidget *friendsList_;
    QListWidget *friendRequestsList_;

    QPushButton addFriendButton_;
    QPushButton manageRequestsButton_;
    QPushButton backToMainMenuButton_;
    QPushButton submitAdd_;
    QPushButton backFromAdd_;
    QPushButton acceptButton_;
    QPushButton declineButton_;
    QPushButton backFromReqButton_;

    QLineEdit friendNameInput_;
    QLabel *addFriendMsgLabel_;
    QLabel *noFriendsLabel_;
    QLabel *noRequestsLabel_;

    void setup();
    void updateFriendsList();
    void updateFriendRequestsList();
};

#endif // FRIENDS_MENU_GUI_HPP
