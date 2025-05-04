#ifndef BINDINGS_CONSTANTS_HPP
#define BINDINGS_CONSTANTS_HPP

#include <string_view>

namespace bindings {

    inline constexpr std::string_view PACKET_DELIMITER = "\n";

    inline constexpr std::string_view PACKET_TYPE_FIELD = "type";

}

#endif // BINDINGS_CONSTANTS_HPP
