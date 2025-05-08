#define MATHCMACKING_HPP
#ifndef MATCHMACKING_HPP

#include "../../common/bindings/create_game.hpp"
#include "../../common/bindings/join_game.hpp"
#include "../../common/tetris_royal_lib/game_mode/game_mode.hpp"
#include "../game_server/game_server.hpp"

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

/**
 * @class
 *
 * @brief
 */
class GameCandidate {
  private:
    NumberOfPlayers numberOfPlayerTotale_;
    NumberOfPlayers numberOfPlayersMax_;
    GameMode gameMode;
    std::vector<Player> players_;

  public:
    GameCandidate(RequestJoinGame joinGame);
    GameCandidate(RequestCreateGame createGame);

    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */
    void removePlayer(UserID playerID);

    ~GameCandidate() = default;

    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */
    bool isThisPartyReady();

    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */
    bool isthisPlayerInThisGame(UserID userId);

    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */
    bool tryToAddPlayer(RequestJoinGame joinGame);

    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */
    bool isThereRoomInThisGame();

    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */
    bool isEmpty();

    /**
    * @brief 
    */
    std::vector<Player> &getPlayers();

    /**
    * @brief 
    */
    std::vector<UserID> getPlayerIDs();

    /**
    * @brief 
    */
    GameMode getGameMode();
};


/**
 * @class
 *
 * @brief
 */
class Matchmaking {
  private:
    std::vector<GameCandidate> gamesCanditatesClassic_;
    std::vector<GameCandidate> gamesCanditatesDuel_;
    std::vector<GameCandidate> gamesCanditatesRoyalCompetition_;


    GameFindCallback gameFindCallback_;

    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */
    void createNewGameCandidate(std::vector<GameCandidate> &games,
                                RequestJoinGame joinGame);
                            
    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */               
    void startGame(GameCandidate &&gameCandidate);
    std::vector<GameCandidate> &getGame(GameMode gameMode);

  public:
    Matchmaking(GameFindCallback gameFindCallback) ;
    ~Matchmaking() = default;

    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */
    void addPlayer(RequestJoinGame joinGame);

    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */
    void removePlayer(UserID playerID, GameMode gameMode);


    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */
    void findaGame(std::vector<GameCandidate> &games, RequestJoinGame joinGame);

    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */
    void createAGame(RequestCreateGame createGame);

    /**
    * @brief 
    *
    * @param 
    * @param 
    *
    * @return
    */
    void abortMatchmaking( const std::shared_ptr<ClientLink>& clientLink ); 
};

#endif