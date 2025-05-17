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

#include "social_service.hpp"

// ========== SocialService class ==========

SocialService::SocialService(std::shared_ptr<FriendsManager> &friendsManager,
                             std::shared_ptr<MessagesManager> &messagesManager,
                             GetUser getUser)
    : friendsManager_{friendsManager}, messagesManager_{messagesManager},
      getUser_{getUser} {}

void SocialService::handleMessages(UserID senderID, bindings::Message message) {
    messagesManager_->addMessage(senderID, message.recipientId,
                                 message.content);
}

void SocialService::handleFriendRequest(
    UserID senderID, bindings::FriendRequest friendRequest,
    std::shared_ptr<AccountManager> &accountManager) {
    if (accountManager->checkUsernameExists(friendRequest.targetName)) {
        friendsManager_->addPendingFriendRequest(
            static_cast<int>(senderID),
            accountManager->getUserId(friendRequest.targetName));
    }
}

void SocialService::handleHandleFriendRequest(
    UserID senderID, bindings::HandleFriendRequest handleFrienddRequest) {
    if (handleFrienddRequest.action
        == bindings::HandleFriendRequest::Action::Accept) {
        friendsManager_->addFriend(senderID, handleFrienddRequest.userId);
    }

    friendsManager_->removePendingFriendRequest(senderID,
                                                handleFrienddRequest.userId);
}

void SocialService::handleRemoveFriend(UserID senderID,
                                       bindings::RemoveFriend removeFriend) {
    friendsManager_->removeFriend(static_cast<int>(senderID),
                                  static_cast<int>(removeFriend.userID));
}

bindings::PendingFriendRequests
SocialService::getPendignsFriendRequests(UserID userID) {
    bindings::PendingFriendRequests pendingsFriendRequests;
    for (auto id : friendsManager_->getPendingFriendRequest(userID)) {
        pendingsFriendRequests.requests.push_back(getUser_(id));
    }
    return pendingsFriendRequests;
}

bindings::FriendsList SocialService::getFriendsList(UserID userID) {
    bindings::FriendsList friends;
    for (auto id : friendsManager_->getFriends(userID)) {
        friends.friendsList.push_back(getUser_(id));
    }
    return friends;
}

bindings::Conversations SocialService::getConversations(
    UserID userID, std::shared_ptr<AccountManager> &accountManager) {
    bindings::Conversations conversations;
    for (auto id : messagesManager_->getAllUser(userID)) {
        if (messagesManager_->isThereDiscussion(userID, id)) {
            std::optional<bindings::Conversation> optDiscussion =
                messagesManager_->getDiscussion(userID, id);
            if (optDiscussion.has_value()) {
                conversations.conversationsById.insert(
                    {static_cast<unsigned long>(id),
                     {accountManager->getUsername(id), optDiscussion.value()}});
            }
        }
    }
    return conversations;
}

std::vector<int> SocialService::getFriendIdsList(UserID userID) {
    return friendsManager_->getFriends(userID);
}
