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

#ifndef BINDINGS_CHANGE_USERNAME_RESPONSE_HPP
#define BINDINGS_CHANGE_USERNAME_RESPONSE_HPP

#include "binding_type.hpp"
#include "constants.hpp"

#include <nlohmann/json.hpp>

namespace bindings {

    /**
     * @brief Binding sent by the server to a client as a response to a password
     * change. Indicates succes or fail.
     */
    struct ChangeUsernameResponse {
        bool success;

        nlohmann::json to_json() const {
            return nlohmann::json{
                {PACKET_TYPE_FIELD, BindingType::ChangeUsernameResponse},
                {"data",
                 {
                     {"success", success},
                 }}};
        }

        static ChangeUsernameResponse from_json(const nlohmann::json &j) {
            if (j.at(PACKET_TYPE_FIELD)
                != BindingType::ChangeUsernameResponse) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return ChangeUsernameResponse{data.at("success").get<bool>()};
        }
    };

} // namespace bindings

#endif // BINDINGS_CHANGE_USERNAME_RESPONSE
