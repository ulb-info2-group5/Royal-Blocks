#include "game_mode.hpp"

std::string toString(GameMode mode) {
    switch (mode) {
    case GameMode::Endless:
        return "Endless";
    case GameMode::Classic:
        return "Classic";
    case GameMode::Dual:
        return "Dual";
    case GameMode::RoyalCompetition:
        return "Royal Competition";
    default:
        return "Unknown game mode";
    }
}
