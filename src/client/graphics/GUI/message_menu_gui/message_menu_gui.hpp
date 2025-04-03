// File: message_menu_gui.hpp
// Authors: Jonas, Ernest, Rafaou

#ifndef MESSAGE_MENU_GUI_HPP
#define MESSAGE_MENU_GUI_HPP

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QStackedWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QTextBrowser>
#include <qboxlayout.h>

class Controller; // Forward declaration
class MainGui; // Forward declaration

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
    MessageMenuGui(Controller &controller, MainGui &mainGui, QWidget *parent = nullptr);
    ~MessageMenuGui() = default;

signals:
    void backToMainMenu();
};

#endif // MESSAGE_MENU_GUI_HPP
