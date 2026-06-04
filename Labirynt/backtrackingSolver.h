#ifndef BACKTRACKINGSOLVER_H
#define BACKTRACKINGSOLVER_H

#include "mazeSolver.h"
#include "myexceptions.h"

/*
 * Klasa BacktrackingSolver - algorytm szukania drogi z powrotami (backtracking).
 *
 * Jak dziala algorytm z powrotami?
 * 1. Zaczynamy od punktu startowego.
 * 2. Probujemy isc w jednym kierunku (gora, dol, lewo, prawo).
 * 3. Jezeli dotarlismy do celu - sukces!
 * 4. Jezeli weszlismy w slepa uliczke lub zapetlilismy sie - COFAMY SIE (backtrack)
 *    i probujemy inny kierunek.
 * 5. Jezeli przeszlismy wszystkie kierunki bez sukcesu - brak drogi.
 *
 * Algorytm jest rekurencyjny - wywoluje sam siebie dla kolejnych pol.
 * Uzywa tablicy _visited zeby nie wchodzic dwa razy na to samo pole.
 *
 * Wada: nie znajdzie najkrotszej drogi, tylko jakas poprawna droge.
 * Zaleta: prosty w implementacji.
 */
class BacktrackingSolver : public MazeSolver
{
private:
    bool* _visited; // tablica odwiedzonych pol (zeby nie zapetlac sie)

    /*
     * Rekurencyjna metoda pomocnicza - serce algorytmu backtracking.
     *
     * Probuje znalezc droge od biezacego pola (x,y) do pola finish.
     * Jezeli znajdzie droge - dopisuje pole (x,y) do result i zwraca true.
     * Jezeli nie znajdzie - zwraca false (i nic nie dopisuje do result).
     *
     * @param m      labirynt
     * @param x      biezaca kolumna
     * @param y      biezacy wiersz
     * @param finish cel do osiagniecia
     * @param result sciezka wynikowa
     * @return true jezeli znaleziono droge przez to pole
     */
    bool _solve(const Maze& m, unsigned x, unsigned y, Point finish, Path& result);

public:
    /*
     * Konstruktor domyslny - inicjuje wskaznik na nullptr
     */
    BacktrackingSolver();

    /*
     * Destruktor - zwalnia pamiec tablicy _visited
     */
    ~BacktrackingSolver();

    /*
     * Szuka drogi algorytmem z powrotami.
     *
     * @param m      labirynt w ktorym szukamy
     * @param start  punkt startowy
     * @param finish punkt koncowy
     * @param result tutaj zostanie zapisana sciezka
     * @return true jezeli droga istnieje
     *
     * @throws MyExceptions::InvalidArgument gdy start lub finish jest poza labiryntem
     *                                       lub jest sciana
     */
    bool findPath(const Maze& m, Point start, Point finish, Path& result) override;
};

#endif // BACKTRACKINGSOLVER_H
