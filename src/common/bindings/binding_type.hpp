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

#ifndef BINDINGS_BINDING_TYPE_HPP
#define BINDINGS_BINDING_TYPE_HPP

/**
 * @brief The bindings namespace defines the communication layer between
 * the server and the clients. All packets exchanged are represented as
 * JSON "bindings", each containing a type field that allows us to identify
 * the packet's content and deserialize it accordingly.
 */
namespace bindings {

    /**
     * @brief The different types of bindings.
     */
    enum class BindingType {
        Authentication,
        AuthenticationResponse,
        FriendsList,
        FriendRequest,
        RemoveFriend,
        Message,
        Registration,
        RegistrationResponse,
        User,
        Ranking,
        JoinGame,
        Conversation,
        Conversations,
        CreateGame,
        HandleFriendRequest,
        PendingFriendRequests,
        ChangeUsername,
        ChangePassword,
        ChangeUsernameResponse,
        AbortMatchMaking,
        ViewGame,

        // in game
        GameState,
        GameStateViewer,
        QuitGame,
        BigDrop,
        BuyBonus,
        BuyPenalty,
        EmptyPenaltyStash,
        HoldActiveTetromino,
        MoveActive,
        RotateActive,
        SelectTarget,

        // intern to server
        RemoveClient,
    };

} // namespace bindings

#endif // BINDINGS_BINDING_TYPE_HPP
