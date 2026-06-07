#include "backtrackingSolver.h"


BacktrackingSolver::BacktrackingSolver()
    : _visited(nullptr)
{
}


BacktrackingSolver::~BacktrackingSolver()
{
    delete[] _visited;
    _visited = nullptr;
}


bool BacktrackingSolver::findPath(const Maze& m, Point start, Point finish, Path& result)
{
    // ---- Walidacja argumentow ----

    // Sprawdzamy czy punkt startowy jest w granicach labiryntu
    if (start.x() >= m.width() || start.y() >= m.height())
    {
        throw MyExceptions::InvalidArgument("Start point is outside the maze");
    }

    // Sprawdzamy czy punkt koncowy jest w granicach labiryntu
    if (finish.x() >= m.width() || finish.y() >= m.height())
    {
        throw MyExceptions::InvalidArgument("Finish point is outside the maze");
    }

    // Sprawdzamy czy start nie jest sciana
    if (m.isWall(start.x(), start.y()))
    {
        throw MyExceptions::InvalidArgument("Start point is a wall");
    }

    // Sprawdzamy czy meta nie jest sciana
    if (m.isWall(finish.x(), finish.y()))
    {
        throw MyExceptions::InvalidArgument("Finish point is a wall");
    }

    // ---- Przygotowanie tablicy odwiedzonych pol ----

    // Zwalniamy stara tablice jezeli istnieje (poprzednie wywolanie findPath)
    delete[] _visited;

    // Alokujemy nowa tablice o rozmiarze (width * height), wypelniona false
    unsigned totalCells = m.width() * m.height();
    _visited = new bool[totalCells];
    for (unsigned i = 0; i < totalCells; i++)
    {
        _visited[i] = false;
    }

    result.clear();

    // ---- Uruchomienie rekurencji ----

    //Rekurencja dodaje punkty od konca do poczatku wiec trzeba pozniej obrocic
    bool found = _solve(m, start.x(), start.y(), finish, result);

    if (found)
    {
        // Odwracamy sciezke 
        Path reversed;
        for (int i = (int)result.length() - 1; i >= 0; i--)
        {
            reversed.add(result[(unsigned)i]);
        }
        result = reversed;
    }
    else
    {
        result.clear();
    }

    return found;
}


bool BacktrackingSolver::_solve(const Maze& m, unsigned x, unsigned y, Point finish, Path& result)
{
    // Sprawdzamy czy pole jest poza labiryntem 
    if (x >= m.width() || y >= m.height())
    {
        return false;
    }

    // Sprawdzamy czy pole jest sciana
    if (m.isWall(x, y))
    {
        return false;
    }

    //  Sprawdzamy czy pole juz odwiedzilismy 
    if (_visited[y * m.width() + x])
    {
        return false;
    }

    // Oznaczamy pole jako odwiedzone
    _visited[y * m.width() + x] = true;

    // Sprawdzamy czy dotarlismy do celu 
    if (x == finish.x() && y == finish.y())
    {
        // Dotarlismy wiec Dodajemy biezace pole do sciezki i zwracamy sukces
        result.add(Point(x, y));
        return true;
    }

    // ---- Probujemy isc w 4 kierunki ----

    // Kierunki: (dx, dy) oznacza zmiane wspolrzednych
    int dx[] = { 0,  0,  1, -1 }; // dol, gora, prawo, lewo - zmiana x
    int dy[] = { 1, -1,  0,  0 }; // dol, gora, prawo, lewo - zmiana y

    for (int i = 0; i < 4; i++)
    {
        // Obliczamy wspolrzedne sasiadujacego pola
        int nx = (int)x + dx[i];
        int ny = (int)y + dy[i];

        // Sprawdzamy czy wspolrzedne sa nieujemne
        if (nx < 0 || ny < 0)
        {
            continue; // skip bo wyszlibysmy poza labirynt
        }

        // Rekurencyjnie probujemy znalezc droge przez pole (nx, ny)
        if (_solve(m, (unsigned)nx, (unsigned)ny, finish, result))
        {
            // pole obok to droga dodajemy biezace pole do sciezki.
            result.add(Point(x, y));
            return true;
        }
    }

    // Zadne z sasiadujacych pol nie prowadzi do celu - cofamy sie
    return false;
}
