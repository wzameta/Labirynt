#ifndef ROUTEFINDER_H
#define ROUTEFINDER_H

#include "maze.h"
#include "mazeSolver.h"
#include "point.h"
#include "path.h"
#include "myexceptions.h"

/*
 * Klasa RouteFinder - reprezentuje konkretne zadanie znajdowania drogi.
 *
 * Laczy ze soba:
 * - labirynt (Maze*) - w czym szukamy
 * - algorytm (MazeSolver*) - jak szukamy
 * - punkt startowy i koncowy - skad dokad
 * - wynikowa sciezka (Path) - wynik ostatniego szukania
 *
 * Dzieki metodzie changeSolver() mozemy latwo zmienic algorytm
 * dla tego samego labiryntu i tych samych punktow startowego/koncowego.
 * To jest wzorzec projektowy "Strategia" (Strategy Pattern).
 *
 * UWAGA: RouteFinder przechowuje wskazniki na Maze i MazeSolver,
 * ale NIE jest ich wlascicielem - nie zwalnia ich pamieci w destruktorze.
 * Odpowiedzialnosc za zwalnianie pamieci spoczywa na wywolujacym.
 */
class RouteFinder
{
private:
    Maze* _maze;   // wskaznik na labirynt (nie zwalniamy!)
    MazeSolver* _solver; // wskaznik na algorytm  (nie zwalniamy!)
    Point       _start;  // punkt startowy
    Point       _finish; // punkt koncowy
    Path        _path;   // ostatnio wyznaczona sciezka

public:
    /*
     * Konstruktor - inicjuje wszystkie pola.
     *
     * @param m      wskaznik na labirynt
     * @param solver wskaznik na algorytm szukania drogi
     * @param start  punkt startowy
     * @param finish punkt koncowy
     *
     * @throws MyExceptions::InvalidArgument gdy m lub solver jest nullptr
     */
    RouteFinder(Maze* m, MazeSolver* solver, Point start, Point finish);

    /*
     * Uruchamia aktualnie ustawiony algorytm szukania drogi.
     * Wynik jest przechowywany wewnatrz klasy i dostepny przez getPath().
     *
     * @return true jezeli droga zostala znaleziona, false jezeli brak drogi
     */
    bool solve();

    /*
     * Zmienia algorytm szukania drogi na nowy.
     * Mozna potem wywolac solve() ponownie z nowym algorytmem.
     *
     * @param newSolver wskaznik na nowy algorytm
     *
     * @throws MyExceptions::InvalidArgument gdy newSolver jest nullptr
     */
    void changeSolver(MazeSolver* newSolver);

    /*
     * Zwraca ostatnio wyznaczona sciezke.
     * Jezeli solve() nie bylo wywolane lub nie znalezlo drogi, sciezka bedzie pusta.
     *
     * @return ostatnia wyznaczona sciezka (kopia)
     */
    Path getPath() const;
};

#endif // ROUTEFINDER_H
