#ifndef MAPSOLVER_H
#define MAPSOLVER_H

#include "mazeSolver.h"
#include "myexceptions.h"

/*
 * Klasa MapSolver - algorytm szukania drogi z mapa odleglosci (BFS - Breadth First Search).
 *
 * Jak dziala algorytm z mapa?dasda
 *
 * FAZA 1 - Budowanie mapy odleglosci (_buildMap):
 * - Zaczynamy od punktu KONCZOWEGO (meta).
 * - Szerzysmy sie falowo we wszystkich kierunkach (BFS - przeszukiwanie wszerz).
 * - Kazde pole otrzymuje liczbe krokow potrzebnych do dotarcia do mety.
 * - Pola niedostepne (sciany, odizolowane) maja wartosc -1.
 *
 * Przyklad mapy odleglosci (S = start, F = finish, # = sciana):
 *
 *   . . # . .       4 3 # 3 4
 *   . . # . .  -->  3 2 # 2 3
 *   . . . F .       2 1 0 1 2  (F = 0, bo jestesmy na mecie)
 *   . . . . S       3 2 1 2 3  (S = 3, potrzebujemy 3 krokow)
 *
 * FAZA 2 - Odtwarzanie sciezki (_reconstruct):
 * - Zaczynamy od punktu STARTOWEGO.
 * - W kazdym kroku idziemy na siad z MNIEJSZA odlegloscia.
 * - Powatarzamy az dotrzemy do mety (odleglosc = 0).
 *
 * Zaleta: zawsze znajduje NAJKROTSZA droge!
 * Wada: wymaga dodatkowej pamieci na mape odleglosci.
 */
class MapSolver : public MazeSolver
{
private:
    int* _distMap; // mapa odleglosci: _distMap[y*width + x] = odleglosc od mety
    // -1 oznacza: nieosiagalne (sciana lub odizolowane pole)

/*
 * Faza 1: buduje mape odleglosci od punktu finish.
 * Uzywa algorytmu BFS (przeszukiwanie wszerz / fala).
 *
 * @param m      labirynt
 * @param finish punkt od ktorego liczymy odleglosci (meta)
 */
    void _buildMap(const Maze& m, Point finish);

    /*
     * Faza 2: odtwarza sciezke od start do finish uzywajac mapy odleglosci.
     * Idzie od start w kierunku malejacych odleglosci az do finish.
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

#endif // MAPSOLVER_H
