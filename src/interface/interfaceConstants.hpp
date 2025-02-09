#ifndef INTERFACECONSTANTS_HPP
#define INTERFACECONSTANTS_HPP

#include <string>
#include <optional>
#include <vector>
#include <array>
#include <cstdlib>
#include <iostream>
#include <stdint.h>

const uint32_t WIDTH = 10,
                HEIGHT = 20;

const uint8_t NB_BLOCKS_PER_PIECE = 4;


// const uint8_t  PIECE_Z = 1,
//                 PIECE_L = 2,
//                 PIECE_O = 3,
//                 PIECE_S = 4,
//                 PIECE_I = 5,
//                 PIECE_J = 6,
//                 PIECE_T = 7;
enum colors {
    BLACK,
    WHITE, 
    GREY,
    DARK_BLUE,
    LIGHT_BLUE,
    MAGENTA,
    RED,
    ORANGE, 
    PINK,
    GREEN, 
    YELLOW
}color_t;

struct vec2Int {
    uint8_t x;
    uint8_t y;
};

struct pieceDetails
{
   unsigned char type;
   std::array<vec2Int, NB_BLOCKS_PER_PIECE> coordinates;
   colors color;
};

struct pieces
    {
    pieceDetails PIECE_Z;
    pieceDetails PIECE_L;
    pieceDetails PIECE_O;
    pieceDetails PIECE_S;
    pieceDetails PIECE_I;
    pieceDetails PIECE_J;
    pieceDetails PIECE_T;
};

const pieces piece =
{
    .PIECE_Z = {.type = 'Z',
                .coordinates = {{1,0}, {1,1}, {2,1}, {2,2}},
                .color = colors::RED },
    .PIECE_L = {.type = 'L',
                .coordinates = {{0,2}, {1,2}, {2,2}, {2,1}},
                .color = colors::ORANGE },
    .PIECE_O = {.type = 'O',
                .coordinates = {{0,2}, {2,1}, {2,1}, {2,2}},
                .color = colors::RED },
    .PIECE_S = {.type = 'Z',
                .coordinates = {{1,0}, {1,1}, {2,1}, {2,2}},
                .color = colors::RED },
    .PIECE_I = {.type = 'Z',
                .coordinates = {{1,0}, {1,1}, {2,1}, {2,2}},
                .color = colors::RED },
    .PIECE_J = {.type = 'Z',
                .coordinates = {{1,0}, {1,1}, {2,1}, {2,2}},
                .color = colors::RED },
    .PIECE_T = {.type = 'Z',
                .coordinates = {{1,0}, {1,1}, {2,1}, {2,2}},
                .color = colors::RED }
};


enum effects {
    INVERT,
    BLOC,
    SPEED_SLOWER,
    SPEED_INCREASE,
    LIGHTNING,
    LIGHT_SHUTDOWN, 
    TRANSFORM  
}effect_t;


#endif