#ifndef MATCHMACKING_HPP
#define MATHCMACKING_HPP

#include <iostream>
#include <vector>
#include <string>
#include "../../common/tetris_royal_lib/game_mode/game_mode.hpp"

#include "../network/games_manager/games_manager.hpp"



using NumberOfPlayers = unsigned int ;


class Loby {
    private: 
        GameMode gameMode_;
        std::vector<PlayerID> players;
        NumberOfPlayers numberOfPlayers_;

    public: 
        Loby(); 
}; 

class GameCandidate{
    private: 
        
        NumberOfPlayers numberOfPlayerTotale_;
        NumberOfPlayers numberOfPlayersTargeted_; 
    public: 

        
}; 

class Matchmaking {
    private:
        std::vector<GameCandidate> gamesCanditates_;
    public: 
        Matchmaking(); 
        void addLoby(Loby newLoby); 
        void createNewGameCandidate(Loby newLoby);

}; 



#endif 