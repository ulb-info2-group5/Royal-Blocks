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

#ifndef SOCIAL_SERVICE_HPP
#define SOCIAL_SERVICE_HPP

#include <asio.hpp>
#include <nlohmann/json.hpp>

#include "../database/account_manager/account_manager.hpp"
#include "../database/friends_manager/friends_manager.hpp"
#include "../database/messages_manager/messages_manager.hpp"

#include "../../common/bindings/user.hpp"

#include "../../common/bindings/conversations.hpp"
#include "../../common/bindings/friend_request.hpp"
#include "../../common/bindings/friends_list.hpp"
#include "../../common/bindings/handle_friend_request.hpp"
#include "../../common/bindings/message.hpp"
#include "../../common/bindings/pending_friend_requests.hpp"
#include "../../common/bindings/remove_friend.hpp"

/**
 * @class SocialService
 *
 * @brief Instance to do all the operations concerning the friends' resquests,
 * the interaction between accounts through messages on the database
 *
 */
class SocialService {
    using GetUser = std::function<bindings::User(UserID)>;

  private:
    std::shared_ptr<FriendsManager> friendsManager_;
    std::shared_ptr<MessagesManager> messagesManager_;
    GetUser getUser_;

  public:
    SocialService(std::shared_ptr<FriendsManager> &friendsManager,
                  std::shared_ptr<MessagesManager> &messagesManager,
                  GetUser getUser);
    ~SocialService() = default;

    /**
     * @brief add the message from the sender to the recipient on the database
     *
     * @param senderID userID of the sender
     * @param message binding with the message's content and recipient's userID
     */
    void handleMessages(UserID senderID, bindings::Message message);

    /**
     * @brief send a friend request from the sender to the recipient on the
     * database
     *
     * @param senderID sender's userID
     * @param friendRequest binding for the friend requestion containing the
     * recipient's userID
     * @param AccountManager shared pointer of the database"s account manager
     */
    void handleFriendRequest(UserID senderID,
                             bindings::FriendRequest friendRequest,
                             std::shared_ptr<AccountManager> &AccountManager);

    /**
     * @brief update the state of a friend request (deny or approval)
     *
     * @param senderID sender's userID
     * @param handleFriendRequest binding containing the friend request's
     * response
     */
    void handleHandleFriendRequest(
        UserID senderID, bindings::HandleFriendRequest handleFrienddRequest);

    /**
     * @brief remove a friend of a friends' list's account
     *
     * @param senderID sender's userID
     * @param removeFriend binding containing the informations of the userID to
     * suppress it on the friends' list
     */
    void handleRemoveFriend(UserID senderID,
                            bindings::RemoveFriend removeFriend);

    // === getters ===

    /**
     * @brief returns the pending friend requests concerning an userID
     */
    bindings::PendingFriendRequests getPendignsFriendRequests(UserID userID);

    /**
     * @brief returns the friends' list concerning an userID
     */
    bindings::FriendsList getFriendsList(UserID userID);

    /**
     * @brief returns the conversations concerning an userID
     */
    bindings::Conversations
    getConversations(UserID userID,
                     std::shared_ptr<AccountManager> &accountManager);

    /**
     * @brief returns the userID of the friends' list concerning an userID
     */
    std::vector<int> getFriendIdsList(UserID userID);
};

#endif
