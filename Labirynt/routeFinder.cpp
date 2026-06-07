#include "routeFinder.h"


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

    // Sprawdzamy czy punkty sa w granicach labiryntu, bez tego bylyby sprawdzone dopiero przy wywollaniu solve().
    if (start.x() >= m->width() || start.y() >= m->height())
        throw MyExceptions::InvalidArgument("Start point is outside the maze");

    if (finish.x() >= m->width() || finish.y() >= m->height())
        throw MyExceptions::InvalidArgument("Finish point is outside the maze");


    _maze = m;
    _solver = solver;
}


bool RouteFinder::solve()
{
    return _solver->findPath(*_maze, _start, _finish, _path);
}


void RouteFinder::changeSolver(MazeSolver* newSolver)
{
    if (newSolver == nullptr)
    {
        throw MyExceptions::InvalidArgument("New solver pointer cannot be null");
    }

    _solver = newSolver;
}


Path RouteFinder::getPath() const
{
    return _path;
}
