#include "interfaceGame.hpp"

// constructors and destructor 
 InterfaceGame::InterfaceGame(playerGameInfo currPlayer, std::array<std::array<colors,WIDTH>, HEIGHT>& playerBoard) noexcept :
 currPlayer_{currPlayer}, playerBoard_{playerBoard} {}

 InterfaceGame::InterfaceGame(playerGameInfo currPlayer, std::array<std::array<colors, WIDTH>, HEIGHT>& playerBoard,
              uint8_t playerMalus, 
              std::vector<opponentInfo> opponentsInfo) noexcept :
    InterfaceGame(currPlayer, playerBoard)
{
    playerMalus_.emplace(playerMalus);
    opponents_.emplace(opponentsInfo);
}

InterfaceGame::InterfaceGame(playerGameInfo currPlayer, std::array<std::array<colors, WIDTH>, HEIGHT>& playerBoard,
              uint8_t playerMalus,
              uint16_t energyPower, std::vector<effects>& effectsQueue,
              std::vector<opponentInfo> opponentsInfo) noexcept :
    InterfaceGame(currPlayer, playerBoard, playerMalus, opponentsInfo)
{
    energyPower_.emplace(energyPower);
    effectsQueue_.emplace(effectsQueue);
}

InterfaceGame::~InterfaceGame() = default;

//protected methods 

void InterfaceGame::updateCurrentPlayerBoard(std::array< std::array<colors, WIDTH>, HEIGHT>& newPlayerBoard) noexcept 
{
    playerBoard_ = newPlayerBoard;
}

void InterfaceGame::updateCurrentPlayerInfo(playerGameInfo playerInfoUpdate) noexcept
{
    currPlayer_ = playerInfoUpdate;
}

void InterfaceGame::updatePlayerMalus(uint8_t malusNumberToBeActivated) noexcept
{
    playerMalus_.emplace(malusNumberToBeActivated);
}

void InterfaceGame::updatePlayerEffectState(uint8_t currEnergyPower, std::vector<effects>& currEffectsQueue) noexcept
{
    effectsQueue_.emplace(currEffectsQueue);
    energyPower_.emplace(currEnergyPower);
}

// void InterfaceGame::updateOpponentBoard(std::array<std::array<colors, WIDTH>, HEIGHT>& newOpponentBoard, uint8_t index) noexcept 
// {
//     //not sure if it does correctly what it should 
//     opponentInfo[index] = newOpponentBoard;
// }

// void InterfaceGame::updateAllOpponentBoards(std::vector<std::array<std::array<colors, WIDTH>, HEIGHT>>& newOpponentBoards) noexcept
// {
//     for (uint8_t i = 0; i < currPlayer_.totalPlayers ; ++i)
//     {
//         updateOpponentBoard(newOpponentBoards.at(i), i);
//     }
// }

// public methods 


uint8_t InterfaceGame::getPlayersNumber() const { return currPlayer_.totalPlayers; }
PlayMode InterfaceGame::getPlayMode() const { return currPlayer_.mode; }


std::array<std::array<colors, WIDTH>, HEIGHT>& InterfaceGame::getCurrPlayerBoard() const { return playerBoard_; }
uint32_t InterfaceGame::getPlayerScore() const { return currPlayer_.score; }
std::string InterfaceGame::getPlayerName() const { return currPlayer_.name; }

std::optional<uint8_t> InterfaceGame::getPlayerMalus() const { return playerMalus_; }
std::optional<uint8_t> InterfaceGame::getPlayerEnergyPower() const { return energyPower_; }

std::optional<std::vector<effects>> InterfaceGame::getEffectsQueue() const { return effectsQueue_; }


// std::array < std::array<colors, WIDTH>, HEIGHT>& InterfaceGame::getOpponentBoard(uint8_t index) { return opponents_.value().at(index); }

