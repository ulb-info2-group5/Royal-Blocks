// File: message_menu_gui.cpp
// Authors: Jonas, Ernest, Rafaou

#include "message_menu_gui.hpp"

#include "../../../core/controller/controller.hpp"
#include "../main_gui.hpp"

#include <QMessageBox>
#include <QTimer>
#include <QThread>
#include <QScrollBar>
#include <qboxlayout.h>

constexpr int FRIENDSLIST_WIDTH = 150;
constexpr int MESSAGE_INPUT_HEIGHT = 50;
constexpr char SEND_TEXT[] = "Send";
constexpr char BACK_TEXT[] = "Back";
constexpr char FRIENDSLIST_LABEL[] = "Friends List";
constexpr char CHAT_DISPLAY_LABEL[] = "Chat Display";
constexpr char MESSAGE_INPUT_LABEL[] = "Message Input";
constexpr char TYPE_MESSAGE_TEXT[] = "Type your message here...";
constexpr char NO_MESSAGES_TEXT[] = "No messages yet";

MessageMenuGui::MessageMenuGui(Controller &controller, MainGui &mainGui, QWidget *parent)
    : controller_(controller), mainGui_(mainGui), QWidget(parent) {
    setupUI();
}

void MessageMenuGui::setupUI() {
    QVBoxLayout *chatWriteLayout_ = new QVBoxLayout;
    QVBoxLayout *friendsListLayout_ = new QVBoxLayout;
    QHBoxLayout *mainLayout_ = new QHBoxLayout;
    QPushButton *sendButton_ = new QPushButton;
    QPushButton *backButton_ = new QPushButton;
    QLabel *friendsListLabel_ = new QLabel;
    QLabel *chatDisplayLabel_ = new QLabel;
    QLabel *messageInputLabel_ = new QLabel;

    friendsList_.setFixedWidth(FRIENDSLIST_WIDTH);
    messageInput_.setFixedHeight(MESSAGE_INPUT_HEIGHT);
    messageInput_.setAlignment(Qt::AlignHCenter);
    chatDisplay_.setReadOnly(true);

    sendButton_->setText(SEND_TEXT);
    backButton_->setText(BACK_TEXT);
    messageInput_.setPlaceholderText(TYPE_MESSAGE_TEXT);

    friendsListLabel_->setText(FRIENDSLIST_LABEL);
    friendsListLabel_->setAlignment(Qt::AlignCenter);
    chatDisplayLabel_->setText(CHAT_DISPLAY_LABEL);
    chatDisplayLabel_->setAlignment(Qt::AlignCenter);
    messageInputLabel_->setText(MESSAGE_INPUT_LABEL);
    messageInputLabel_->setAlignment(Qt::AlignCenter);

    friendsListLayout_->addWidget(friendsListLabel_);
    friendsListLayout_->addWidget(&friendsList_);
    chatWriteLayout_->addWidget(chatDisplayLabel_);
    chatWriteLayout_->addWidget(&chatDisplay_);
    chatWriteLayout_->addWidget(messageInputLabel_);
    chatWriteLayout_->addWidget(&messageInput_);
    chatWriteLayout_->addWidget(sendButton_);
    chatWriteLayout_->addWidget(backButton_);

    mainLayout_->addLayout(friendsListLayout_);
    mainLayout_->addLayout(chatWriteLayout_);
    mainLayout_->setAlignment(Qt::AlignCenter);

    setLayout(mainLayout_);

    updateAll();

    connect(&friendsList_, &QListWidget::currentRowChanged, this, &MessageMenuGui::updateChat);
    connect(sendButton_, &QPushButton::clicked, this, &MessageMenuGui::onSendMessage);
    connect(backButton_, &QPushButton::clicked, this, &MessageMenuGui::onBack);
    connect(&mainGui_, &MainGui::updateConversations, this, &MessageMenuGui::updateChat);
    connect(&mainGui_, &MainGui::updateFriendsList, this, &MessageMenuGui::updateAll);
    connect(&messageInput_, &QLineEdit::returnPressed, this, &MessageMenuGui::onEnterKeyPressedInInput);
}

void MessageMenuGui::onEnterKeyPressedInInput() {
    if (messageInput_.hasFocus() && !messageInput_.text().isEmpty()) {
        onSendMessage();
    }
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
        chatDisplay_.setText(NO_MESSAGES_TEXT);
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

    QString messageText = messageInput_.text().trimmed();
    if (messageText.isEmpty()) return;

    controller_.sendMessage(friends[friendIndex].userID, messageText.toStdString());
    messageInput_.clear();

    loadMessages(friendIndex);
}

void MessageMenuGui::onBack() {
    emit backToMainMenu();
}