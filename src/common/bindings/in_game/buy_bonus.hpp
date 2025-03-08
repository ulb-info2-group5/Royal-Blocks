#ifndef BINDINGS_BUY_BONUS_HPP
#define BINDINGS_BUY_BONUS_HPP

#include "../../tetris_royal_lib/effect/bonus/bonus_type.hpp"

#include "../binding_type.hpp"

#include <nlohmann/json.hpp>

namespace bindings {

    struct BuyBonus {
        BonusType bonusType;

        nlohmann::json to_json() const {
            return nlohmann::json{{"type", BindingType::BuyBonus},
                                  {"data",
                                   {
                                       {"bonusType", bonusType},
                                   }}};
        }

        static BuyBonus from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::BuyBonus) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return BuyBonus{data.at("bonusType").get<BonusType>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_BUY_BONUS_HPP
