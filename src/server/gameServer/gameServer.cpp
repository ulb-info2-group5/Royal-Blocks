#include "gameServer.hpp"

// constructor
GameServer::GameServer(std::vector<PlayerState> players, GameMode gameMode) : 
    players_{players}, gameStatePtr_{std::make_shared<GameState>(gameMode, players_)}
{
    gameEngine_ = GameEngine{gameStatePtr_};
    events_ = {};

    players_ = {};
    viewers_ = {};
}

// protected methods


void GameServer::applyUserMoveTetris(Event &event)
{
    // if (event == EVENT::TetromiMoveBigDrop) gameEngine_->bigDrop(player);
    gameEngine_->tryMoveActive(event.sender, event.TetrominoMove);
}

void GameServer::applyUserRotateTetris(Event &event)
{
   
    gameEngine_->tryRotateActive(event.sender, event.rotateClockWise);
    
}

void GameServer::applyUserHoldTetromino(Event &event)
{
    gameEngine_->holdNextTetromino(event.sender);
}

void GameServer::applyUserBuyEffect(Event &event)
{
    gameEngine_->tryBuyEffect(event.sender, event.effect, event.isStackingEffect);
}

void GameServer::applyUserNextEffect(Event &event)
{
    gameEngine_->selectNextEffect(event.sender);
}

void GameServer::applyUserPrevEffect(Event &event)
{
    gameEngine_->selectPrevEffect(event.sender);
}

void GameServer::changeUserTarget(Event &event)
{
    gameEngine_->selectTarget(event.sender, event.receiver);
}

void GameServer::applyUserPenaltyStash(Event &event)
{
    gameEngine_->emptyPenaltyStash(event.sender);
}

void GameServer::tetrisTick()
{
    gameEngine_->tick();
}

void GameServer::applyUserMove(Event &event)
{
    switch (event.type)
    {
        case EVENT_TYPE::TETROMINO_MOVE : applyUserMoveTetris(event); break;
        case EVENT_TYPE::TETROMINO_ROTATE : applyUserRotateTetris(event) ; break;
        case EVENT_TYPE::PENALTY_NORMAL :  break;
        case EVENT_TYPE::BUY_PENALTY_ROYAL :applyUserBuyEffect(event); break;
        case EVENT_TYPE::TETROMINO_HOLD : applyUserHoldTetromino(event) ; break;
        case EVENT_TYPE::USER_CHANGE_TARGET : applyUserTarger(event); break;
        case EVENT_TYPE::USER_PREV_EFFECT : applyUserPrevEffect(event); break; 
        case EVENT_TYPE::USER_NEXT_EFFECT : applyUserNextEffect(event); break;
        case EVENT_TYPE::USER_PENALTY_STACK : applyUserPenaltyStash(event); break;
        case EVENT_TYPE::DISCONNECT: break;
    }
}

// PlayerStateExternal GameServer::createPlayerStateExternal(uint8_t player);

// PlayerStateSelf GameServer::createPlayerStateSelf(uint8_t player);

// GameState GameServer::createGameState();

// public methods

void GameServer::addViewer(uint32_t viewer)
{
    viewers_.push_back(viewer);

} 

void GameServer::addEvent(Event &event)
{
    events_.push_back(event);
}

// void GameServer::update();
/*
    dequeue all the events and verify validity of all events
    applied the events on the tetris concerned + tetris -> update
    send update playerState and gameState to each player (personalized)
    if time : add update in queue ?
    */
