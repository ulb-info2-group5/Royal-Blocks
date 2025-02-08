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


const uint8_t  PIECE_Z = 1,
                PIECE_L = 2,
                PIECE_O = 3,
                PIECE_S = 4,
                PIECE_I = 5,
                PIECE_J = 6,
                PIECE_T = 7;

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