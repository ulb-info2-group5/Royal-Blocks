#ifndef ABSTRACT_GAME_DISPLAY_HPP
#define ABSTRACT_GAME_DISPLAY_HPP

#include "../common/types/types.hpp"
#include "core/in_game/game_state/game_state.hpp"
#include "core/in_game/game_state/game_state_viewer.hpp"

class Controller;

class AbstractGameDisplay {
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

    std::variant<client::GameState, client::GameStateViewer> gameState_;

    static Color colorIdToColor(unsigned colorID);

    UserID getNthOpponentUserID(size_t n) const;

    size_t getBoardHeight() const;

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

    size_t getNumOpponents() const;

    const client::Tetromino &getTetrominoQueueNth(size_t tetrominoIdx) const;

    const client::Tetromino *getHoldTetromino() const;

    size_t getTetrominoQueuesSize() const;

    const std::vector<std::pair<EffectType, Energy>> &getEffectPrices() const;

    bool inGame() const;

    bool isSpectating() const;

    bool isWinner() const;
};

#endif // ABSTRACT_GAME_DISPLAY_HPP
