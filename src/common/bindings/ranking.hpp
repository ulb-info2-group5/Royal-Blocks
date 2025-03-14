#ifndef BINDINGS_RANKING_HPP
#define BINDINGS_RANKING_HPP

#include "binding_type.hpp"

#include <nlohmann/json.hpp>
#include <string>

#include "../types/types.hpp"

namespace bindings {

    struct Ranking {
        using PlayerScore = std::pair<std::string, Score>;

        std::vector<PlayerScore> ranking;

        nlohmann::json to_json() const {
            return nlohmann::json{{"type", BindingType::Ranking},
                                  {"data",
                                   {
                                       {"ranking", ranking},
                                   }}};
        }

        static Ranking from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::Ranking) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return Ranking{data.at("ranking").get<std::vector<PlayerScore>>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_RANKING_HPP
