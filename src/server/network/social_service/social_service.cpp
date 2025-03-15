#include "social_service.hpp"

// ========== SocialService class ==========

SocialService::SocialService(std::shared_ptr<FriendsManager>& friendsManager, std::shared_ptr<MessagesManager> &messagesManager ) 
: friendsManager_{friendsManager}, messagesManager_{messagesManager} {

} 

void SocialService::handleMessages(UserID senderID ,bindings::Message message ){

}
void SocialService::handleFriendRequest(UserID senderID, bindings::FriendRequest friendRequest, std::shared_ptr<AccountManager>& accountManager){
    
    friendsManager_->addPendingFriendRequest(static_cast<int>(senderID), static_cast<int>(accountManager->getUserId(friendRequest.targetName)));
    
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

bindings::PendingFriendRequests SocialService::getPendignsFriendRequests(UserID userID, GetUser getUser){
    bindings::PendingFriendRequests pendingsFriendRequests;
    for (auto id : friendsManager_->getPendingFriendRequest(userID) ){
        pendingsFriendRequests.requests.push_back(getUser(id));
    }
    return pendingsFriendRequests;
}