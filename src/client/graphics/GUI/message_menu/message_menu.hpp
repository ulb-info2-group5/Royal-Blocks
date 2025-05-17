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

// File: message_menu_gui.hpp
// Authors: Jonas, Ernest, Rafaou

#ifndef GUI_MESSAGE_MENU_HPP
#define GUI_MESSAGE_MENU_HPP

#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QTextBrowser>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

class Controller;

namespace GUI {

    class TetrisWindow;

    /**
     * @brief Message service display, allows to send and receive messages.
     */
    class MessageMenu : public QWidget {
        Q_OBJECT

      private:
        Controller &controller_;
        TetrisWindow &tetrisWindow_;

        QListWidget friendsList_;
        QTextBrowser chatDisplay_;
        QLineEdit messageInput_;

        void setupUI();
        void loadFriends();
        void loadMessages(int friendIndex);

      private slots:
        void updateChat();
        void onSendMessage();
        void onBack();

        /**
         * @brief Update the friends list and update the chat
         */
        void updateAll();

        /**
         * @brief Grab the message by the palyer and send it when the key
         * "enter" is pressed
         */
        void onEnterKeyPressedInInput();

      public:
        MessageMenu(Controller &controller, TetrisWindow &tetrisWindow,
                    QWidget *parent = nullptr);
        ~MessageMenu() = default;

      signals:
        void backToMainMenu();
    };

} // namespace GUI

#endif // GUI_MESSAGE_MENU_HPP
