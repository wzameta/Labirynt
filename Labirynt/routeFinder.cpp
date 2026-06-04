#include "routeFinder.h"

/*
 * Konstruktor - inicjujemy wszystkie pola.
 * Uzywamy listy inicjalizacyjnej dla pol _start i _finish
 * poniewaz klasa Point nie ma konstruktora domyslnego.
 */
RouteFinder::RouteFinder(Maze* m, MazeSolver* solver, Point start, Point finish)
    : _start(start), _finish(finish)
{
    // Sprawdzamy czy przekazano prawidlowe wskazniki
    if (m == nullptr)
    {
        throw MyExceptions::InvalidArgument("Maze pointer cannot be null in RouteFinder");
    }

    if (solver == nullptr)
    {
        throw MyExceptions::InvalidArgument("Solver pointer cannot be null in RouteFinder");
    }

    _maze = m;
    _solver = solver;
}

/*
 * Uruchamia algorytm szukania drogi.
 * Wynik jest zapisywany do pola _path.
 * Zwraca true jezeli znaleziono droge, false w przeciwnym razie.
 */
bool RouteFinder::solve()
{
    // Delegujemy do aktualnie ustawionego algorytmu
    // Przekazujemy labirynt, punkt startowy, koncowy i referencje na sciezke wynikowa
    return _solver->findPath(*_maze, _start, _finish, _path);
}

/*
 * Zmienia algorytm szukania drogi.
 * Kolejne wywolanie solve() uzyje nowego algorytmu.
 */
void RouteFinder::changeSolver(MazeSolver* newSolver)
{
    if (newSolver == nullptr)
    {
        throw MyExceptions::InvalidArgument("New solver pointer cannot be null");
    }

    _solver = newSolver;
}

/*
 * Zwraca kopie ostatnio wyznaczonej sciezki.
 */
Path RouteFinder::getPath() const
{
    return _path;
}
