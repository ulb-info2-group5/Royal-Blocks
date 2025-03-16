#include "social_service.hpp"

// ========== SocialService class ==========

SocialService::SocialService(std::shared_ptr<FriendsManager>& friendsManager, std::shared_ptr<MessagesManager> &messagesManager , GetUser getUser) 
: friendsManager_{friendsManager}, messagesManager_{messagesManager}, getUser_{getUser} {

} 

void SocialService::handleMessages(UserID senderID ,bindings::Message message){
    std::cout << "debug m 1" << std::endl;
    if (getUser_(message.recipientId).state != bindings::State::Offline){
        // TODO : depending on the choice of client-side message implementation 
        // send the message to the recipient or not 
    }
    std::cout << "debug m 2" << std::endl;
    messagesManager_->addMessage(senderID, message.recipientId, message.content);
    std::cout << "debug m 3" << std::endl;
}

void SocialService::handleFriendRequest(UserID senderID, bindings::FriendRequest friendRequest, std::shared_ptr<AccountManager>& accountManager){
    std::cout << "debug 0" << std::endl;
    if (accountManager->checkUsernameExists(friendRequest.targetName)){
        std::cout << "debug 1" << std::endl;
        friendsManager_->addPendingFriendRequest(static_cast<int>(senderID), static_cast<int>(accountManager->getUserId(friendRequest.targetName)));
    }
}

void SocialService::handleHandleFriendRequest(UserID senderID, bindings::HandleFriendRequest handleFrienddRequest){
    if (handleFrienddRequest.action == bindings::HandleFriendRequest::Action::Accept){
        friendsManager_->addFriend(static_cast<int>(senderID), static_cast<int>(handleFrienddRequest.user.userID) );
    }
    friendsManager_->removePendingFriendRequest(static_cast<int>(senderID), static_cast<int>(handleFrienddRequest.user.userID));
}


void SocialService::handleRemoveFriend(UserID senderID, bindings::RemoveFriend removeFriend){
    friendsManager_->removeFriend(static_cast<int>(senderID), static_cast<int>(removeFriend.userID));
}




bindings::PendingFriendRequests SocialService::getPendignsFriendRequests(UserID userID){
    bindings::PendingFriendRequests pendingsFriendRequests;
    for (auto id : friendsManager_->getPendingFriendRequest(userID) ){
        pendingsFriendRequests.requests.push_back(getUser_(id));
    }
    return pendingsFriendRequests;
}


bindings::FriendsList SocialService::getFriendsList(UserID userID){
    bindings::FriendsList friends;
    std::cout << "friends : " << userID << std::endl; 
    for (auto id : friendsManager_->getFriends(userID)){
        std::cout << id << std::endl;
        friends.friendsList.push_back(getUser_(id));
    }
    return friends;
}



bindings::Conversations SocialService::getConversations(UserID userID){
    bindings::Conversations conversations;
    for (auto id : messagesManager_->getAllUser(userID)){
        //
    }
    return conversations;
}