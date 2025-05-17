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

#ifndef ABSTRACT_TIMED_EFFECT_HPP
#define ABSTRACT_TIMED_EFFECT_HPP

#include <memory>

#include <nlohmann/json.hpp>

class ATimedEffect {
  protected:
    ATimedEffect() = default;
    ATimedEffect(const ATimedEffect &) = delete;
    ATimedEffect(ATimedEffect &&) = delete;
    ATimedEffect &operator=(const ATimedEffect &) = delete;
    ATimedEffect &operator=(ATimedEffect &&) = delete;

  public:
    virtual ~ATimedEffect() = default;

    /**
     * @brief Notifies that a clock tick has occurred.
     */
    virtual void tick() {};

    /**
     * @brief Notifies that the active tetromino has been placed.
     */
    virtual void tetrominoPlaced() {};

    /**
     * @brief Returns true if the effect isn't active anymore; false otherwise.
     */
    virtual bool isFinished() const = 0;

    /**
     * @brief Returns a double representing the proportion of the effect's
     * duration that has elapsed.
     */
    virtual double getElapsedTime() const = 0;

    /* ------------------------------------------------
     *          Serialization
     * ------------------------------------------------*/

    /**
     * @brief Serializes the ATimedEffect to json.
     */
    virtual nlohmann::json serialize() const = 0;
};

using ATimedEffectPtr = std::shared_ptr<ATimedEffect>;

#endif // ABSTRACT_TIMED_EFFECT_HPP
