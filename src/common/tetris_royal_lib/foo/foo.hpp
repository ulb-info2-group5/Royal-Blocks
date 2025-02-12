#ifndef FOO_HPP
#define FOO_HPP

#include <iostream>

#include "tetris/tetris.hpp"

class Foo {
  private:
    Tetris tetris;

  public:
    Foo() { std::cout << "foo constructed" << std::endl; }
};

#endif // FOO_HPP
