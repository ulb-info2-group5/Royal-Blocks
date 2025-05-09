#ifndef BINDINGS_FRIEND_REQUEST_HPP
#define BINDINGS_FRIEND_REQUEST_HPP

#include "binding_type.hpp"
#include "constants.hpp"

#include <nlohmann/json.hpp>

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Binding sent by a client to send a friend request to another user.
     */
    struct FriendRequest {
        std::string targetName;

        nlohmann::json to_json() const {
            return nlohmann::json{
                {PACKET_TYPE_FIELD, BindingType::FriendRequest},
                {"data",
                 {
                     {"targetName", targetName},
                 }}};
        }

        static FriendRequest from_json(const nlohmann::json &j) {
            if (j.at(PACKET_TYPE_FIELD) != BindingType::FriendRequest) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return FriendRequest{
                data.at("targetName").get<std::string>(),
            };
        }
    };

} // namespace bindings

#endif // BINDINGS_FRIEND_REQUEST_HPP
