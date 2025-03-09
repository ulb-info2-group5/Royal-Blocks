#ifndef BINDINGS_RANKING_HPP
#define BINDINGS_RANKING_HPP

#include "binding_type.hpp"

#include <nlohmann/json.hpp>
#include <vector>

namespace bindings {

    struct Ranking {
        std::vector<std::string> ranking;

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
            return Ranking{data.at("ranking").get<std::vector<std::string>>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_RANKING_HPP
