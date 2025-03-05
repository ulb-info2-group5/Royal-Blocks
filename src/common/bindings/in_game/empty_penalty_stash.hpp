#ifndef EMPTY_PENALTY_STASH_HPP
#define EMPTY_PENALTY_STASH_HPP

#include "../bindings.hpp"

#include <nlohmann/json.hpp>

namespace bindings {

    struct EmptyPenaltyStash {
        nlohmann::json to_json() const {
            return nlohmann::json{
                {"type", BindingType::EmptyPenaltyStash},
            };
        }

        static EmptyPenaltyStash from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::EmptyPenaltyStash) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            return EmptyPenaltyStash{};
        }
    };

} // namespace bindings

#endif // EMPTY_PENALTY_STASH_HPP
