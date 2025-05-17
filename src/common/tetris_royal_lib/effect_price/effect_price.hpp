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

#ifndef EFFECT_PRICE_HPP
#define EFFECT_PRICE_HPP

#include "../../types/types.hpp"
#include "../effect/effect_type.hpp"

using EffectPrice = std::pair<EffectType, Energy>;

constexpr Energy DEFAULT_EFFECT_PRICE = 3;

/**
 * @brief Returns the given effect's price.
 * Defaults to DEFAULT_EFFECT_PRICE if no price is specified.
 */
Energy getEffectPrice(EffectType effectType);

#endif // EFFECT_PRICE_HPP
