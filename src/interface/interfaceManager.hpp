#ifndef INTERFACEMANAGER_HPP
#define INTERFACEMANAGER_HPP

#include "interfaceConfig.hpp"

class InterfaceManager {
    private: 

    userInfo currUser_;

    public:

    InterfaceManager() noexcept;
    ~InterfaceManager();

    //getters everywhere

    StateUser getUserState() const;
    uint32_t getUserScore() const;
    std::string getUserName() const;

    //not sure of the visibility of the methods below

    //setters
    void changeUserState( StateUser newUserState) noexcept;
    void changeUserScoreClassement(uint32_t newUserScore) noexcept;
    void changeUserName(std::string newUserName) noexcept;
    
};


#endif