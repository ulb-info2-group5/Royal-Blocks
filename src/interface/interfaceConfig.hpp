#ifndef INTERFACECONFIG_HPP
#define INTERFACECONFIG_HPP

#include "interfaceConstants.hpp"


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

enum class PlayMode : uint8_t 
{
    ENDLESS,
    DUEL   ,
    CLASSIC,
    ROYAL
};

#endif