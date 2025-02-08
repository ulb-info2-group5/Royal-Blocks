#include "interfaceGame.hpp"

// constructeur et destructeur 
 InterfaceGame::InterfaceGame(playerGameInfo currPlayer, std::array<std::array<colors,WIDTH>, HEIGHT>& playerBoard) noexcept 
 {
 }

 InterfaceGame::InterfaceGame(playerGameInfo currPlayer, std::array<std::array<colors, WIDTH>, HEIGHT>& playerBoard,
              uint8_t playerMalus, 
              std::vector<std::array<std::array<colors, WIDTH>, HEIGHT>>& opponentsBoards) noexcept 
{

}

InterfaceGame::InterfaceGame(playerGameInfo currPlayer, std::array<std::array<colors, WIDTH>, HEIGHT>& playerBoard,
              uint8_t playerMalus,
              uint16_t energyPower, std::vector<effects>& effectsQueue,
              std::vector<std::array<std::array<colors, WIDTH>, HEIGHT>>& opponentsBoards) noexcept
{

}

