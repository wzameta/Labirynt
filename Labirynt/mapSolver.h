#ifndef MAPSOLVER_H
#define MAPSOLVER_H

#include "mazeSolver.h"
#include "myexceptions.h"

/*
 * Klasa MapSolver - algorytm szukania drogi z mapa odleglosci (BFS - Breadth First Search).
 *
 * Jak dziala algorytm z mapa?
 *
 * FAZA 1 - Budowanie mapy odleglosci (_buildMap):
 * - Zaczynamy od mety
 * - rozchodzimy sie rownomiernie we wszystkich kierunkach
 * - Kazde pole otrzymuje liczbe krokow potrzebnych do dotarcia do mety
 * - Pola niedostepne (sciany, odizolowane) maja wartosc -1

 *
 * FAZA 2 - Odtwarzanie sciezki (_reconstruct):
 * - Zaczynamy od start.
 * - W kazdym kroku idziemy na pole z mniejsza odlegloscia
 * - Powatarzamy az dotrzemy do mety
 *
 */
class MapSolver : public MazeSolver
{
private:
    int* _distMap; // mapa odleglosci: _distMap[y * width + x] = odleglosc od mety
    // -1 oznacza nieosiagalne

/*
 * Buduje mape odleglosci od punktu finish.
 * Uzywa algorytmu BFS (przeszukiwanie wszerz / fala).
 *
 * @param m      labirynt
 * @param finish punkt od ktorego liczymy odleglosci (meta)
 */
    void _buildMap(const Maze& m, Point finish);

    /*
     * Odtwarza sciezke od start do finish uzywajac mapy odleglosci.
     *
     * @param m      labirynt
     * @param start  punkt startowy
     * @param finish punkt koncowy
     * @param result tutaj zostanie zapisana sciezka
     */
    void _reconstruct(const Maze& m, Point start, Point finish, Path& result);

public:
    /*
     * Konstruktor domyslny
     */
    MapSolver();

    /*
     * Destruktor - zwalnia pamiec tablicy _distMap
     */
    ~MapSolver();

    /*
     * Szuka NAJKROTSZEJ drogi algorytmem z mapa.
     *
     * @param m      labirynt w ktorym szukamy
     * @param start  punkt startowy
     * @param finish punkt koncowy
     * @param result tutaj zostanie zapisana najkrotsza sciezka
     * @return true jezeli droga istnieje
     *
     * @throws MyExceptions::InvalidArgument gdy start lub finish jest poza labiryntem
     *                                       lub jest sciana
     */
    bool findPath(const Maze& m, Point start, Point finish, Path& result) override;
};

#endif
