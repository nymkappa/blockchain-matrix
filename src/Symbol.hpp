#pragma once

class Symbol
{
public:
    Symbol(int x, int y, int size, char symbol);
    void Draw();

public:
    char _symbol;
    int _x;
    int _y;
    int _size;
    unsigned char _red;
    unsigned char _green;
    unsigned char _blue;
};