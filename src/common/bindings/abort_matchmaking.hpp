#ifndef ABORT_MATCHMAKING_HPP
#define ABORT_MATCHMAKING_HPP

#include "../binding_type.hpp"

#include <nlohmann/json.hpp>

namespace bindings {

    struct AbortMatchMaking {
        nlohmann::json to_json() const {
            return nlohmann::json{
                {"type", BindingType::AbortMatchMaking},
            };
        }

        static AbortMatchMaking from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::AbortMatchMaking) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            return AbortMatchMaking{};
        }
    };

} // namespace bindings

#endif // BINDINGS_ABORT_MATCHMAKING_HPP
