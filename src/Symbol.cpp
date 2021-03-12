#include <iostream>
#include "Symbol.hpp"

Symbol::Symbol(int x, int y, int size, char symbol) : _x(x), _y(y), _size(size), _symbol(symbol)
{
    std::cout << "Create symbol at [" << _x << ", " << y << "], size " << _size << " with symbol '" << _symbol << "'\n";

    _red = rand() % 255;
    _green = rand() % 255;
    _blue = rand() % 255;
}
