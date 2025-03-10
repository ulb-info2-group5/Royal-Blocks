#ifndef MATCHMACKING_HPP
#define MATHCMACKING_HPP

#include <iostream>
#include <vector>
#include <string>
#include "../../common/tetris_royal_lib/game_mode/game_mode.hpp"
#include "../../common/bindings/join_game.hpp"
#include "../../common/bindings/create_game.hpp"
#include "../network/games_manager/games_manager.hpp"



using NumberOfPlayers = unsigned int ;


class Loby {
    private: 
        GameMode gameMode_;
        std::vector<PlayerID> players;
        NumberOfPlayers numberOfPlayers_;

    public: 
        Loby();
        void addFriend(bindings::JoinGame joinGame); 
}; 

class GameCandidate{
    private: 
        NumberOfPlayers numberOfPlayerTotale_;
        NumberOfPlayers numberOfPlayersMax_; 
        std::vector<Loby> lobys_;
    public:
        GameCandidate(NumberOfPlayers numberOfPlayersMax); 
        ~GameCandidate() = default;
        bool isThisPartyReady();
        bool isthisPlayerInThisGame(PlayerID playerId);
        bool tryToAddPlayer(bindings::JoinGame joinGame);
        std::optional<bindings::JoinGame> joinFriend(bindings::JoinGame joinGame);        
}; 

class Matchmaking {
    private:
        std::vector<GameCandidate> gamesCanditatesClassic_;
        std::vector<GameCandidate> gamesCanditatesDuel_;
        std::vector<GameCandidate> gamesCanditatesRoyalCompetition_;
        
        void createNewGameCandidate(bindings::JoinGame joinGame);
        std::vector<GameCandidate>& getGame(GameMode gameMode);

    public: 
        Matchmaking() = default;
        ~Matchmaking() = default; 
        void addPlayer(bindings::JoinGame joinGame); 
        void findaGame(std::vector<GameCandidate>& games, bindings::JoinGame joinGame);
        void createAGame(bindings::CreateGame createGame);

}; 



#endif 