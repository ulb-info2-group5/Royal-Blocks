#ifndef ABSTRACT_GAME_DISPLAY_HPP
#define ABSTRACT_GAME_DISPLAY_HPP

#include "../common/types/types.hpp"
#include "core/in_game/game_state/game_state.hpp"
#include "core/in_game/game_state/game_state_viewer.hpp"
#include <optional>

class Controller;

class AbstractGameDisplay {
  private:
    std::variant<client::GameState, client::GameStateViewer> gameState_;

  public:
    // Returned by selfCellInfoAt.
    // Tells us whether the cell at (x,y) is a part of the active or preview
    // or a placed Tetromino.
    enum class SelfCellType {
        Active,
        Preview,
        Placed,
    };

    enum class Color {
        Black,
        White,
        Grey,
        DarkBlue,
        LightBlue,
        Purple,
        Red,
        Orange,
        Pink,
        Green,
        Yellow
    };

  protected:
    AbstractGameDisplay(Controller &controller);

    Controller &controller_;

    static Color colorIdToColor(unsigned colorID);

    UserID getNthOpponentUserID(size_t n) const;

    size_t getBoardHeight() const;

    void
    setGameState(const std::variant<client::GameState, client::GameStateViewer>
                     &newGameState);

    const std::variant<client::GameState, client::GameStateViewer> &
    getGameState();

    size_t getBoardWidth() const;

    Energy getSelfScore() const;

    std::optional<UserID> getSelectedTarget() const;

    Score getSelfEnergy() const;

    GameMode getGameMode() const;

    std::optional<std::pair<unsigned, SelfCellType>>
    selfCellInfoAt(int x, int y) const;

    const std::string &getSelfUsername() const;

    std::optional<unsigned> opponentsBoardGetColorIdAt(size_t opponentIdx,
                                                       int x, int y) const;

    const std::string &getOpponentUsername(size_t opponentIdx) const;

    bool checkOpponentAlive(size_t opponentIdx) const;

    size_t getNumOpponents() const;

    const client::Tetromino &getTetrominoQueueNth(size_t tetrominoIdx) const;

    const client::Tetromino *getHoldTetromino() const;

    size_t getTetrominoQueuesSize() const;

    const std::vector<std::pair<EffectType, Energy>> &getEffectPrices() const;

    // pair<penalty-name, elapsedTime>
    std::optional<std::pair<std::string, double>> getPenaltyInfo() const;

    // pair<bonus-name, elapsedTime>
    std::optional<std::pair<std::string, double>> getBonusInfo() const;

    bool inGame() const;

    bool isSpectating() const;

    bool isWinner() const;

    bool gameIsFinished() const;
};

#endif // ABSTRACT_GAME_DISPLAY_HPP
