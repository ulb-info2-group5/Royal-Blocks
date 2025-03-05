#ifndef BINDING_TYPE_HPP
#define BINDING_TYPE_HPP

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

#endif // BINDING_TYPE_HPP
