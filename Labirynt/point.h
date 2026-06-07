#ifndef POINT_H
#define POINT_H

/*
 * Klasa Point - reprezentuje pojedynczy punkt (pole) na planszy labiryntu.
 *
 * Przechowuje wspolrzedne (x, y) pola:
 * - x to kolumna (poziomo, od lewej)
 * - y to wiersz  (pionowo, od gory)
 */
class Point
{
private:
    unsigned _x; 
    unsigned _y; 

public:
    /*
     * Konstruktor domyslny - tworzy punkt (0, 0).
     * Wymagany przez DynamicArray przy alokacji tablicy (new T[n]).
     */
    Point();

    /*
     * Konstruktor - tworzy punkt o podanych wspolrzednych
     *
     * @param x kolumna punktu
     * @param y wiersz punktu
     */
    Point(unsigned x, unsigned y);

    /*
     * Zwraca wspolrzedna x  punktu
     *
     * @return wspolrzedna x
     */
    unsigned x() const;

    /*
     * Zwraca wspolrzedna y punktu
     *
     * @return wspolrzedna y
     */
    unsigned y() const;
};

#endif 
