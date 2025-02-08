#ifndef INTERFACECONFIG_HPP
#define INTERFACECONFIG_HPP

#include "interfaceConstants.hpp"


//not sure if it should go here 
const uint8_t   STATE_LOG = 1,
                STATE_MENU = 2,
                STATE_POOL = 3,
                STATE_IN_GAME = 4,
                STATE_END_OF_GAME = 5,
                STATE_CLASSEMENT = 6,
                STATE_MESSAGE_BOX = 7,
                STATE_MESSAGE_CHAT = 8;

const uint8_t ENDLESS = 1,
              DUEL    = 2,
              CLASSIC = 3,
              ROYAL   = 4;

struct playerGameInfo {
    uint32_t score;
    uint8_t mode;
    uint8_t totalPlayers;
    std::string name;
};

struct userInfo {
    uint8_t state;
    uint32_t scoreClassement;
    std::string name;
};

#endif