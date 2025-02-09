#ifndef INTERFACEGAME_HPP
#define INTERFACEGAME_HPP

#include "interfaceConfig.hpp"

class InterfaceGame {
    private:

    playerGameInfo currPlayer_;
    std::array<std::array<colors, WIDTH>, HEIGHT>& playerBoard_;

    std::optional<uint8_t> playerMalus_ = std::optional<uint8_t>{std::nullopt};

    std::optional<uint8_t> energyPower_ = std::optional<uint16_t>{std::nullopt};
    std::optional<std::vector<effects>>&& effectsQueue_ = std::optional<std::vector<effects>>{std::nullopt};

    std::optional<std::vector<opponentInfo>> opponents_ = std::optional<std::vector<opponentInfo>>{std::nullopt};

    protected:

    // setters

    void updateCurrentPlayerBoard(std::array< std::array<colors, WIDTH>, HEIGHT>& newPlayerBoard) noexcept;

    void updateCurrentPlayerInfo(playerGameInfo playerInfoUpdate) noexcept;

    void updatePlayerMalus(uint8_t malusNumberToBeActivated) noexcept;

    void updatePlayerEffectState(uint8_t currEnergyPower, std::vector<effects>& currEffectsQueue) noexcept;

    void updateOpponentBoard(std::array<std::array<colors, WIDTH>, HEIGHT>& newOpponentBoard, uint8_t index) noexcept;

    void updateAllOpponentBoards(std::vector<std::array<std::array<colors, WIDTH>, HEIGHT>>& newOpponentBoards) noexcept;

    public:
    // version ENDLESS
    InterfaceGame(playerGameInfo currPlayer, std::array<std::array<colors,WIDTH>, HEIGHT>& playerBoard) noexcept;

    //version CLASSIQUE and DUO
    InterfaceGame(playerGameInfo currPlayer, std::array<std::array<colors, WIDTH>, HEIGHT>& playerBoard,
              uint8_t playerMalus, 
              std::vector<opponentInfo> opponentsInfo) noexcept;

    //version ROYAL
    InterfaceGame(playerGameInfo currPlayer, std::array<std::array<colors, WIDTH>, HEIGHT>& playerBoard,
              uint8_t playerMalus,
              uint16_t energyPower, std::vector<effects>& effectsQueue,
              std::vector<opponentInfo> opponentsInfo) noexcept;

    ~InterfaceGame();

    //getters everywhere 

    uint8_t getPlayersNumber() const;
    PlayMode getPlayMode() const;

    
    std::array<std::array<colors, WIDTH>, HEIGHT>& getCurrPlayerBoard() const;
    uint32_t getPlayerScore() const;
    std::string getPlayerName() const;

    std::optional<uint8_t> getPlayerMalus() const;
    std::optional<uint8_t> getPlayerEnergyPower() const;
    
    std::optional<std::vector<effects>> getEffectsQueue() const;
    

    std::array< std::array<colors, WIDTH>, HEIGHT>& getOpponentBoard(uint8_t index);

    //update methode : having 3 overload ( 1 for endless, 1 for Duo & classique, 1 for royal)
    //passing in parameter the gamestate and the player state surely

    //void update()

};

#endif