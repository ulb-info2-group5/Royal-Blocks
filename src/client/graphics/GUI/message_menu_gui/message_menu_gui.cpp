// File: message_menu_gui.cpp
// Authors: Jonas, Ernest, Rafaou

#include "message_menu_gui.hpp"

#include "../../../core/controller/controller.hpp"
#include "../main_gui.hpp"
#include "../qt_config/qt_config.hpp"

#include <QMessageBox>

MessageMenuGui::MessageMenuGui(Controller &controller, MainGui &mainGui, QWidget *parent)
    : controller_(controller), mainGui_(mainGui), QWidget(parent) {
    setupUI();
}

void MessageMenuGui::setupUI() {
    stack_ = new QStackedWidget(this);
    mainWidget_ = new QWidget(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget_);

    friendsList_ = new QListWidget(this);
    chatDisplay_ = new QTextBrowser(this);
    messageInput_ = new QTextEdit(this);

    sendButton_ = new QPushButton("Send", this);
    backButton_ = new QPushButton("Back", this);

    sidebarLayout_ = new QVBoxLayout();
    sidebarLayout_->addWidget(new QLabel("Friends List"));
    sidebarLayout_->addWidget(friendsList_);

    chatLayout_ = new QVBoxLayout();
    chatLayout_->addWidget(new QLabel("Conversation"));
    chatLayout_->addWidget(chatDisplay_);
    chatLayout_->addWidget(messageInput_);
    chatLayout_->addWidget(sendButton_);
    chatLayout_->addWidget(backButton_);

    mainLayout_ = new QHBoxLayout(mainWidget_);
    mainLayout_->addLayout(sidebarLayout_);
    mainLayout_->addLayout(chatLayout_);

    stack_->addWidget(mainWidget_);
    QVBoxLayout *globalLayout = new QVBoxLayout(this);
    globalLayout->addWidget(stack_);

    loadFriends();

    connect(friendsList_, &QListWidget::currentRowChanged, this, &MessageMenuGui::onFriendSelected);
    connect(sendButton_, &QPushButton::clicked, this, &MessageMenuGui::onSendMessage);
    connect(backButton_, &QPushButton::clicked, this, &MessageMenuGui::onBack);
}

void MessageMenuGui::loadFriends() {
    friendsList_->clear();
    auto friends = controller_.getFriendsList();

    for (const auto &friendUser : friends) {
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(friendUser.username));
        item->setData(Qt::UserRole, QVariant::fromValue(friendUser.userID));
        friendsList_->addItem(item);
    }
}

void MessageMenuGui::onFriendSelected() {
    int friendIndex = friendsList_->currentRow();
    if (friendIndex >= 0) {
        loadMessages(friendIndex);
    }
}

void MessageMenuGui::loadMessages(int friendIndex) {
    chatDisplay_->clear();
    auto friends = controller_.getFriendsList();
    if (friendIndex < 0 || friendIndex >= static_cast<int>(friends.size())) return;

    auto [name, conversation] = controller_.getConversationWith(friends[friendIndex].userID);

    if (conversation.senderMessages.empty()) {
        chatDisplay_->setText("No messages yet");
    } else {
        QString chatHistory;
        for (const auto &[senderId, message] : conversation.senderMessages) {
            QString senderName = (senderId == friends[friendIndex].userID) ? QString::fromStdString(name) : "Me";
            chatHistory += senderName + ": " + QString::fromStdString(message) + "\n";
        }
        chatDisplay_->setText(chatHistory);
    }
}

void MessageMenuGui::onSendMessage() {
    int friendIndex = friendsList_->currentRow();
    if (friendIndex < 0) return;

    auto friends = controller_.getFriendsList();
    if (friendIndex >= static_cast<int>(friends.size())) return;

    QString messageText = messageInput_->toPlainText().trimmed();
    if (messageText.isEmpty()) return;

    controller_.sendMessage(friends[friendIndex].userID, messageText.toStdString());
    messageInput_->clear();
    loadMessages(friendIndex);
}

void MessageMenuGui::onBack() {
    emit backToMainMenu();
}