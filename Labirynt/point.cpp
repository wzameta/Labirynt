#include "point.h"

/*
 * Konstruktor domyslny - tworzy punkt (0, 0).
 * Wymagany przez DynamicArray (new T[n] wymaga konstruktora domyslnego).
 */
Point::Point()
    : _x(0), _y(0)
{
}

/*
 * Konstruktor - inicjalizuje wspolrzedne punktu
 */
Point::Point(unsigned x, unsigned y)
    : _x(x), _y(y)
{
    // Uzywamy listy inicjalizacyjnej (: _x(x), _y(y))
    // Jest to lepszy styl w C++ niz przypisywanie w ciele konstruktora
}

/*
 * Zwraca wspolrzedna x (kolumna)
 */
unsigned Point::x() const
{
    return _x;
}

/*
 * Zwraca wspolrzedna y (wiersz)
 */
unsigned Point::y() const
{
    return _y;
}
