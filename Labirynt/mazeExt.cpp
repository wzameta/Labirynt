#include "mazeExt.h"

/*
 * Konstruktor - tworzy pusty labirynt o podanych wymiarach.
 *
 * Alokujemy tablice dynamiczna o rozmiarze (width * height).
 * Wypelniamy ja wartoscia false (wszystkie pola wolne).
 *
 * Rzucamy wyjatek gdy wymiary sa nieprawidlowe (zero nie ma sensu).
 */
MazeExt::MazeExt(unsigned width, unsigned height)
{
    // Sprawdzamy czy wymiary sa prawidlowe
    if (width == 0 || height == 0)
    {
        throw MyExceptions::InvalidArgument("Maze dimensions must be greater than 0");
    }

    _width = width;
    _height = height;

    // Alokujemy tablice dynamiczna: width * height elementow typu bool
    // Np. dla labiryntu 10x8 alokujemy 80 elementow
    _data = new bool[_width * _height];

    // Wypelniamy tablice wartoscia false (wszystkie pola sa wolne)
    for (unsigned i = 0; i < _width * _height; i++)
    {
        _data[i] = false;
    }
}

/*
 * Destruktor - zwalnia pamiec zajmowana przez tablice danych.
 * Bez tego mielibysmy wyciek pamieci!
 */
MazeExt::~MazeExt()
{
    delete[] _data; // zwalniamy pamiec tablicy
    _data = nullptr;
}

/*
 * Zwraca szerokosc labiryntu
 */
unsigned MazeExt::width() const
{
    return _width;
}

/*
 * Zwraca wysokosc labiryntu
 */
unsigned MazeExt::height() const
{
    return _height;
}

/*
 * Sprawdza czy pole (x, y) jest sciana.
 *
 * Najpierw sprawdzamy czy wspolrzedne sa w zakresie.
 * Potem obliczamy indeks w tablicy jednowymiarowej.
 *
 * Wzor na indeks: index = y * _width + x
 * Przyklad: labirynt 10x8, pole (3, 2) -> index = 2*10 + 3 = 23
 */
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

/*
 * Ustawia pole (x, y) jako sciane lub pole wolne.
 *
 * Dziala analogicznie do isWall - najpierw sprawdzamy zakres,
 * potem ustawiamy odpowiedni element tablicy.
 */
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
