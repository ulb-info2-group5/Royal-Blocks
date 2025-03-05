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
    };

} // namespace bindings

#endif // BINDING_TYPE_HPP
