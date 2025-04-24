#ifndef GUI_FRIENDS_MENU_HPP
#define GUI_FRIENDS_MENU_HPP

#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>

class Controller;

namespace GUI {

    class TetrisWindow;

    /**
    * @brief It allows add, remove friends from the list.
    * Accept or decline friend request.
    * Send a friend request.
    * Show frinds list.
    */

    class FriendsMenu : public QWidget {
        Q_OBJECT

      private:
        Controller &controller_;
        TetrisWindow &tetrisWindow_;

        QStackedWidget stack_;

        QListWidget friendsList_;
        QListWidget friendRequestsList_;

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
         * @brief Refresh the friends list by calling the updateFriendsList
         * method
         */
        void refreshFriendsList();

        /*
         * @brief Refresh the friend requests list by calling the
         * updateFriendRequestsList method
         */
        void refreshFriendRequestsList();

      public:
        FriendsMenu(Controller &controller, TetrisWindow &tetrisWindow,
                    QWidget *parent = nullptr);

        ~FriendsMenu() = default;

      signals:
        /*
         * @brief Signal emitted when the user click on the back button to
         * return to the main menu
         */
        void backToMainMenu();
    };

} // namespace GUI

#endif // GUI_FRIENDS_MENU_HPP
