#ifndef BINDINGS_REMOVE_CLIENT_HPP
#define BINDINGS_REMOVE_CLIENT_HPP

#include "../../common/bindings/binding_type.hpp"

#include <nlohmann/json.hpp>

namespace bindings {
    struct RemoveClient {
        nlohmann::json to_json() const {
            return nlohmann::json{{"type", BindingType::RemoveClient}};
        }
        static RemoveClient from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::RemoveClient) {
                throw std::runtime_error("Invalid type field in JSON");
            }
        }
    };

} // namespace bindings

#endif // BINDINGS_REMOVE_CLIENT_HPP
