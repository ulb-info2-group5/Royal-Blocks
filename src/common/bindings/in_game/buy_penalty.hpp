#ifndef BINDINGS_BUY_PENALTY_HPP
#define BINDINGS_BUY_PENALTY_HPP

#include "../../tetris_royal_lib/effect/penalty/penalty_type.hpp"

#include "../binding_type.hpp"

#include <nlohmann/json.hpp>

namespace bindings {

    struct BuyPenalty {
        PenaltyType penaltyType;
        bool stashForLater;

        nlohmann::json to_json() const {
            return nlohmann::json{{"type", BindingType::BuyPenalty},
                                  {"data",
                                   {
                                       {"penaltyType", penaltyType},
                                       {"stashForLater", stashForLater},
                                   }}};
        }

        static BuyPenalty from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::BuyPenalty) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return BuyPenalty{data.at("penaltyType").get<PenaltyType>(),
                              data.at("stashForLater").get<bool>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_BUY_PENALTY_HPP
