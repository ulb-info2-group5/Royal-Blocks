#ifndef PLAYERSTATE_HPP
#define PLAYERSTATE_HPP

#include "interfaceConfig.hpp"

class PlayerState {
  private:
    uint32_t score_;

    std::optional<uint8_t> playerMalus_ = std::optional<uint8_t>{std::nullopt};

    std::optional<uint8_t> energyPower_ = std::optional<uint16_t>{std::nullopt};
    std::optional<std::vector<effects>> &&effectsQueue_ =
        std::optional<std::vector<effects>>{std::nullopt};

  public:
    PlayerState(uint32_t score) noexcept;

    PlayerState(uint32_t score, uint8_t playerMalus) noexcept;

    PlayerState(uint32_t score, uint8_t playerMalus, uint8_t energyPower,
                std::vector<effects> &effectsQueue) noexcept;

    uint32_t getScore() const;

    uint8_t getPlayerMalus() const;

    uint8_t getEnergyPower() const;

    std::vector<effects> &getEffectsQueue() const;
};

#endif