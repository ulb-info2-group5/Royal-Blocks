// File: message_menu_gui.cpp
// Authors: Jonas, Ernest, Rafaou

#include "message_menu_gui.hpp"

#include "../../../core/controller/controller.hpp"
#include "../main_gui.hpp"

#include <QMessageBox>
#include <QTimer>
#include <QThread>
#include <QScrollBar>
#include <qnamespace.h>

MessageMenuGui::MessageMenuGui(Controller &controller, MainGui &mainGui, QWidget *parent)
    : controller_(controller), mainGui_(mainGui), QWidget(parent) {
    setupUI();
}

void MessageMenuGui::setupUI() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    sendButton_.setText("Send");
    backButton_.setText("Back");
    messageInput_.setPlaceholderText("Type your message here...");

    layout->addWidget(new QLabel("Friends List", this));
    layout->addWidget(&friendsList_);
    layout->addWidget(new QLabel("Chat Display", this));
    layout->addWidget(&chatDisplay_);
    layout->addWidget(new QLabel("Message Input", this));
    layout->addWidget(&messageInput_);
    layout->addWidget(&sendButton_);
    layout->addWidget(&backButton_);

    setLayout(layout);

    updateAll();

    connect(&friendsList_, &QListWidget::currentRowChanged, this, &MessageMenuGui::updateChat);
    connect(&sendButton_, &QPushButton::clicked, this, &MessageMenuGui::onSendMessage);
    connect(&backButton_, &QPushButton::clicked, this, &MessageMenuGui::onBack);
    connect(&mainGui_, &MainGui::updateConversations, this, &MessageMenuGui::updateChat);
    connect(&mainGui_, &MainGui::updateFriendsList, this, &MessageMenuGui::updateAll);
}

void MessageMenuGui::updateAll() {
    loadFriends();
    updateChat();
}

void MessageMenuGui::loadFriends() {
    friendsList_.clear();
    std::vector<bindings::User> friends = controller_.getFriendsList();

    for (const auto &friendUser : friends) {
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(friendUser.username));
        item->setData(Qt::UserRole, QVariant::fromValue(friendUser.userID));
        friendsList_.addItem(item);
    }
    if (friendsList_.count() > 0) {
        friendsList_.setCurrentRow(0);
    }
}

void MessageMenuGui::updateChat() {
    int friendIndex = friendsList_.currentRow();
    if (friendIndex >= 0) {
        loadMessages(friendIndex);
    } else {
        chatDisplay_.clear();
    }
}

void MessageMenuGui::loadMessages(int friendIndex) {
    QScrollBar *scrollBar = chatDisplay_.verticalScrollBar();
    int previousScrollValue = scrollBar->value();

    chatDisplay_.clear();

    std::vector<bindings::User> friends = controller_.getFriendsList();
    if (friendIndex < 0 || friendIndex >= static_cast<int>(friends.size())) return;

    auto [name, conversation] = controller_.getConversationWith(friends[friendIndex].userID);

    if (conversation.senderMessages.empty()) {
        chatDisplay_.setText("No messages yet");
    } else {
        QString chatHistory;
        for (const auto &[senderId, message] : conversation.senderMessages) {
            QString senderName = (senderId == friends[friendIndex].userID) ? QString::fromStdString(name) : "Me";
            chatHistory += senderName + ": " + QString::fromStdString(message) + "\n";
        }
        chatDisplay_.setText(chatHistory);
    }

    scrollBar->setValue(previousScrollValue);
}



void MessageMenuGui::onSendMessage() {
    int friendIndex = friendsList_.currentRow();
    if (friendIndex < 0) return;

    std::vector<bindings::User> friends = controller_.getFriendsList();
    if (friendIndex >= static_cast<int>(friends.size())) return;

    QString messageText = messageInput_.toPlainText().trimmed();
    if (messageText.isEmpty()) return;

    controller_.sendMessage(friends[friendIndex].userID, messageText.toStdString());
    messageInput_.clear();

    loadMessages(friendIndex);
}


void MessageMenuGui::onBack() {
    emit backToMainMenu();
}