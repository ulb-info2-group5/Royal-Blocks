#ifndef BINDINGS_RANKING_HPP
#define BINDINGS_RANKING_HPP

#include "binding_type.hpp"

#include <nlohmann/json.hpp>
#include <string>

#include "../types/types.hpp"

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Bindings that contains the ranking (each player and their
     * associated score).
     */
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
