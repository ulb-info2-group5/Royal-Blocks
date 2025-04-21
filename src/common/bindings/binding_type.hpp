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
