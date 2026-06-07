#include "mazeExt.h"


MazeExt::MazeExt(unsigned width, unsigned height)
{
    if (width == 0 || height == 0)
    {
        throw MyExceptions::InvalidArgument("Maze dimensions must be greater than 0");
    }

    _width = width;
    _height = height;

    // Alokujemy tablice dynamiczna width * height elementow typu bool
    _data = new bool[_width * _height];

    // Wypelniamy tablice wartoscia false
    for (unsigned i = 0; i < _width * _height; i++)
    {
        _data[i] = false;
    }
}


MazeExt::~MazeExt()
{
    delete[] _data; // zwalniamy pamiec tablicy
    _data = nullptr;
}


unsigned MazeExt::width() const
{
    return _width;
}


unsigned MazeExt::height() const
{
    return _height;
}


bool MazeExt::isWall(unsigned x, unsigned y) const
{
    // Sprawdzamy czy wspolrzedne sa w zakresie labiryntu
    if (x >= _width || y >= _height)
    {
        throw MyExceptions::OutOfBounds("Coordinates out of maze bounds in isWall()");
    }

    // Obliczamy indeks w tablicy jednowymiarowej i zwracamy wartosc
    return _data[y * _width + x];
}


void MazeExt::setWall(unsigned x, unsigned y, bool value)
{
    // Sprawdzamy czy wspolrzedne sa w zakresie labiryntu
    if (x >= _width || y >= _height)
    {
        throw MyExceptions::OutOfBounds("Coordinates out of maze bounds in setWall()");
    }

    // Ustawiamy pole w tablicy
    _data[y * _width + x] = value;
}
