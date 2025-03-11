#ifndef BINDINGS_BINDING_TYPE_HPP
#define BINDINGS_BINDING_TYPE_HPP

namespace bindings {

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

        // in game
        GameState,
        QuitGame,
        BigDrop,
        BuyBonus,
        BuyPenalty,
        EmptyPenaltyStash,
        HoldNextTetromino,
        MoveActive,
        RotateActive,
        SelectTarget,
    };

} // namespace bindings

#endif // BINDINGS_BINDING_TYPE_HPP
