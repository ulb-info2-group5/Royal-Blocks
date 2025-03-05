#ifndef BIG_DROP_HPP
#define BIG_DROP_HPP

#include "../bindings.hpp"

#include <nlohmann/json.hpp>

namespace bindings {

    struct BigDrop {
        nlohmann::json to_json() const {
            return nlohmann::json{
                {"type", BindingType::BigDrop},
            };
        }

        static BigDrop from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::BigDrop) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            return BigDrop{};
        }
    };

} // namespace bindings

#endif // BIG_DROP_HPP
