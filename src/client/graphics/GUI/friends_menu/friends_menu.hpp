/*
 * This file is part of Royal Blocks.
 *
 * Royal Blocks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Royal Blocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Royal Blocks.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef GUI_FRIENDS_MENU_HPP
#define GUI_FRIENDS_MENU_HPP

#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QStackedWidget>
#include <QWidget>

class Controller;

namespace GUI {

    class TetrisWindow;

    /**
     * @brief Allows to:
     * - show the friendslist
     * - add/remove friends from the friendslist
     * - accept/decline friend requests
     * - send a friend request
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
