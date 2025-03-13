#ifndef GAME_MODE_HPP
#define GAME_MODE_HPP

#include "string"

enum class GameMode {
    Endless,
    Classic,
    Dual,
    RoyalCompetition,
    NumGameMode,
};

/*
 * @brief Converts a GameMode to a string
 *
 * @param mode the GameMode to convert
 * @return the string representation of the GameMode
 */
std::string toString(GameMode mode);

#endif // GAME_MODE_HPP
