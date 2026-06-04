#include "backtrackingSolver.h"

/*
 * Konstruktor - ustawiamy wskaznik _visited na nullptr.
 * Tablica zostanie przydzielona dopiero w findPath().
 */
BacktrackingSolver::BacktrackingSolver()
    : _visited(nullptr)
{
}

/*
 * Destruktor - zwalniamy tablice _visited jezeli zostala przydzielona.
 */
BacktrackingSolver::~BacktrackingSolver()
{
    delete[] _visited;
    _visited = nullptr;
}

/*
 * Glowna metoda szukania drogi - przygotowuje tablice _visited i uruchamia rekurencje.
 */
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

    // Czyscimy sciezke wynikowa
    result.clear();

    // ---- Uruchomienie rekurencji ----

    // Wywolujemy rekurencyjna metode _solve od punktu startowego
    // UWAGA: rekurencja dodaje punkty od konca do poczatku (post-order traversal)
    // Dlatego po znalezieniu drogi musimy odwrocic kolejnosc punktow.
    bool found = _solve(m, start.x(), start.y(), finish, result);

    if (found)
    {
        // Odwracamy sciezke zeby byla w kolejnosci start -> meta
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

/*
 * Rekurencyjna metoda szukania drogi - serce algorytmu backtracking.
 *
 * Parametry:
 * - (x, y) - biezace pole, ktore teraz sprawdzamy
 * - finish  - pole docelowe
 * - result  - sciezka ktora budujemy
 *
 * Logika:
 * 1. Sprawdzamy czy pole (x, y) jest prawidlowe (w zakresie, nie sciana, nie odwiedzone)
 * 2. Oznaczamy pole jako odwiedzone
 * 3. Jezeli to jest cel - dodajemy do sciezki i konczymy z sukcesem
 * 4. Probujemy rekurencyjnie isc w 4 kierunki (dol, gore, prawo, lewo)
 * 5. Jezeli ktorys kierunek dal sukces - dodajemy biezace pole i zwracamy true
 * 6. Jezeli zadny kierunek nie dal sukcesu - zwracamy false (backtrack)
 */
bool BacktrackingSolver::_solve(const Maze& m, unsigned x, unsigned y, Point finish, Path& result)
{
    // ---- Sprawdzamy czy pole jest poza labiryntem ----
    // (to moze sie zdarzyc gdy idziemy od krawedzi labiryntu)
    if (x >= m.width() || y >= m.height())
    {
        return false;
    }

    // ---- Sprawdzamy czy pole jest sciana ----
    if (m.isWall(x, y))
    {
        return false;
    }

    // ---- Sprawdzamy czy pole juz odwiedzilismy (unikamy petli) ----
    if (_visited[y * m.width() + x])
    {
        return false;
    }

    // ---- Oznaczamy pole jako odwiedzone ----
    _visited[y * m.width() + x] = true;

    // ---- Sprawdzamy czy dotarlismy do celu ----
    if (x == finish.x() && y == finish.y())
    {
        // Dotarlismy! Dodajemy biezace pole do sciezki i zwracamy sukces.
        result.add(Point(x, y));
        return true;
    }

    // ---- Probujemy isc w 4 kierunki ----
    // Uwaga: uzywamy signed int dla obliczen zeby uniknac przepelnienia unsigned
    // (np. 0 - 1 dla unsigned daje bardzo duza liczbe, nie -1)

    // Kierunki: (dx, dy) oznacza zmiane wspolrzednych
    // Kolejnosc kierunkow wplywa na to jak wyglada znaleziona sciezka
    int dx[] = { 0,  0,  1, -1 }; // dol, gora, prawo, lewo - zmiana x
    int dy[] = { 1, -1,  0,  0 }; // dol, gora, prawo, lewo - zmiana y

    for (int i = 0; i < 4; i++)
    {
        // Obliczamy wspolrzedne sasiadujacego pola
        int nx = (int)x + dx[i];
        int ny = (int)y + dy[i];

        // Sprawdzamy czy wspolrzedne sa nieujemne (unsigned nie moze byc ujemne)
        if (nx < 0 || ny < 0)
        {
            continue; // pomijamy - wyszlibysmy poza labirynt
        }

        // Rekurencyjnie probujemy znalezc droge przez pole (nx, ny)
        if (_solve(m, (unsigned)nx, (unsigned)ny, finish, result))
        {
            // Sasiad znalazl droge! Dodajemy biezace pole do sciezki.
            // Uwaga: dodajemy BPO rekurencji, wiec punkty beda w kolejnosci od startu do mety.
            result.add(Point(x, y));
            return true;
        }
    }

    // Zadne z sasiadujacych pol nie prowadzi do celu - cofamy sie (backtrack)
    return false;
}
