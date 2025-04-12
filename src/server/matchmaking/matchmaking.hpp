#ifndef MATCHMACKING_HPP
#define MATHCMACKING_HPP

#include "../../common/bindings/create_game.hpp"
#include "../../common/bindings/join_game.hpp"
#include "../../common/tetris_royal_lib/game_mode/game_mode.hpp"
#include "../games_manager/games_manager.hpp"
#include <iostream>
#include <string>
#include <vector>

using NumberOfPlayers = size_t;


using GameFindCallback =
        std::function<void(std::vector<Player>, GameMode)>;


constexpr NumberOfPlayers MAXPLAYERDUAL = 2;
constexpr NumberOfPlayers MAXPLAYERCLASSICANDROYAL = 9;

struct RequestJoinGame {
    Player player;
    bindings::JoinGame bindGame;
};

struct RequestCreateGame {
    Player player;
    bindings::CreateGame bindCreateGame;
};

class GameCandidate {
  private:
    NumberOfPlayers numberOfPlayerTotale_;
    NumberOfPlayers numberOfPlayersMax_;
    GameMode gameMode;
    std::vector<Player> players_;

  public:
    GameCandidate(RequestJoinGame joinGame);
    GameCandidate(RequestCreateGame createGame);

    void removePlayer(UserID playerID);

    ~GameCandidate() = default;
    bool isThisPartyReady();
    bool isthisPlayerInThisGame(UserID userId);
    bool tryToAddPlayer(RequestJoinGame joinGame);
    bool isThereRoomInThisGame();
    bool isEmpty();

    std::vector<Player> &getPlayers();
    std::vector<UserID> getPlayerIDs();
    GameMode getGameMode();
};

class Matchmaking {
  private:
    std::vector<GameCandidate> gamesCanditatesClassic_;
    std::vector<GameCandidate> gamesCanditatesDuel_;
    std::vector<GameCandidate> gamesCanditatesRoyalCompetition_;


    GameFindCallback gameFindCallback_;

    void createNewGameCandidate(std::vector<GameCandidate> &games,
                                RequestJoinGame joinGame);
    void startGame(GameCandidate &&gameCandidate, GamesManager &gamesManager);
    std::vector<GameCandidate> &getGame(GameMode gameMode);

  public:
    Matchmaking(GameFindCallback gameFindCallback) ;
    ~Matchmaking() = default;
    void addPlayer(RequestJoinGame joinGame, GamesManager &gamesManager);
    void removePlayer(UserID playerID, GameMode gameMode);


    void findaGame(std::vector<GameCandidate> &games, RequestJoinGame joinGame,
                   GamesManager &gamesManager);
    void createAGame(RequestCreateGame createGame);

    void abortMatchmaking( const std::shared_ptr<ClientLink>& clientLink ); 
};

#endif