#ifndef PLACEMENT_TIMED_EFFECT_HPP
#define PLACEMENT_TIMED_EFFECT_HPP

#include "abstract_timed_effect.hpp"

#include <cstddef>
#include <ostream>

class PlacementTimedEffectTest;

class PlacementTimedEffect : public virtual ATimedEffect {
  private:
    size_t numPlacements_;
    // Number of Tetrominoes left to place before the effect expires (decreases
    // with each placement)
    size_t remainingPlacements_;

  protected:
    PlacementTimedEffect(size_t placementsNum);
    PlacementTimedEffect(const PlacementTimedEffect &);
    PlacementTimedEffect(PlacementTimedEffect &&) = delete;
    PlacementTimedEffect &operator=(const PlacementTimedEffect &) = delete;
    PlacementTimedEffect &operator=(PlacementTimedEffect &&) = delete;

  public:
    virtual ~PlacementTimedEffect() = default;

    bool operator==(const PlacementTimedEffect &other) const;

    void tetrominoPlaced() override;

    bool isFinished() const override;

    double getElapsedTime() const override;

    /**
     * @brief Outputs the PlacementTimedEffect to a stream.
     *
     * @param os The output stream.
     * @param PlacementTimedEffect The PlacementTimedEffect to output.
     * @return A reference to the output stream.
     */
    friend std::ostream &
    operator<<(std::ostream &os,
               const PlacementTimedEffect &placementTimedEffect);

    friend PlacementTimedEffectTest;
};

#endif // PLACEMENT_TIMED_EFFECT_HPP
