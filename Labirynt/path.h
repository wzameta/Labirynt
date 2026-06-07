#ifndef PATH_H
#define PATH_H

#include <iostream>
#include "point.h"
#include "dynamicArray.h"
#include "myexceptions.h"

/*
 * Klasa Path - reprezentuje sciezke jako uporzadkowana sekwencje punktow.
 * Wewnatrz uzywamy szablonu DynamicArray<Point> do przechowywania punktow.
 */
class Path
{
private:
    DynamicArray<Point> _points; // dynamiczna tablica punktow sciezki

public:
    /*
     * Dodaje punkt na koniec sciezki
     * @param p punkt do dodania
     */
    void add(Point p);

    /*
     * Usuwa wszystkie punkty ze sciezki (zeruje sciezke)
     */
    void clear();

    /*
     * Zwraca liczbe punktow w sciezce
     * @return liczba punktow
     */
    unsigned length() const;

    /*
     * Operator [] - zwraca punkt o podanym indeksie
     * @param i indeks punktu (0 = punkt startowy, length-1 = punkt koncowy)
     * @return punkt pod podanym indeksem
     * @throws MyExceptions::OutOfBounds gdy indeks jest poza zakresem
     */
    Point operator[](unsigned i) const;
};

/*
 * Przeciazenie operatora << dla klasy Path.
 * Wypisuje wszystkie punkty sciezki w kolejnosci od poczatku do konca.
 * Format: (x0,y0) -> (x1,y1) -> ... -> (xn,yn)
 * @param out strumien wyjsciowy
 * @param p   sciezka do wypisania
 * @return    referencja na strumien
 */
std::ostream& operator<<(std::ostream& out, const Path& p);

#endif 

