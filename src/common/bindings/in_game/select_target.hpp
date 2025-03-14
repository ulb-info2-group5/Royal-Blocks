#ifndef BINDINGS_SELECT_TARGET_HPP
#define BINDINGS_SELECT_TARGET_HPP

#include "../binding_type.hpp"

#include "../../common/types/types.hpp"

#include <nlohmann/json.hpp>
namespace bindings {

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
