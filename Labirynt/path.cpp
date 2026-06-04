#include "path.h"

/*
 * Dodaje punkt na koniec sciezki.
 * Delegujemy do metody add() szablonu DynamicArray.
 */
void Path::add(Point p)
{
    _points.add(p);
}

/*
 * Usuwa wszystkie punkty ze sciezki.
 * Delegujemy do metody clear() szablonu DynamicArray.
 */
void Path::clear()
{
    _points.clear();
}

/*
 * Zwraca liczbe punktow w sciezce.
 * Delegujemy do metody size() szablonu DynamicArray.
 */
unsigned Path::length() const
{
    return _points.size();
}

/*
 * Operator [] - zwraca punkt pod podanym indeksem.
 * Delegujemy do operatora [] szablonu DynamicArray.
 * DynamicArray samo rzuca wyjatek OutOfBounds gdy indeks jest nieprawidlowy.
 */
Point Path::operator[](unsigned i) const
{
    return _points[i]; // DynamicArray rzuci wyjatek jesli i >= length()
}

/*
 * Implementacja operatora << dla klasy Path.
 *
 * Wypisujemy kolejne punkty sciezki.
 * Miedzy punktami wypisujemy " -> " (strzalka).
 * Format: (0,0) -> (1,0) -> (2,0)
 */
std::ostream& operator<<(std::ostream& out, const Path& p)
{
    for (unsigned i = 0; i < p.length(); i++)
    {
        // Wypisujemy punkt w formacie (x,y)
        out << "(" << p[i].x() << "," << p[i].y() << ")";

        // Miedzy punktami dodajemy strzalke (ale nie po ostatnim)
        if (i < p.length() - 1)
        {
            out << " -> ";
        }
    }

    return out;
}
