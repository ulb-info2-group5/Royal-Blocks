#ifndef IGAME_HPP
#define IGAME_HPP

#include "interfaceConfig.hpp"
#include "playerState.hpp"
#include "gameState.hpp"

class IGame 
{
    protected : 

    virtual void drawPlayerBoard() = 0;

    virtual void drawOpponentsBoard() = 0;

    //virtual void drawPieceQueue() = 0;

    //virtual void drawPlayerInfo() = 0;

    // not sure of the name
    //virtual void drawMenuOptions() = 0;

   // virtual void changePlayerState() = 0;

    //virtual void changeAim(uint8_t playerIndex) = 0;

    //virtual void applyEffect(effects effect) = 0;

    //virtual void changePieceInStock() = 0;

    // virtual void drawEndlessMode() = 0;

    // virtual void drawDualMode() = 0;

    // virtual void drawClassicMode() = 0;

    virtual void drawRoyalMode() = 0;

    public:

    virtual ~IGame() = default;

    virtual void drawWindow() = 0;

};

#endif