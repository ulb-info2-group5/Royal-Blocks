// File: message_menu_gui.hpp
// Authors: Jonas, Ernest, Rafaou

#ifndef GUI_MESSAGE_MENU_HPP
#define GUI_MESSAGE_MENU_HPP

#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QTextBrowser>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <qboxlayout.h>

class Controller;

namespace GUI {

    class MainGui;

    class MessageMenuGui : public QWidget {
        Q_OBJECT

      private:
        Controller &controller_;
        MainGui &mainGui_;

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
        void updateAll();
        void onEnterKeyPressedInInput();

      public:
        MessageMenuGui(Controller &controller, MainGui &mainGui,
                       QWidget *parent = nullptr);
        ~MessageMenuGui() = default;

      signals:
        void backToMainMenu();
    };

} // namespace GUI

#endif // GUI_MESSAGE_MENU_HPP
