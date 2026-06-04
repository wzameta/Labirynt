#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include "maze.h"
#include "point.h"
#include "path.h"

/*
 * Interfejs MazeSolver - abstrakcyjna klasa bazowa dla algorytmow szukania drogi.
 *
 * Dzieki temu interfejsowi mozemy latwo podmienic algorytm szukania drogi
 * nie zmieniajac reszty kodu (wzorzec Strategy/Strategia).
 *
 * Kazda klasa implementujaca ten interfejs (BacktrackingSolver, MapSolver)
 * musi zaimplementowac metode findPath().
 */
class MazeSolver
{
public:
    /*
     * Wirtualny destruktor - konieczny w klasach bazowych
     */
    virtual ~MazeSolver() {}

    /*
     * Szuka drogi w labiryncie od punktu start do punktu finish.
     *
     * Jezeli droga istnieje:
     * - zwraca true
     * - zapisuje znaleziona sciezke do parametru result
     *
     * Jezeli droga NIE istnieje:
     * - zwraca false
     * - czysci parametr result (result.clear())
     *
     * @param m      referencja na labirynt w ktorym szukamy drogi
     * @param start  punkt startowy (skad zaczynamy)
     * @param finish punkt koncowy   (gdzie chcemy dotrzec)
     * @param result sciezka wynikowa - tutaj zostanie zapisana znaleziona droga
     * @return true jezeli droga istnieje, false jezeli nie istnieje
     */
    virtual bool findPath(const Maze& m, Point start, Point finish, Path& result) = 0;
};

#endif // MAZESOLVER_H
