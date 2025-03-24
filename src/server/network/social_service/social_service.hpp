#ifndef SOCIAL_SERVICE_HPP
#define SOCIAL_SERVICE_HPP

#include <boost/asio.hpp>
#include <iostream>
#include <mutex>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>


#include "../../database/account_manager/account_manager.hpp"
#include "../../database/database_manager/database_manager.hpp"
#include "../../database/friends_manager/friends_manager.hpp"
#include "../../database/messages_manager/messages_manager.hpp"

#include "../../../common/bindings/user_state.hpp"
#include "../../../common/bindings/user.hpp"

#include "../../../common/bindings/binding_type.hpp"
#include "../../../common/bindings/message.hpp"
#include "../../../common/bindings/conversation.hpp"
#include "../../../common/bindings/conversations.hpp"
#include "../../../common/bindings/friends_list.hpp"
#include "../../../common/bindings/friend_request.hpp"
#include "../../../common/bindings/remove_friend.hpp"
#include "../../../common/bindings/handle_friend_request.hpp"
#include "../../../common/bindings/pending_friend_requests.hpp"




class SocialService{
    using GetUser = std::function<bindings::User(UserID)>;
    private:
        std::shared_ptr<FriendsManager> friendsManager_;
        std::shared_ptr<MessagesManager> messagesManager_;
        GetUser getUser_;

    public:
        SocialService(std::shared_ptr<FriendsManager>& friendsManager, std::shared_ptr<MessagesManager> &messagesManager, GetUser getUser );
        ~SocialService() = default;

        void handleMessages(UserID senderID ,bindings::Message message );
        void handleFriendRequest(UserID senderID, bindings::FriendRequest friendRequest, std::shared_ptr<AccountManager>& AccountManager);
        void handleHandleFriendRequest(UserID senderID, bindings::HandleFriendRequest handleFrienddRequest);
        void handleRemoveFriend(UserID senderID, bindings::RemoveFriend removeFriend);

        // === getters ===
        bindings::PendingFriendRequests getPendignsFriendRequests(UserID userID);

        bindings::FriendsList getFriendsList(UserID userID);


        bindings::Conversations getConversations(UserID userID, std::shared_ptr<AccountManager>& accountManager);

        std::vector<int> getFriendIdsList(UserID userID);



};


#endif 

