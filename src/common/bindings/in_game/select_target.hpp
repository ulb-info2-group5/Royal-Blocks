#ifndef BINDINGS_SELECT_TARGET_HPP
#define BINDINGS_SELECT_TARGET_HPP

#include "../binding_type.hpp"

#include "../../types/types.hpp"

#include <nlohmann/json.hpp>

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Binding sent by the client to select a player as current target.
     */
    struct SelectTarget {
        UserID targetId;

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
            return SelectTarget{data.at("targetId").get<UserID>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_SELECT_TARGET_HPP
