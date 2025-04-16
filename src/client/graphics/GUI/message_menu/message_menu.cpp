// File: message_menu_gui.cpp
// Authors: Jonas, Ernest, Rafaou

#include "message_menu.hpp"

#include "../../../core/controller/controller.hpp"
#include "../main_gui.hpp"

#include <QBoxLayout>
#include <QMessageBox>
#include <QScrollBar>
#include <QThread>
#include <QTimer>

namespace GUI {

    constexpr int FRIENDSLIST_WIDTH = 150;
    constexpr int MESSAGE_INPUT_HEIGHT = 50;
    constexpr char SEND_TEXT[] = "Send";
    constexpr char BACK_TEXT[] = "Back";
    constexpr char FRIENDSLIST_LABEL[] = "Friends List";
    constexpr char CHAT_DISPLAY_LABEL[] = "Chat Display";
    constexpr char MESSAGE_INPUT_LABEL[] = "Message Input";
    constexpr char TYPE_MESSAGE_TEXT[] = "Type your message here...";
    constexpr char NO_MESSAGES_TEXT[] = "No messages yet";

    MessageMenu::MessageMenu(Controller &controller, MainGui &mainGui,
                             QWidget *parent)
        : QWidget(parent), controller_(controller), mainGui_(mainGui) {
        setupUI();
    }

    void MessageMenu::setupUI() {
        QVBoxLayout *chatWriteLayout = new QVBoxLayout;
        QVBoxLayout *friendsListLayout = new QVBoxLayout;
        QHBoxLayout *mainLayout = new QHBoxLayout;
        QPushButton *sendButton = new QPushButton;
        sendButton->setAutoDefault(true);
        QPushButton *backButton = new QPushButton;
        backButton->setAutoDefault(true);
        QLabel *friendsListLabel = new QLabel;
        QLabel *chatDisplayLabel = new QLabel;
        QLabel *messageInputLabel = new QLabel;

        friendsList_.setFixedWidth(FRIENDSLIST_WIDTH);
        messageInput_.setFixedHeight(MESSAGE_INPUT_HEIGHT);
        messageInput_.setAlignment(Qt::AlignHCenter);
        chatDisplay_.setReadOnly(true);

        sendButton->setText(SEND_TEXT);
        backButton->setText(BACK_TEXT);
        messageInput_.setPlaceholderText(TYPE_MESSAGE_TEXT);

        friendsListLabel->setText(FRIENDSLIST_LABEL);
        friendsListLabel->setAlignment(Qt::AlignCenter);
        chatDisplayLabel->setText(CHAT_DISPLAY_LABEL);
        chatDisplayLabel->setAlignment(Qt::AlignCenter);
        messageInputLabel->setText(MESSAGE_INPUT_LABEL);
        messageInputLabel->setAlignment(Qt::AlignCenter);

        friendsListLayout->addWidget(friendsListLabel);
        friendsListLayout->addWidget(&friendsList_);
        chatWriteLayout->addWidget(chatDisplayLabel);
        chatWriteLayout->addWidget(&chatDisplay_);
        chatWriteLayout->addWidget(messageInputLabel);
        chatWriteLayout->addWidget(&messageInput_);
        chatWriteLayout->addWidget(sendButton);
        chatWriteLayout->addWidget(backButton);

        mainLayout->addLayout(friendsListLayout);
        mainLayout->addLayout(chatWriteLayout);
        mainLayout->setAlignment(Qt::AlignCenter);

        setLayout(mainLayout);

        updateAll();

        connect(&friendsList_, &QListWidget::currentRowChanged, this,
                &MessageMenu::updateChat);
        connect(sendButton, &QPushButton::clicked, this,
                &MessageMenu::onSendMessage);
        connect(backButton, &QPushButton::clicked, this, &MessageMenu::onBack);
        connect(&mainGui_, &MainGui::updateConversations, this,
                &MessageMenu::updateChat);
        connect(&mainGui_, &MainGui::updateFriendsList, this,
                &MessageMenu::updateAll);
        connect(&messageInput_, &QLineEdit::returnPressed, this,
                &MessageMenu::onEnterKeyPressedInInput);
    }

    void MessageMenu::onEnterKeyPressedInInput() {
        if (messageInput_.hasFocus() && !messageInput_.text().isEmpty()) {
            onSendMessage();
        }
    }

    void MessageMenu::updateAll() {
        loadFriends();
        updateChat();
    }

    void MessageMenu::loadFriends() {
        friendsList_.clear();
        std::vector<bindings::User> friends = controller_.getFriendsList();

        for (const auto &friendUser : friends) {
            QListWidgetItem *item = new QListWidgetItem(
                QString::fromStdString(friendUser.username));
            item->setData(Qt::UserRole, QVariant::fromValue(friendUser.userID));
            friendsList_.addItem(item);
        }
        if (friendsList_.count() > 0) {
            friendsList_.setCurrentRow(0);
        }
    }

    void MessageMenu::updateChat() {
        int friendIndex = friendsList_.currentRow();
        if (friendIndex >= 0) {
            loadMessages(friendIndex);
        } else {
            chatDisplay_.clear();
        }
    }

    void MessageMenu::loadMessages(int friendIndex) {
        QScrollBar *scrollBar = chatDisplay_.verticalScrollBar();
        int previousScrollValue = scrollBar->value();

        chatDisplay_.clear();

        std::vector<bindings::User> friends = controller_.getFriendsList();
        if (friendIndex < 0 || friendIndex >= static_cast<int>(friends.size()))
            return;

        auto [name, conversation] =
            controller_.getConversationWith(friends[friendIndex].userID);

        if (conversation.senderMessages.empty()) {
            chatDisplay_.setText(NO_MESSAGES_TEXT);
        } else {
            QString chatHistory;
            for (const auto &[senderId, message] :
                 conversation.senderMessages) {
                QString senderName = (senderId == friends[friendIndex].userID)
                                         ? QString::fromStdString(name)
                                         : "Me";
                chatHistory +=
                    senderName + ": " + QString::fromStdString(message) + "\n";
            }
            chatDisplay_.setText(chatHistory);
        }

        scrollBar->setValue(previousScrollValue);
    }

    void MessageMenu::onSendMessage() {
        int friendIndex = friendsList_.currentRow();
        if (friendIndex < 0) return;

        std::vector<bindings::User> friends = controller_.getFriendsList();
        if (friendIndex >= static_cast<int>(friends.size())) return;

        QString messageText = messageInput_.text().trimmed();
        if (messageText.isEmpty()) return;

        controller_.sendMessage(friends[friendIndex].userID,
                                messageText.toStdString());
        messageInput_.clear();

        loadMessages(friendIndex);
    }

    void MessageMenu::onBack() { emit backToMainMenu(); }

} // namespace GUI
