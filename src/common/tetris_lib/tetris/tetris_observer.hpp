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

#ifndef TETRIS_OBSERVER_HPP
#define TETRIS_OBSERVER_HPP

#include <memory>

struct TetrisObserver {
    TetrisObserver() = default;
    TetrisObserver(const TetrisObserver &) = default;
    TetrisObserver(TetrisObserver &&) = default;
    TetrisObserver &operator=(const TetrisObserver &) = default;
    TetrisObserver &operator=(TetrisObserver &&) = default;

    virtual ~TetrisObserver() = default;

    virtual void notifyLost() = 0;

    virtual void notifyActiveTetrominoPlaced() = 0;
};

using TetrisObserverPtr = std::shared_ptr<TetrisObserver>;

#endif // TETRIS_OBSERVER_HPP
