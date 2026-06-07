#include <iostream>
#include <exception>
#include "maze.h"
#include "mazeExt.h"
#include "point.h"
#include "path.h"
#include "mazeSolver.h"
#include "backtrackingSolver.h"
#include "mapSolver.h"
#include "routeFinder.h"
#include "myexceptions.h"

int main()
{
    try
    {
        // ---- Tworzenie labiryntu 10x8 ----
        Maze* m = new MazeExt(10, 8);

        // ---- Ustawianie scian ----
        m->setWall(2, 0, true);
        m->setWall(2, 1, true);
        m->setWall(2, 2, true);
        m->setWall(2, 3, true);
        m->setWall(2, 4, true);

        m->setWall(4, 3, true);
        m->setWall(5, 3, true);
        m->setWall(6, 3, true);
        m->setWall(7, 3, true);

        m->setWall(5, 5, true);
        m->setWall(5, 6, true);

        // ---- Ustawianie punktow startowego i koncowego ----
        Point start(0, 0);  // lewy gorny rog
        Point finish(9, 7); // prawy dolny rog

        // ---- Tworzenie algorytmow ----
        MazeSolver* s1 = new BacktrackingSolver(); 
        MazeSolver* s2 = new MapSolver();          

        // ---- Tworzenie obiektu szukajacego drogi ----
        // RouteFinder laczy labirynt, algorytm i punkty w jedno zadanie
        RouteFinder* r = new RouteFinder(m, s1, start, finish);

        // ---- Wyswietlenie labiryntu ----
        std::cout << "=== LABIRYNT ===\n";
        std::cout << *m << "\n"; 

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
        r->changeSolver(s2); // podmieniamy algorytm

        // ---- Szukanie drogi algorytmem MapSolver  ----
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
        delete r; 
        delete s2;
        delete s1;
        delete m;
    }
    catch (const MyExceptions::InvalidArgument& e)
    {
        std::cerr << "Blad: nieprawidlowy argument - " << e.what() << std::endl;
        return 1;
    }
    catch (const MyExceptions::OutOfBounds& e)
    {
        std::cerr << "Blad: wyjscie poza zakres - " << e.what() << std::endl;
        return 1;
    }
    catch (const MyExceptions::NoPath& e)
    {
        std::cerr << "Blad: brak drogi - " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Nieoczekiwany blad: " << e.what() << std::endl;
        return 1;
    }

    return 0; 
}
