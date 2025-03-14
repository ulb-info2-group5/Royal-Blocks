#ifndef MATCHMACKING_HPP
#define MATHCMACKING_HPP

#include "../../../common/bindings/create_game.hpp"
#include "../../../common/bindings/join_game.hpp"
#include "../../../common/tetris_royal_lib/game_mode/game_mode.hpp"
#include "../games_manager/games_manager.hpp"
#include <iostream>
#include <string>
#include <vector>

using NumberOfPlayers = size_t;

constexpr NumberOfPlayers MAXPLAYERDUAL = 2;
constexpr NumberOfPlayers MAXPLAYERCLASSICANDROYAL = 9;

struct RequestJoinGame {
    UserID userId;
    bindings::JoinGame bindGame;
};

struct RequestCreateGame {
    UserID userId;
    bindings::CreateGame bindCreateGame;
};

class GameCandidate {
  private:
    NumberOfPlayers numberOfPlayerTotale_;
    NumberOfPlayers numberOfPlayersMax_;
    GameMode gameMode;
    std::vector<UserID> players_;

  public:
    GameCandidate(RequestJoinGame joinGame);
    GameCandidate(RequestCreateGame createGame);

    ~GameCandidate() = default;
    bool isThisPartyReady();
    bool isthisPlayerInThisGame(UserID userId);
    bool tryToAddPlayer(RequestJoinGame joinGame);
    bool isThereRoomInThisGame();

    std::vector<UserID> &getPlayers();
    GameMode getGameMode();
};

class Matchmaking {
  private:
    std::vector<GameCandidate> gamesCanditatesClassic_;
    std::vector<GameCandidate> gamesCanditatesDuel_;
    std::vector<GameCandidate> gamesCanditatesRoyalCompetition_;

    void createNewGameCandidate(std::vector<GameCandidate> &games,
                                RequestJoinGame joinGame);
    void startGame(GameCandidate &&gameCandidate, GamesManager &gamesManager);
    std::vector<GameCandidate> &getGame(GameMode gameMode);

  public:
    Matchmaking() = default;
    ~Matchmaking() = default;
    void addPlayer(RequestJoinGame joinGame, GamesManager &gamesManager);
    void findaGame(std::vector<GameCandidate> &games, RequestJoinGame joinGame,
                   GamesManager &gamesManager);
    void createAGame(RequestCreateGame createGame);
};

#endif