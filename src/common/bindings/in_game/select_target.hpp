#ifndef SELECT_TARGET_HPP
#define SELECT_TARGET_HPP

#include "../../tetris_lib/tetromino/tetromino.hpp"

#include "../bindings.hpp"

#include <cstddef>

using PlayerID = size_t;

namespace bindings {

    struct SelectTarget {
        PlayerID targetId;

        nlohmann::json to_json() const {
            return nlohmann::json{{"type", BindingType::SelectTarget},
                                  {"data",
                                   {
                                       {"targetId", targetId},
                                   }}};
        }

        static SelectTarget from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::SelectTarget) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return SelectTarget{data.at("targetId").get<PlayerID>()};
        }
    };

} // namespace bindings

#endif // SELECT_TARGET_HPP
