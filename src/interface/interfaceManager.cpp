#include "interfaceManager.hpp"

// constructor and destructor

InterfaceManager::InterfaceManager() noexcept {
    currUser_.state = 1;
    currUser_.scoreClassement = 0;
    currUser_.name = "";
}

InterfaceManager::~InterfaceManager() = default;

// public methods 

uint8_t InterfaceManager::getUserState() const { return currUser_.state; }
uint32_t InterfaceManager::getUserScore() const { return currUser_.scoreClassement; }
std::string InterfaceManager::getUserName() const { return currUser_.name; }

void InterfaceManager::changeUserState(uint8_t newUserState ) noexcept {
    currUser_.state = (newUserState % NUMBER_OF_STATES);
}

void InterfaceManager::changeUserScoreClassement(uint32_t newUserScore) noexcept {
    currUser_.scoreClassement = newUserScore;
}

void InterfaceManager::changeUserName(std::string newUserName) noexcept {
    currUser_.name = newUserName;
}
