#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "interfaceConfig.hpp"


class GameState
{
    private :

    PlayMode gameMode_;

    uint8_t playersNumber_;

    std::vector<std::pair<std::string, std::array<std::array<colors,WIDTH>,HEIGHT>>>& playersInfo_;

    public : 

    GameState(PlayMode gameMode, uint8_t playersNumber, std::vector<std::pair<std::string, std::array<std::array<colors,WIDTH>,HEIGHT>>>& playersInfo) noexcept;

    // getters

    PlayMode getPlayMode() const;

    uint8_t  getPlayersNumber() const;

    std::pair<std::string, std::array<std::array<colors,WIDTH>,HEIGHT>> getPlayerInfo(uint8_t index) const;
};

#endif