#ifndef BINDINGS_EMPTY_PENALTY_STASH_HPP
#define BINDINGS_EMPTY_PENALTY_STASH_HPP

#include "../binding_type.hpp"
#include "../constants.hpp"

#include <nlohmann/json.hpp>

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Binding sent by the client to empty the penalty stash.
     */
    struct EmptyPenaltyStash {
        nlohmann::json to_json() const {
            return nlohmann::json{
                {PACKET_TYPE_FIELD, BindingType::EmptyPenaltyStash},
            };
        }

        static EmptyPenaltyStash from_json(const nlohmann::json &j) {
            if (j.at(PACKET_TYPE_FIELD) != BindingType::EmptyPenaltyStash) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            return EmptyPenaltyStash{};
        }
    };

} // namespace bindings

#endif // BINDINGS_EMPTY_PENALTY_STASH_HPP
