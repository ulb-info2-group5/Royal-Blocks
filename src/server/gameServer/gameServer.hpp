#ifndef GAMESERVER_HPP
#define GAMESERVER_HPP

#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <queue>
#include <stdint.h>
#include <utility>
#include <string>
#include <memory>

#include "../../../client/core/player_tetris/player_tetris_external.hpp"
#include "../../../client/core/player_tetris/player_tetris_self.hpp"
#include "../../../client/core/game_state/game_state.hpp"

#include "../../../common/tetris_lib/tetris/tetris.hpp"
#include "../../../common/tetris_lib/tetris/tetris_observer.hpp"

#include "../../../common/tetris_royal_lib/game_engine/game_engine.hpp"

#include "../../../common/tetris_lib/tetris/tetris_observer.hpp"

using namespace client;

enum class EVENT_TYPE {
    TETROMINO_MOVE,
    TETROMINO_ROTATE,
    PENALTY_NORMAL, 
    BUY_PENALTY_ROYAL,
    TETROMINO_HOLD,
    USER_CHANGE_TARGET,
    USER_PREV_EFFECT,
    USER_NEXT_EFFECT,
    USER_PENALTY_STACK 
    DISCONNECT,
};
struct Event
{
    uint32_t sender;
    uint32_t receiver;
    TetrominoMove move;
    bool rotateClockWise;
    EffectType effect;
    bool isStackingEffect;
    bool isConnected;
    EVENT_TYPE type;
};


class GameServer
{
    private : 

    std::vector<Event> events_;

    std::vector<PlayerTetris> players_;
    std::vector<uint32_t> viewers_;

    std::shared_ptr<GameEngine> gameEngine_;
    GameStatePtr gameStatePtr_;

    // will be initialise in constructor; not sure of the type
    static std::chrono::_V2::system_clock currTime_;

    protected:

    void applyUserMoveTetris(Event &event);

    void applyUserRotateTetris(Event &event);

    void applyUserHoldTetromino(Event &event);

    void applyUserBuyEffect(Event &event);

    void applyUserNextEffect(Event &event);

    void applyUserPrevEffect(Event &event);

    void changeUserTarget(Event &event);

    void applyUserPenaltyStash(Event &event);

    void tetrisTick();

    // PlayerStateExternal createPlayerStateExternal(uint8_t player);

    // PlayerStateSelf createPlayerStateSelf(uint8_t player);

    // GameState createGameState();
    
    public:

    GameServer(std::vector<PlayerState> players, GameMode gameMode);

    ~GameServer() = default;

    void addViewer(uint32_t viewer);

    void addEvent(Event &event);

    // void update();
    /*
    dequeue all the events and verify validity of all events
    applied the events on the tetris concerned + tetris -> update
    send update playerState and gameState to each player (personalized)
    if time : add update in queue ?
    */

};


#endif