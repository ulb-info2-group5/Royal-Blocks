#ifndef GAME_DISPLAY_GUI_HPP
#define GAME_DISPLAY_GUI_HPP

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QImage> 

#include "../../../../common/tetris_royal_lib/game_mode/game_mode.hpp"
#include "../../../../common/types/types.hpp"
#include "../../../core/in_game/game_state/game_state.hpp"
#include "../../../core/in_game/game_state/game_state_viewer.hpp"

#include <memory>


class Controller;

class MainGui;

class GameDisplayGUI : public QWidget {
    Q_OBJECT

    private:

    Controller &controller_;
    MainGui &mainGui_;

    std::variant<client::GameState, client::gameStateViewer> gameState_;

    QWidget *mainWidget_;

    QPushButton quitButton_;
    QImage selfBoard_;
    std::vector<QImage> opBoards_;

    std::vector<QPushButton> targetButtons_;
    std::vector<QPushButton> effectsButtons_;
    QVBoxLayout effectsLayout_;

    //std::vector<QLabel> targetLabels_;

    void quitButton();
    void playerInfo();
    void energy();
    void availableEffects();
    void penaltyInfo();
    void bonusInfo();
    void holdTetromino();
    void leftPane();

    void gameMode();
    void selBoard();
    void tetrominoQueue();
    void middlePane();

    void opponentsBoard();

    void rightPane();

    void drawEndlessMode();
    void drawMultiMode();

    void drawGameOver();
    void drawWin();
    void drawSpectate();

    UserID getNthOpponentUserID(size_t n) const;

    void handleKeys();

    size_t getBoardHeight() const;

    size_t getBoardWidth() const;

    Energy getSelfScore() const;

    std::optional<UserID> getSelectedTarget() const;

    Score getSelfEnergy() const;

    GameMode getGameMode() const;

    std::string getSelfUsername() const;

    std::optional<unsigned> opponentsBoardGetColorIdAt(size_t opponentIdx,
                                                       int x, int y) const;

    std::string getOpponentUsername(size_t opponentIdx) const;

    size_t getNumOpponents() const;

    const client::Tetromino &getTetrominoQueueNth(size_t tetrominoIdx) const;

    const client::Tetromino *getHoldTetromino() const;

    size_t getTetrominoQueuesSize() const;

    const std::vector<std::pair<EffectType, Energy>> &getEffectPrices() const;

    bool inGame() const;

    bool isSpectating();

private slots:

        // add the functions for the buttons

    public:

        GameDisplayGUI(Controller &controller, MainGui &mainGui, QWidget *parent = nullptr);

        ~GameDisplayGUI() = default;

    signals:

        void quitGame();


};

#endif