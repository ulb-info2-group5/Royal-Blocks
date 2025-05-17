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

#include "tetromino_shapes.hpp"

#include "../vec2/vec2.hpp"
#include "abstract_tetromino.hpp"

/*--------------------------------------------------
             TetrominoShapes
--------------------------------------------------*/

// #### Output Stream ####

std::ostream &operator<<(std::ostream &os, TetrominoShape shape) {
    switch (shape) {
    case TetrominoShape::Z:
        os << "Z";
        break;
    case TetrominoShape::L:
        os << "L";
        break;
    case TetrominoShape::O:
        os << "O";
        break;
    case TetrominoShape::S:
        os << "S";
        break;
    case TetrominoShape::I:
        os << "I";
        break;
    case TetrominoShape::J:
        os << "J";
        break;
    case TetrominoShape::T:
        os << "T";
        break;
    case TetrominoShape::NumBasicTetrominoShape:
        os << "NumTetrominoShape";
        break;
    case TetrominoShape::MiniTetromino:
        os << "MiniTetromino";
        break;
    default:
        os << "Unknown";
        break;
    }
    return os;
}

/*--------------------------------------------------
             Tetromino's Derivatives
--------------------------------------------------*/

// #### Z Shape ####

TetrominoZ::TetrominoZ(Vec2 &&anchorPoint)
    : ATetromino(std::move(anchorPoint),
                 std::vector<Vec2>{{0, 0}, {0, 1}, {-1, 1}, {1, 0}},
                 &ATetromino::ZLSJT_OFFSET_DATA, TetrominoShape::Z) {}

// #### L Shape ####

TetrominoL::TetrominoL(Vec2 &&anchorPoint)
    : ATetromino(std::move(anchorPoint),
                 std::vector<Vec2>{{0, 0}, {-1, 0}, {1, 0}, {1, 1}},
                 &ATetromino::ZLSJT_OFFSET_DATA, TetrominoShape::L) {}

// #### O Shape ####

TetrominoO::TetrominoO(Vec2 &&anchorPoint)
    : ATetromino(std::move(anchorPoint),
                 std::vector<Vec2>{{0, 0}, {0, 1}, {1, 1}, {1, 0}},
                 &ATetromino::O_OFFSET_DATA, TetrominoShape::O) {}

// #### S Shape ####

TetrominoS::TetrominoS(Vec2 &&anchorPoint)
    : ATetromino(std::move(anchorPoint),
                 std::vector<Vec2>{{0, 0}, {-1, 0}, {0, 1}, {1, 1}},
                 &ATetromino::ZLSJT_OFFSET_DATA, TetrominoShape::S) {}

// #### I Shape ####

TetrominoI::TetrominoI(Vec2 &&anchorPoint)
    : ATetromino(std::move(anchorPoint),
                 std::vector<Vec2>{{0, 0}, {-1, 0}, {1, 0}, {2, 0}},
                 &ATetromino::I_OFFSET_DATA, TetrominoShape::I) {}

// #### J Shape ####

TetrominoJ::TetrominoJ(Vec2 &&anchorPoint)
    : ATetromino(std::move(anchorPoint),
                 std::vector<Vec2>{{0, 0}, {-1, 0}, {-1, 1}, {1, 0}},
                 &ATetromino::ZLSJT_OFFSET_DATA, TetrominoShape::J) {}

// #### T Shape ####

TetrominoT::TetrominoT(Vec2 &&anchorPoint)
    : ATetromino(std::move(anchorPoint),
                 std::vector<Vec2>{{0, 0}, {-1, 0}, {0, 1}, {1, 0}},
                 &ATetromino::ZLSJT_OFFSET_DATA, TetrominoShape::T) {

    // This tetromino should spawn in a way that it looks like a T so we need to
    // rotate it twice.
    // (We cannot change its body when spawn instead, because then we would need
    // another offset-data just for this shape)
    for (size_t i = 0; i < 2; i++) {
        rotate(true);
    }
}

// #### MiniTetromino Shape ####

MiniTetromino::MiniTetromino(Vec2 &&anchorPoint)
    : ATetromino(std::move(anchorPoint), std::vector<Vec2>{{0, 0}},
                 &ATetromino::ZLSJT_OFFSET_DATA,
                 TetrominoShape::MiniTetromino) {}
