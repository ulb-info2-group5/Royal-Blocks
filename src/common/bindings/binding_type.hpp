#ifndef BINDINGS_BINDING_TYPE_HPP
#define BINDINGS_BINDING_TYPE_HPP

namespace bindings {

    enum class BindingType {
        Authentication,
        AuthenticationResponse,
        FriendRequest,
        Message,
        Registration,
        RegistrationResponse,
        User,

        // in game
        GameState,
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
