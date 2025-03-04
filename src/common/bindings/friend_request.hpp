#ifndef FRIEND_REQUEST_HPP
#define FRIEND_REQUEST_HPP

#include <nlohmann/json.hpp>

using PlayerID = size_t;

namespace bindings {

    struct FriendRequest {
        enum class FriendRequestType { Add, Remove };

        PlayerID requesterId;
        PlayerID targetId;
        FriendRequestType friendRequestType;

        nlohmann::json to_json() const {
            return nlohmann::json{{"type", "friendRequest"},
                                  {"data",
                                   {
                                       {"requesterId", requesterId},
                                       {"targetId", targetId},
                                       {"friendRequestType", friendRequestType},
                                   }}};
        }

        static FriendRequest from_json(const nlohmann::json &j) {
            if (j.at("type") != "friendRequest") {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return FriendRequest{
                data.at("requesterId").get<PlayerID>(),
                data.at("targetId").get<PlayerID>(),
                data.at("friendRequestType").get<FriendRequestType>()};
        }
    };

} // namespace bindings

#endif // FRIEND_REQUEST_HPP
