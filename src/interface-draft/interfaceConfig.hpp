#ifndef INTERFACECONFIG_HPP
#define INTERFACECONFIG_HPP

#include "interfaceConstants.hpp"


//not sure if it should go here 
// const uint8_t   STATE_LOG = 0,
//                 STATE_MENU = 1,
//                 STATE_POOL = 2,
//                 STATE_IN_GAME = 3,
//                 STATE_END_OF_GAME = 4,
//                 STATE_CLASSEMENT = 5,
//                 STATE_MESSAGE_BOX = 6,
//                 STATE_MESSAGE_CHAT = 7;

enum class UserState : uint8_t
{
    STATE_INITIAL,
    STATE_LOG,
    STATE_INSCRIPTION,
    STATE_MENU,
    STATE_POOL,
    STATE_IN_GAME,
    STATE_END_OF_GAME,
    STATE_CLASSEMENT,
    STATE_MESSAGE_BOX,
    STATE_MESSAGE_CHAT
};

// const uint8_t   NUMBER_OF_STATES = 8;

enum class PlayMode : uint8_t 
{
    ENDLESS,
    DUEL   ,
    CLASSIC,
    ROYAL
};

// const uint8_t ENDLESS = 1,
//               DUEL    = 2,
//               CLASSIC = 3,
//               ROYAL   = 4;

struct playerGameInfo 
{
    uint32_t score;
    PlayMode mode;
    uint8_t totalPlayers;
    std::string name;
};

struct userInfo 
{
    UserState state;
    uint32_t scoreClassement;
    std::string name;
};

struct opponentInfo
{
    std::string name;
    std::array<std::array<colors, WIDTH>,HEIGHT>& board;
};

#endif