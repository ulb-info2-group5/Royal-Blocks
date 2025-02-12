#ifndef PLAYER_STATE_HPP
#define PLAYER_STATE_HPP

#include "../effect/penalty/penalty.hpp"
#include "../effect_selector/effect_selector.hpp"
#include "serializable_queue/serializable_queue.hpp"

#include <cstddef>
#include <optional>
#include <sys/types.h>

using PlayerID = size_t;
using Score = size_t;
using Energy = size_t;

class PlayerState {
  private:
    /* ------------------------------------------------
     *              Common to all GameModes
     * ------------------------------------------------*/

    PlayerID playerID_;
    Score score_;
    bool isAlive_;

    /* ------------------------------------------------
     *      Classic & RoyalCompetition Specific
     * ------------------------------------------------*/

    std::optional<PlayerID> penaltyTarget_;

    /* ------------------------------------------------
     *          RoyalCompetition Specific
     * ------------------------------------------------*/

    std::optional<Energy> energy_;

    // Penalties/Bonuses that the player has received/granted himself and will
    // be applied as soon as the current Penalty/Bonus is finished.
    std::optional<SerializableQueue<Penalty::PenaltyType>>
        receivedPenaltiesQueue_;
    std::optional<SerializableQueue<Bonus::BonusType>> grantedBonusesQueue_;

    // Penalties/Bonuses the player can send/grant himself
    std::optional<EffectSelector> effectSelector_;

    // Currently active bonus & penalty (no optional needed, just make it
    // nullptr)
    AbstractTimedEffectPtr pActiveBonus_;
    AbstractTimedEffectPtr pActivePenalty_;

  public:
    PlayerState() = default;
    PlayerState(const PlayerState &) = delete;
    PlayerState(PlayerState &&) = default;
    PlayerState &operator=(const PlayerState &) = delete;
    PlayerState &operator=(PlayerState &&) = default;

    ~PlayerState() = default;

    /* ------------------------------------------------
     *              Common to all GameModes
     * ------------------------------------------------*/

    /**
     * @brief Returns the player's ID.
     */
    PlayerID getPlayerID() const;

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
    std::optional<PlayerID> getPenaltyTarget() const;

    /**
     * @brief Sets the player's target.
     */
    void setPenaltyTarget(PlayerID playerID);

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
     * @brief Returns effect selected by the player.
     */
    std::optional<EffectType> getSelectedEffect();

    /**
     * @brief Adds the bonus to the grantedBonusQueue.
     */
    void grantBonus(Bonus::BonusType bonus);

    /**
     * @brief Adds the penalty to the receivedPenaltiesQueue.
     */
    void receivePenalty(Penalty::PenaltyType penalty);

    /**
     * @brief Fetches the next bonus that the player has granted himself (stored
     * in the queue).
     */
    std::optional<Bonus::BonusType> fetchGrantedBonus();

    /**
     * @brief Fetches the next penalty that the player has received (stored
     * in the queue).
     */
    std::optional<Penalty::PenaltyType> fetchReceivedPenalty();

    /**
     * @brief Sets the given timed-effect bonus as active bonus.
     */
    void setActiveBonus(AbstractTimedEffectPtr pTimedEffect);

    /**
     * @brief Sets the given timed-effect penalty as active penalty.
     */
    void setActivePenalty(AbstractTimedEffectPtr pTimedEffect);

    /**
     * @brief Selects the next effect in the effect selector.
     */
    void selectNextEffect();

    /**
     * @brief Selects the previous effect in the effect selector.
     */
    void selectPrevEffect();
};

#endif // PLAYER_STATE_HPP
