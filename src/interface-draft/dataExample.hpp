#ifndef DATAEXAMPLE_HPP
#define DATAEXAMPLE_HPP

#include "interfaceConfig.hpp"

const std::array<std::array<colors, WIDTH>, HEIGHT> EXEMPLE_BOARD =

{
    {colors::BLACK, colors::BLACK,colors::BLACK, colors::DARK_BLUE,colors::DARK_BLUE, colors::BLACK,colors::BLACK, colors::BLACK,colors::BLACK, colors::BLACK,},
    {colors::BLACK, colors::BLACK,colors::BLACK, colors::DARK_BLUE,colors::DARK_BLUE, colors::BLACK,colors::BLACK, colors::BLACK,colors::BLACK, colors::BLACK,},
    {colors::BLACK, colors::BLACK,colors::BLACK, colors::DARK_BLUE,colors::DARK_BLUE, colors::BLACK,colors::BLACK, colors::BLACK,colors::BLACK, colors::BLACK,},
    {colors::BLACK, colors::BLACK,colors::BLACK, colors::DARK_BLUE,colors::DARK_BLUE, colors::BLACK,colors::BLACK, colors::BLACK,colors::BLACK, colors::BLACK,},
    {colors::BLACK, colors::BLACK,colors::BLACK, colors::DARK_BLUE,colors::DARK_BLUE, colors::BLACK,colors::BLACK, colors::BLACK,colors::BLACK, colors::BLACK,},
    {colors::BLACK, colors::BLACK,colors::BLACK, colors::DARK_BLUE,colors::DARK_BLUE, colors::BLACK,colors::BLACK, colors::BLACK,colors::BLACK, colors::BLACK,},
    {colors::BLACK, colors::BLACK,colors::BLACK, colors::DARK_BLUE,colors::DARK_BLUE, colors::BLACK,colors::BLACK, colors::BLACK,colors::BLACK, colors::BLACK,},
    {colors::BLACK, colors::BLACK,colors::BLACK, colors::DARK_BLUE,colors::DARK_BLUE, colors::BLACK,colors::BLACK, colors::BLACK,colors::BLACK, colors::BLACK,},
    {colors::BLACK, colors::BLACK,colors::BLACK, colors::DARK_BLUE,colors::DARK_BLUE, colors::BLACK,colors::BLACK, colors::BLACK,colors::BLACK, colors::BLACK,},
    {colors::BLACK, colors::BLACK,colors::BLACK, colors::DARK_BLUE,colors::DARK_BLUE, colors::BLACK,colors::BLACK, colors::BLACK,colors::BLACK, colors::BLACK,},
    {colors::BLACK, colors::BLACK,colors::BLACK, colors::DARK_BLUE,colors::DARK_BLUE, colors::BLACK,colors::BLACK, colors::BLACK,colors::BLACK, colors::BLACK,},
    {colors::BLACK, colors::BLACK,colors::BLACK, colors::DARK_BLUE,colors::DARK_BLUE, colors::BLACK,colors::BLACK, colors::BLACK,colors::BLACK, colors::BLACK,},
    {colors::BLACK, colors::BLACK,colors::BLACK, colors::DARK_BLUE,colors::DARK_BLUE, colors::BLACK,colors::BLACK, colors::BLACK,colors::BLACK, colors::BLACK,},
    {colors::BLACK, colors::BLACK,colors::BLACK, colors::DARK_BLUE,colors::DARK_BLUE, colors::BLACK,colors::BLACK, colors::BLACK,colors::BLACK, colors::BLACK,},
    {colors::BLACK, colors::BLACK,colors::BLACK, colors::DARK_BLUE,colors::DARK_BLUE, colors::BLACK,colors::BLACK, colors::BLACK,colors::BLACK, colors::BLACK,},
    {colors::BLACK, colors::BLACK,colors::BLACK, colors::DARK_BLUE,colors::DARK_BLUE, colors::BLACK,colors::BLACK, colors::BLACK,colors::BLACK, colors::BLACK,},
    {colors::BLACK, colors::BLACK,colors::BLACK, colors::DARK_BLUE,colors::DARK_BLUE, colors::BLACK,colors::BLACK, colors::BLACK,colors::BLACK, colors::BLACK,},
    {colors::BLACK, colors::BLACK,colors::BLACK, colors::DARK_BLUE,colors::DARK_BLUE, colors::BLACK,colors::BLACK, colors::BLACK,colors::BLACK, colors::BLACK,},
    {colors::BLACK, colors::BLACK,colors::BLACK, colors::DARK_BLUE,colors::DARK_BLUE, colors::BLACK,colors::BLACK, colors::BLACK,colors::BLACK, colors::BLACK,},
    {colors::BLACK, colors::BLACK,colors::BLACK, colors::DARK_BLUE,colors::DARK_BLUE, colors::BLACK,colors::BLACK, colors::BLACK,colors::BLACK, colors::BLACK,},
    {colors::BLACK, colors::BLACK,colors::BLACK, colors::DARK_BLUE,colors::DARK_BLUE, colors::BLACK,colors::BLACK, colors::BLACK,colors::BLACK, colors::BLACK,}
};

const userInfo EXEMPLE_USER_INFO = {.state = UserState::STATE_INITIAL,
                                    .name = "lucas12345",
                                    .scoreClassement = 123456789};

const opponentInfo EXEMPLE_OPPONENT = {.name = "ethan12345",
                                       .board = EXEMPLE_BOARD};

#endif