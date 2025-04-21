#ifndef BINDINGS_BIG_DROP_HPP
#define BINDINGS_BIG_DROP_HPP

#include "../binding_type.hpp"

#include <nlohmann/json.hpp>

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Binding sent by the client to make a bigDrop action.
     */
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

#endif // BINDINGS_BIG_DROP_HPP
