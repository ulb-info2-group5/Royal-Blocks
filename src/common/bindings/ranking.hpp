/*
 * This file is part of Royal Blocks.
 *
 * Royal Blocks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Royal Blocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Royal Blocks.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef BINDINGS_RANKING_HPP
#define BINDINGS_RANKING_HPP

#include "binding_type.hpp"

#include <nlohmann/json.hpp>
#include <string>

#include "../types/types.hpp"
#include "constants.hpp"

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
            return nlohmann::json{{PACKET_TYPE_FIELD, BindingType::Ranking},
                                  {"data",
                                   {
                                       {"ranking", ranking},
                                   }}};
        }

        static Ranking from_json(const nlohmann::json &j) {
            if (j.at(PACKET_TYPE_FIELD) != BindingType::Ranking) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return Ranking{data.at("ranking").get<std::vector<PlayerScore>>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_RANKING_HPP
