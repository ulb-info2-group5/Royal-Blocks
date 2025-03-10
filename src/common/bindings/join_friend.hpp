#ifndef BINDINGS_JOIN_FRIEND_HPP
#define BINDINGS_JOIN_FRIEND_HPP

#include "in_game/select_target.hpp"

namespace bindings {

    struct JoinFriend {
        PlayerID friendId;

        nlohmann::json to_json() const {
            return nlohmann::json{{"type", BindingType::JoinFriend},
                                  {"data",
                                   {
                                       {"friendId", friendId},
                                   }}};
        }

        static JoinFriend from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::JoinFriend) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return JoinFriend{data.at("friendId").get<PlayerID>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_JOIN_FRIEND_HPP
