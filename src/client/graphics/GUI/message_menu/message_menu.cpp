// File: message_menu_gui.cpp
// Authors: Jonas, Ernest, Rafaou

#include "message_menu.hpp"

#include "../../../core/controller/controller.hpp"
#include "../tetris_window.hpp"

#include <QBoxLayout>
#include <QMessageBox>
#include <QScrollBar>
#include <QTimer>

namespace GUI {

    inline constexpr int FRIENDSLIST_WIDTH = 150;
    inline constexpr int MESSAGE_INPUT_HEIGHT = 30;
    inline constexpr char SEND_TEXT[] = "Send";
    inline constexpr char BACK_TEXT[] = "Back";
    inline constexpr char FRIENDSLIST_LABEL[] = "Friends List";
    inline constexpr char CHAT_DISPLAY_LABEL[] = "Chat Display";
    inline constexpr char MESSAGE_INPUT_LABEL[] = "Message Input";
    inline constexpr char TYPE_MESSAGE_TEXT[] = "Type your message here...";
    inline constexpr char NO_MESSAGES_TEXT[] = "No messages yet";

    MessageMenu::MessageMenu(Controller &controller, TetrisWindow &tetrisWindow,
                             QWidget *parent)
        : QWidget(parent), controller_(controller),
          tetrisWindow_(tetrisWindow) {
        setupUI();
    }

    void MessageMenu::setupUI() {
        QVBoxLayout *chatWriteLayout = new QVBoxLayout();
        QVBoxLayout *friendsListLayout = new QVBoxLayout();
        QHBoxLayout *mainLayout = new QHBoxLayout();
        QPushButton *sendButton = new QPushButton(this);
        sendButton->setAutoDefault(true);
        QPushButton *backButton = new QPushButton(this);
        backButton->setAutoDefault(true);
        QLabel *friendsListLabel = new QLabel(this);
        QLabel *chatDisplayLabel = new QLabel(this);
        QLabel *messageInputLabel = new QLabel(this);

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
        connect(&tetrisWindow_, &TetrisWindow::updateConversations, this,
                &MessageMenu::updateChat);
        connect(&tetrisWindow_, &TetrisWindow::updateFriendsList, this,
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
        int currentRow = friendsList_.currentRow();  // Current friend index
        QVariant currentUserId;
        if (currentRow >= 0) {
            QListWidgetItem *currentItem = friendsList_.item(currentRow);
            currentUserId = currentItem->data(Qt::UserRole);
        }
        friendsList_.clear();
        std::vector<bindings::User> friends = controller_.getFriendsList();

        for (const auto &friendUser : friends) {
            QListWidgetItem *item = new QListWidgetItem(
                QString::fromStdString(friendUser.username));
            item->setData(Qt::UserRole, QVariant::fromValue(friendUser.userID));
            friendsList_.addItem(item);
        }

        // Restore the previous selection if it is still valid
        if (currentUserId.isValid()) {
            for (int i = 0; i < friendsList_.count(); ++i) {
                QListWidgetItem *item = friendsList_.item(i);
                if (item->data(Qt::UserRole) == currentUserId) {
                    friendsList_.setCurrentRow(i);
                    return;
                }
            }
        }

        // If no valid selection, select the first friend
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

    void MessageMenu::onBack() { 
        QTimer::singleShot(0, this, [this]() {
            emit backToMainMenu();
        }); 
    }

} // namespace GUI
