#include <iostream>
#include <exception>

// Dolaczamy wszystkie potrzebne biblioteki projektu
#include "maze.h"
#include "mazeExt.h"
#include "point.h"
#include "path.h"
#include "mazeSolver.h"
#include "backtrackingSolver.h"
#include "mapSolver.h"
#include "routeFinder.h"
#include "myexceptions.h"

/*
 * Glowna funkcja programu.
 *
 * Tworzy labirynt, ustawia sciany, a nastepnie szuka drogi
 * dwoma algorytmami: BacktrackingSolver i MapSolver.
 * Wyniki sa wypisywane na ekran.
 *
 * Caly kod jest owiniety w try...catch zeby obsluzyc ewentualne wyjatki.
 */
int main()
{
    try
    {
        // ---- Tworzenie labiryntu 10x8 ----
        // MazeExt dziedziczy po Maze, przechowujemy go przez wskaznik na Maze
        // (to jest polimorfizm - mozemy uzywac dowolnej implementacji Maze)
        Maze* m = new MazeExt(10, 8);

        // ---- Ustawianie scian ----
        // Pionowa sciana przy x=2 (wiersze 0-4)
        m->setWall(2, 0, true);
        m->setWall(2, 1, true);
        m->setWall(2, 2, true);
        m->setWall(2, 3, true);
        m->setWall(2, 4, true);

        // Pozioma sciana przy y=3 (kolumny 4-7)
        m->setWall(4, 3, true);
        m->setWall(5, 3, true);
        m->setWall(6, 3, true);
        m->setWall(7, 3, true);

        // Dwie sciany przy x=5
        m->setWall(5, 5, true);
        m->setWall(5, 6, true);

        // ---- Ustawianie punktow startowego i koncowego ----
        Point start(0, 0);  // lewy gorny rog
        Point finish(9, 7); // prawy dolny rog

        // ---- Tworzenie algorytmow ----
        MazeSolver* s1 = new BacktrackingSolver(); // algorytm z powrotami
        MazeSolver* s2 = new MapSolver();          // algorytm z mapa (BFS)

        // ---- Tworzenie obiektu szukajacego drogi ----
        // RouteFinder laczy labirynt, algorytm i punkty w jedno zadanie
        RouteFinder* r = new RouteFinder(m, s1, start, finish);

        // ---- Wyswietlenie labiryntu ----
        std::cout << "=== LABIRYNT ===\n";
        std::cout << *m << "\n"; // operator << wypisuje labirynt

        // ---- Szukanie drogi algorytmem Backtracking ----
        std::cout << "=== BACKTRACKING ===\n";
        if (r->solve())
        {
            std::cout << r->getPath() << "\n"; // operator << wypisuje sciezke
            std::cout << "Liczba punktow sciezki: " << r->getPath().length() << "\n\n";
        }
        else
        {
            std::cout << "Brak drogi.\n\n";
        }

        // ---- Zmiana algorytmu na MapSolver ----
        r->changeSolver(s2); // podmieniamy algorytm - labirynt i punkty sie nie zmieniaja

        // ---- Szukanie drogi algorytmem MapSolver (najkrotsza droga) ----
        std::cout << "=== MAP SOLVER ===\n";
        if (r->solve())
        {
            std::cout << r->getPath() << "\n";
            std::cout << "Liczba punktow sciezki: " << r->getPath().length() << "\n";
        }
        else
        {
            std::cout << "Brak drogi.\n";
        }

        // ---- Zwalnianie pamieci ----
        // Kolejnosc: najpierw RouteFinder, potem algorytmy, na koncu labirynt
        delete r;  // RouteFinder nie zwalnia m ani solverow, tylko siebie
        delete s2;
        delete s1;
        delete m;
    }
    catch (const MyExceptions::InvalidArgument& e)
    {
        // Nieprawidlowy argument przekazany do funkcji
        std::cerr << "Blad: nieprawidlowy argument - " << e.what() << std::endl;
        return 1;
    }
    catch (const MyExceptions::OutOfBounds& e)
    {
        // Wyjscie poza zakres tablicy lub labiryntu
        std::cerr << "Blad: wyjscie poza zakres - " << e.what() << std::endl;
        return 1;
    }
    catch (const MyExceptions::NoPath& e)
    {
        // Brak drogi w labiryncie (ten wyjatek nie jest rzucany w tym przykladzie,
        // ale obslugujemy go na wszelki wypadek)
        std::cerr << "Blad: brak drogi - " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e)
    {
        // Dowolny inny standardowy wyjatek (np. bad_alloc przy braku pamieci)
        std::cerr << "Nieoczekiwany blad: " << e.what() << std::endl;
        return 1;
    }

    return 0; // sukces
}
