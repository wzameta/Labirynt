#ifndef MAZEEXT_H
#define MAZEEXT_H

#include "maze.h"
#include "myexceptions.h"

/*
 * Klasa MazeExt - konkretna implementacja interfejsu Maze.
 *
 * Klasa ta reprezentuje rzeczywisty labirynt przechowywany w pamieci.
 * Dane labiryntu sa zapisane w tablicy dynamicznej typu bool (_data),
 * gdzie kazdy element odpowiada jednemu polu labiryntu.
 *
 * Uklad danych w tablicy:
 * - pole (x, y) jest przechowywane pod indeksem: y * _width + x
 * - to tzw. "row-major order" (wiersze po sobie)
 */
class MazeExt : public Maze
{
private:
    bool* _data;   // wskaznik na tablice dynamiczna przechowujaca dane labiryntu
    unsigned _width;  // szerokosc labiryntu (liczba kolumn)
    unsigned _height; // wysokosc labiryntu (liczba wierszy)

public:
    /*
     * Konstruktor - tworzy pusty labirynt (wszystkie pola sa wolne)
     *
     * @param width  szerokosc labiryntu (liczba kolumn), musi byc > 0
     * @param height wysokosc labiryntu (liczba wierszy), musi byc > 0
     *
     * @throws MyExceptions::InvalidArgument gdy width lub height wynosi 0
     */
    MazeExt(unsigned width, unsigned height);

    /*
     * Destruktor - zwalnia pamiec zajmowana przez tablice _data
     */
    ~MazeExt();

    /*
     * Zwraca szerokosc labiryntu
     *
     * @return szerokosc labiryntu
     */
    unsigned width() const override;

    /*
     * Zwraca wysokosc labiryntu
     *
     * @return wysokosc labiryntu
     */
    unsigned height() const override;

    /*
     * Sprawdza czy pole jest sciana
     *
     * @param x kolumna (0 do width-1)
     * @param y wiersz  (0 do height-1)
     * @return true jezeli pole jest sciana
     *
     * @throws MyExceptions::OutOfBounds gdy x lub y jest poza zakresem labiryntu
     */
    bool isWall(unsigned x, unsigned y) const override;

    /*
     * Ustawia pole jako sciane lub pole wolne
     *
     * @param x     kolumna (0 do width-1)
     * @param y     wiersz  (0 do height-1)
     * @param value true = ustaw sciane, false = ustaw pole wolne
     *
     * @throws MyExceptions::OutOfBounds gdy x lub y jest poza zakresem labiryntu
     */
    void setWall(unsigned x, unsigned y, bool value) override;
};

#endif // MAZEEXT_H
