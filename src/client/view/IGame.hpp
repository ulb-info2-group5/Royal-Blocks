#ifndef IGAME_HPP
#define IGAME_HPP

#include "interfaceConfig.hpp"
#include "playerState.hpp"
#include "gameState.hpp"

class IGame 
{
    public:

    virtual ~IGame() = default;

    virtual void changePlayerState() = 0;

    virtual void changeAim(uint8_t playerIndex) = 0;

    virtual void applyEffect(effects effect) = 0;

    virtual void changePieceInStock() = 0;

    virtual void drawPlayerBoard() = 0;

    virtual void drawOpponentsBoard() = 0;

    virtual void drawPieceQueue() = 0;

    virtual void drawPlayerInfo() = 0;

    // not sure of the name
    virtual void drawMenuOptions() = 0;

    virtual void drawWindow() = 0;

};

#endif