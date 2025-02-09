#include "interfaceManager.hpp"

// constructor and destructor

InterfaceManager::InterfaceManager() noexcept {
    currUser_.state = UserState::STATE_LOG;
    currUser_.scoreClassement = 0;
    currUser_.name = "";
}

InterfaceManager::~InterfaceManager() = default;

// public methods 

UserState InterfaceManager::getUserState() const { return currUser_.state; }
uint32_t InterfaceManager::getUserScore() const { return currUser_.scoreClassement; }
std::string InterfaceManager::getUserName() const { return currUser_.name; }

void InterfaceManager::changeUserState(UserState newUserState ) noexcept {
    currUser_.state = newUserState;
}

void InterfaceManager::changeUserScoreClassement(uint32_t newUserScore) noexcept {
    currUser_.scoreClassement = newUserScore;
}

void InterfaceManager::changeUserName(std::string newUserName) noexcept {
    currUser_.name = newUserName;
}
