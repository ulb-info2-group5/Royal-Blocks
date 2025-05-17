/*
 * This file is part of Royal Blocks.
 *
 * Royal Blocks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Royal Blocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Royal Blocks.  If not, see <https://www.gnu.org/licenses/>.
 */

#define MATHCMACKING_HPP
#ifndef MATCHMACKING_HPP

#include "../../common/bindings/create_game.hpp"
#include "../../common/bindings/join_game.hpp"
#include "../../common/tetris_royal_lib/game_mode/game_mode.hpp"
#include "../game_server/game_server.hpp"

#include <vector>

using NumberOfPlayers = size_t;

using GameFindCallback = std::function<void(std::vector<Player>, GameMode)>;

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
 * @class GameCandidate
 *
 * @brief represent a game that does not yet contain the targeted number of
 * players
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
     * @brief remove player from this gameCandidate
     */
    void removePlayer(UserID playerID);

    ~GameCandidate() = default;

    /**
     * @brief check if the gameCandidate contain the targeted number of players
     * @return true if contain the targeted number of players
     */
    bool isThisPartyReady();

    /**
     * @brief check if a player is present in the gameCandidate
     *@return true if contain the player
     */
    bool isthisPlayerInThisGame(UserID userId);

    /**
     * @brief add player if there is room in this gameGanditate
     * @return true if the player has been added false else
     */
    bool tryToAddPlayer(RequestJoinGame joinGame);

    /**
     * @brief check is there is room in this gameCandidate
     */
    bool isThereRoomInThisGame();

    /**
     * @brief return true if there is no player in the gameCandidate
     *
     */
    bool isEmpty();

    std::vector<Player> &getPlayers();

    std::vector<UserID> getPlayerIDs();

    GameMode getGameMode();
};

/**
 * @class Matchmaking
 *
 * @brief manage the search of game for all clients
 */
class Matchmaking {
  private:
    std::vector<GameCandidate> gamesCanditatesClassic_;
    std::vector<GameCandidate> gamesCanditatesDuel_;
    std::vector<GameCandidate> gamesCanditatesRoyalCompetition_;

    GameFindCallback gameFindCallback_;

    /**
     * @brief add a new gameCandidate
     */
    void createNewGameCandidate(std::vector<GameCandidate> &games,
                                RequestJoinGame joinGame);

    /**
     * @brief start game covert the gamecandite to a game
     *
     * @param
     */
    void startGame(GameCandidate &&gameCandidate);
    std::vector<GameCandidate> &getGame(GameMode gameMode);

  public:
    Matchmaking(GameFindCallback gameFindCallback);
    ~Matchmaking() = default;

    /**
     * @brief add Player in the queue
     *
     */
    void addPlayer(RequestJoinGame joinGame);

    /**
     * @brief remove player from the queue
     */
    void removePlayer(UserID playerID, GameMode gameMode);

    /**
     * @brief looking for a gameCandidate that a client could join
     *if no gameCandidate found a new one with the client is create
     *
     */
    void findaGame(std::vector<GameCandidate> &games, RequestJoinGame joinGame);

    /**
     * @brief create a new gameCandidate according to the requestCreateGame
     *
     */
    void createAGame(RequestCreateGame createGame);

    /**
     * @brief make a client abort the matchmaking
     *
     */
    void abortMatchmaking(const std::shared_ptr<ClientLink> &clientLink);
};

#endif