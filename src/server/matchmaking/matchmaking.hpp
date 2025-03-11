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


struct RequestJoinGame{
    PlayerID playerId;
    bindings::JoinGame bindGame;
};

struct RequestCreateGame{
    PlayerID playerId;
    bindings::CreateGame bindCreateGame;
};

class Loby {
    private: 
        GameMode gameMode_;
        std::vector<PlayerID> players;
        NumberOfPlayers numberOfPlayers_;

    public: 
        Loby(bindings::JoinGame joinGame);
        void addFriend(bindings::JoinGame joinGame); 
}; 

class GameCandidate{
    private: 
        NumberOfPlayers numberOfPlayerTotale_;
        NumberOfPlayers numberOfPlayersMax_; 
        GameMode gameMode;
        std::vector<PlayerID> players_;
    public:
        GameCandidate(RequestJoinGame joinGame);
        GameCandidate(RequestCreateGame createGame);
        
        ~GameCandidate() = default;
        bool isThisPartyReady();
        bool isthisPlayerInThisGame(PlayerID playerId);
        bool tryToAddPlayer(RequestJoinGame joinGame);
        bool isThereRoomInThisGame();
        //std::optional<bindings::JoinGame> joinFriend(bindings::JoinGame joinGame);        
}; 

class Matchmaking {
    private:
        std::vector<GameCandidate> gamesCanditatesClassic_;
        std::vector<GameCandidate> gamesCanditatesDuel_;
        std::vector<GameCandidate> gamesCanditatesRoyalCompetition_;
        
        void createNewGameCandidate(std::vector<GameCandidate>& games, RequestJoinGame joinGame);
        std::vector<GameCandidate>& getGame(GameMode gameMode);

    public: 
        Matchmaking() = default;
        ~Matchmaking() = default; 
        void addPlayer(RequestJoinGame joinGame); 
        void findaGame(std::vector<GameCandidate>& games,RequestJoinGame joinGame);
        void createAGame(RequestCreateGame createGame);

}; 



#endif 