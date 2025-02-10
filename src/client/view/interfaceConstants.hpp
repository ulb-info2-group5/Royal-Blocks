#ifndef INTERFACECONSTANTS_HPP
#define INTERFACECONSTANTS_HPP

#include <array>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <stdint.h>
#include <string>
#include <utility>
#include <vector>

const uint32_t WIDTH = 10,
                HEIGHT = 20;

const uint8_t NB_BLOCKS_PER_PIECE = 4;

enum colors {
    BLACK,
    WHITE, 
    GREY,
    DARK_BLUE,
    LIGHT_BLUE,
    PURPLE,
    RED,
    ORANGE, 
    PINK,
    GREEN, 
    YELLOW
};

struct vec2Int {
    uint8_t x;
    uint8_t y;
};

struct pieceDetails
{
   unsigned char type;
   std::vector<vec2Int> coordinates;
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
//submatrix 4x4 with (0,0) on top left
{
    .PIECE_Z = {.type = 'Z',
                .coordinates = {{.x = 0,.y = 1}, {.x = 1,.y = 1}, 
                                {.x = 1,.y = 2}, {.x = 2,.y = 2}},
                .color = colors::RED },
    .PIECE_L = {.type = 'L',
                .coordinates = {{.x = 1,.y = 2}, {.x = 2,.y = 2}, 
                                {.x = 3,.y = 2}, {.x = 3,.y = 1}},
                .color = colors::ORANGE },
    .PIECE_O = {.type = 'O',
                .coordinates = {{.x = 1,.y = 2}, {.x = 1,.y = 1}, 
                                {.x = 2,.y = 1}, {.x = 2,.y = 2}},
                .color = colors::YELLOW },
    .PIECE_S = {.type = 'S',
                .coordinates = {{.x = 1,.y = 2}, {.x = 2,.y = 1}, 
                                {.x = 3,.y = 1}, {.x = 2,.y = 2}},
                .color = colors::GREEN },
    .PIECE_I = {.type = 'I',
                .coordinates = {{.x = 0,.y = 2}, {.x = 1,.y = 2}, 
                                {.x = 3,.y = 2}, {.x = 2,.y = 2}},
                .color = colors::LIGHT_BLUE },
    .PIECE_J = {.type = 'J',
                .coordinates = {{.x = 0,.y = 1}, {.x = 1,.y = 2}, 
                                {.x = 0,.y = 2}, {.x = 2,.y = 2}},
                .color = colors::DARK_BLUE },
    .PIECE_T = {.type = 'T',
                .coordinates = {{.x = 3,.y = 1}, {.x = 1,.y = 1}, 
                                {.x = 1,.y = 1}, {.x = 2,.y = 2}},
                .color = colors::PURPLE }
};


enum effects {
    INVERT,
    BLOC,
    SPEED_SLOWER,
    SPEED_INCREASE,
    LIGHTNING,
    LIGHT_SHUTDOWN, 
    TRANSFORM  
};


#endif