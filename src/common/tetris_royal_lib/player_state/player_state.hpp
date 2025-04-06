#ifndef PLAYER_STATE_HPP
#define PLAYER_STATE_HPP

#include "../../tetris_lib/tetris/tetris_observer.hpp"
#include "../../types/types.hpp"
#include "../effect/bonus/timed_bonus.hpp"
#include "../effect/penalty/penalty_type.hpp"
#include "../effect/penalty/timed_penalty.hpp"
#include "../effect_price/effect_price.hpp"

#include <cstddef>
#include <optional>
#include <queue>
#include <string_view>
#include <sys/types.h>

constexpr std::string_view DEFAULT_USERNAME_PREFIX = "player ";

class PlayerState final : public TetrisObserver {
  private:
    /* ------------------------------------------------
     *              Common to all GameModes
     * ------------------------------------------------*/

    UserID userID_;
    Score score_;
    bool isAlive_;
    std::string username;

    /* ------------------------------------------------
     *      Classic & RoyalCompetition Specific
     * ------------------------------------------------*/

    std::optional<UserID> penaltyTarget_;

    /* ------------------------------------------------
     *          RoyalCompetition Specific
     * ------------------------------------------------*/

    std::optional<Energy> energy_;

    // Penalties/Bonuses that the player has received/granted himself and will
    // be applied as soon as the current Penalty/Bonus is finished.
    std::queue<PenaltyType> receivedPenaltiesQueue_;
    std::queue<BonusType> grantedBonusesQueue_;

    // Store stacked effects
    std::deque<PenaltyType> stashedPenalties_;

    // Currently active bonus & penalty (no optional needed, just make it
    // nullptr)
    TimedBonusPtr pActiveBonus_;
    TimedPenaltyPtr pActivePenalty_;

    std::optional<size_t> engineTicksSinceLastTick_;

  public:
    PlayerState(UserID userID, std::string username, Score score = 0);
    PlayerState(const PlayerState &) = default;
    PlayerState(PlayerState &&) = default;
    PlayerState &operator=(const PlayerState &) = default;
    PlayerState &operator=(PlayerState &&) = default;

    ~PlayerState() = default;

    /**
     * @brief Toggles the effects-related things such as energy member.
     */
    void toggleEffects(bool activated);

    /* ------------------------------------------------
     *              Common to all GameModes
     * ------------------------------------------------*/

    /**
     * @brief Returns the player's ID.
     */
    UserID getUserID() const;

    /**
     * @brief Returns the player's score.
     */
    Score getScore() const;

    /**
     * @brief Increases the player's score by the given value.
     */
    void increaseScore(Score val);
    /**
     * @brief Returns true if the player is alive (hasn't lost yet); false
     * otherwise.
     */
    bool isAlive() const;

    /**
     * @brief Sets the isAlive member to the given value.
     */
    void setAlive(bool isAlive);

    /* ------------------------------------------------
     *      Classic & RoyalCompetition Specific
     * ------------------------------------------------*/

    /**
     * @brief Returns the player's target.
     */
    std::optional<UserID> getPenaltyTarget() const;

    /**
     * @brief Sets the player's target.
     */
    void setPenaltyTarget(UserID userID);

    /* ------------------------------------------------
     *          RoyalCompetition Specific
     * ------------------------------------------------*/

    /**
     * @brief Returns the player's amount of Energy.
     */
    std::optional<Energy> getEnergy() const;

    /**
     * @brief Increases the player's energy amount by the given amount.
     */
    void increaseEnergy(Energy amount);

    /**
     * @brief Decreases the player's energy amount by the given amount.
     */
    void decreaseEnergy(Energy amount);

    /**
     * @brief Adds the bonus to the grantedBonusQueue.
     */
    void grantBonus(BonusType bonus);

    /**
     * @brief Adds the penalty to the receivedPenaltiesQueue.
     */
    void receivePenalty(PenaltyType penalty);

    /**
     * @brief Fetches the next bonus that the player has granted himself (stored
     * in the queue).
     */
    std::optional<BonusType> fetchGrantedBonus();

    /**
     * @brief Fetches the next penalty that the player has received (stored
     * in the queue).
     */
    std::optional<PenaltyType> fetchReceivedPenalty();

    /**
     * @brief Sets the given timed-bonus as active bonus.
     */
    void setActiveBonus(const TimedBonusPtr &pTimedBonus);

    /**
     * @brief Returns active bonus.
     */
    TimedBonusPtr &getActiveBonus();

    /**
     * @brief Returns active penalty.
     */
    TimedPenaltyPtr &getActivePenalty();

    /**
     * @brief Sets the given timed-penalty as active penalty.
     */
    void setActivePenalty(const TimedPenaltyPtr &pTimedPenalty);

    /**
     * @brief Stashes the penalty for later.
     */
    void stashPenalty(PenaltyType penalty);

    /**
     * @brief Returns the penalties that were stashed and empties the stash.
     */
    std::deque<PenaltyType> getStashedPenalties();

    /**
     * @brief Determines whether the current engine tick corresponds to a game
     * tick for the player.
     *
     * Engine ticks maintain a constant frequency throughout the game and are
     * used to time effects. However, not every engine tick results in a game
     * tick for the player's Tetris instance.
     *
     * This double-tick mechanism exists due to the SpeedUp penalty, which
     * requires the player's Tetris instance to speed up dynamically.
     */
    bool isGameTick();

    /**
     * @brief Notifies that a engine tick has occured.
     *
     * This doesn't do anything besides updating the
     * engineTicksSinceLastTick_ member.
     * This doesn't do anything related to the effects etc.
     */
    void notifyEngineTick();

    /* ------------------------------------------------
     *          TetrisObserver
     * ------------------------------------------------*/

    /**
     * @brief Notifies that the player has lost.
     */
    void notifyLost();

    /**
     * @brief Notifies that a tetromino has been placed.
     */
    void notifyActiveTetrominoPlaced();

  public:
    /* ------------------------------------------------
     *          Serialization
     * ------------------------------------------------*/

    nlohmann::json serializeExternal() const;

    nlohmann::json serializeSelf() const;
};

using PlayerStatePtr = std::shared_ptr<PlayerState>;

#endif // PLAYER_STATE_HPP
