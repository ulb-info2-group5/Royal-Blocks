#ifndef BINDINGS_ROTATE_ACTIVE_HPP
#define BINDINGS_ROTATE_ACTIVE_HPP

#include "../binding_type.hpp"

#include <nlohmann/json.hpp>

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Binding sent by the client to rotate the active tetromino in a
     * certain direction.
     */
    struct RotateActive {
        bool rotateClockwise;

        nlohmann::json to_json() const {
            return nlohmann::json{{"type", BindingType::RotateActive},
                                  {"data",
                                   {
                                       {"rotateClockwise", rotateClockwise},
                                   }}};
        }

        static RotateActive from_json(const nlohmann::json &j) {
            if (j.at("type") != BindingType::RotateActive) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return RotateActive{data.at("rotateClockwise").get<bool>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_ROTATE_ACTIVE_HPP
