#ifndef ABORT_MATCHMAKING_HPP
#define ABORT_MATCHMAKING_HPP

#include "binding_type.hpp"
#include "constants.hpp"

#include <nlohmann/json.hpp>

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Binding sent by the client when the player wants to abort the
     * matchmaking process.
     */
    struct AbortMatchMaking {
        nlohmann::json to_json() const {
            return nlohmann::json{
                {PACKET_TYPE_FIELD, BindingType::AbortMatchMaking},
            };
        }

        static AbortMatchMaking from_json(const nlohmann::json &j) {
            if (j.at(PACKET_TYPE_FIELD) != BindingType::AbortMatchMaking) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            return AbortMatchMaking{};
        }
    };

} // namespace bindings

#endif // BINDINGS_ABORT_MATCHMAKING_HPP
