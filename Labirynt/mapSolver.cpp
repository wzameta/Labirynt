#include "mapSolver.h"

/*
 * Konstruktor - inicjujemy wskaznik na nullptr.
 */
MapSolver::MapSolver()
    : _distMap(nullptr)
{
}

/*
 * Destruktor - zwalniamy mape odleglosci jezeli zostala przydzielona.
 */
MapSolver::~MapSolver()
{

    delete[] _distMap;
    _distMap = nullptr;
}

/*
 * Glowna metoda szukania drogi.
 * 1. Waliduje argumenty
 * 2. Buduje mape odleglosci (BFS od mety)
 * 3. Sprawdza czy start jest osiagalny
 * 4. Odtwarza sciezke
 */
bool MapSolver::findPath(const Maze& m, Point start, Point finish, Path& result)
{
    // ---- Walidacja argumentow ----

    if (start.x() >= m.width() || start.y() >= m.height())
    {
        throw MyExceptions::InvalidArgument("Start point is outside the maze");
    }

    if (finish.x() >= m.width() || finish.y() >= m.height())
    {
        throw MyExceptions::InvalidArgument("Finish point is outside the maze");
    }

    if (m.isWall(start.x(), start.y()))
    {
        throw MyExceptions::InvalidArgument("Start point is a wall");
    }

    if (m.isWall(finish.x(), finish.y()))
    {
        throw MyExceptions::InvalidArgument("Finish point is a wall");
    }

    // ---- Czyscimy wynik ----
    result.clear();

    // ---- Budujemy mape odleglosci ----
    _buildMap(m, finish);

    // Sprawdzamy czy start jest osiagalny (odleglosc != -1)
    int startDist = _distMap[start.y() * m.width() + start.x()];
    if (startDist == -1)
    {
        // Start jest odizolowany od mety - brak drogi
        return false;
    }

    // ---- Odtwarzamy sciezke ----
    _reconstruct(m, start, finish, result);

    return true;
}

/*
 * Buduje mape odleglosci od punktu finish uzywajac algorytmu BFS.
 *
 * BFS (Breadth First Search) - przeszukiwanie wszerz:
 * - Uzywamy kolejki (queue) do przechowywania pol do odwiedzenia
 * - Zaczynamy od mety (odleglosc = 0)
 * - Dla kazdego pola dodajemy jego sasiadow do kolejki z odlegloscia +1
 * - Powtarzamy az kolejka bedzie pusta
 *
 * Implementujemy kolejke recznie uzywajac tablicy i dwoch indeksow (head, tail).
*/
void MapSolver::_buildMap(const Maze& m, Point finish)
{
    unsigned width = m.width();
    unsigned height = m.height();
    unsigned total = width * height;

    // Zwalniamy stara mape
    delete[] _distMap;

    // Alokujemy nowa mape i wypelniamy wartoscia -1 (nieosiagalne)
    _distMap = new int[total];
    for (unsigned i = 0; i < total; i++)
    {
        _distMap[i] = -1;
    }

    // Ustawiamy odleglosc mety na 0
    _distMap[finish.y() * width + finish.x()] = 0;

    // ---- Kolejka BFS ----
    // Uzywamy tablicy o rozmiarze total jako kolejki (max tyle pol ile jest w labiryncie)
    // queueX, queueY przechowuja wspolrzedne pol w kolejce
    unsigned* queueX = new unsigned[total];
    unsigned* queueY = new unsigned[total];
    unsigned  head = 0; // indeks poczatku kolejki (element do odczytania)
    unsigned  tail = 0; // indeks konca kolejki   (miejsce na nowy element)

    // Dodajemy mete na poczatek kolejki
    queueX[tail] = finish.x();
    queueY[tail] = finish.y();
    tail++;

    // Kierunki ruchu: gora, dol, lewo, prawo
    int dx[] = { 0,  0, -1,  1 };
    int dy[] = { -1, 1,  0,  0 };

    // ---- Petla BFS ----
    while (head < tail) // dopoki kolejka nie jest pusta
    {
        // Pobieramy pole z poczatku kolejki
        unsigned cx = queueX[head];
        unsigned cy = queueY[head];
        head++; // "usuwamy" element z kolejki (przesuwamy glowice)

        // Biezaca odleglosc tego pola od mety
        int currentDist = _distMap[cy * width + cx];

        // Sprawdzamy wszystkich 4 sasiadow
        for (int i = 0; i < 4; i++)
        {
            int nx = (int)cx + dx[i];
            int ny = (int)cy + dy[i];

            // Pomijamy pola poza labiryntem
            if (nx < 0 || ny < 0 || (unsigned)nx >= width || (unsigned)ny >= height)
            {
                continue;
            }

            // Pomijamy sciany
            if (m.isWall((unsigned)nx, (unsigned)ny))
            {
                continue;
            }

            // Pomijamy pola juz odwiedzone (odleglosc != -1)
            if (_distMap[(unsigned)ny * width + (unsigned)nx] != -1)
            {
                continue;
            }

            // Ustawiamy odleglosc sasiada = odleglosc biezacego pola + 1
            _distMap[(unsigned)ny * width + (unsigned)nx] = currentDist + 1;

            // Dodajemy sasiada do kolejki do pozniejszego przetworzenia
            queueX[tail] = (unsigned)nx;
            queueY[tail] = (unsigned)ny;
            tail++;
        }
    }

    // Zwalniamy pomocnicze tablice kolejki
    delete[] queueX;
    delete[] queueY;
}

/*
 * Odtwarza sciezke od start do finish uzywajac mapy odleglosci.
 *
 * Algorytm:
 * 1. Zaczynamy od punktu startowego
 * 2. W kazdym kroku szukamy sasiada z MNIEJSZA odlegloscia od mety
 * 3. Idziemy na ten sasiad i powtarzamy
 * 4. Zatrzymujemy sie gdy dotrzemy do mety (odleglosc = 0)
 *
 * To dziala bo mapa odleglosci gwarantuje ze zawsze istnieje kierunek
 * z malejaca odlegloscia (jesli start jest osiagalny).
 */
void MapSolver::_reconstruct(const Maze& m, Point start, Point finish, Path& result)
{
    unsigned width = m.width();

    // Zaczynamy od punktu startowego
    unsigned cx = start.x();
    unsigned cy = start.y();

    // Dodajemy punkt startowy do sciezki
    result.add(Point(cx, cy));

    // Kierunki ruchu
    int dx[] = { 0,  0, -1,  1 };
    int dy[] = { -1, 1,  0,  0 };

    // Idziemy dopoki nie dotrzemy do mety
    while (cx != finish.x() || cy != finish.y())
    {
        // Szukamy sasiada z najmniejsza odlegloscia od mety
        unsigned bestX = cx;
        unsigned bestY = cy;
        int      bestDist = _distMap[cy * width + cx]; // biezaca odleglosc

        for (int i = 0; i < 4; i++)
        {
            int nx = (int)cx + dx[i];
            int ny = (int)cy + dy[i];

            // Pomijamy pola poza labiryntem
            if (nx < 0 || ny < 0 || (unsigned)nx >= m.width() || (unsigned)ny >= m.height())
            {
                continue;
            }

            // Pobieramy odleglosc sasiada
            int neighborDist = _distMap[(unsigned)ny * width + (unsigned)nx];

            // Sprawdzamy czy sasiad ma mniejsza odleglosc (jest blizej mety)
            if (neighborDist != -1 && neighborDist < bestDist)
            {
                bestDist = neighborDist;
                bestX = (unsigned)nx;
                bestY = (unsigned)ny;
            }
        }

        // Idziemy na najlepszego sasiada
        cx = bestX;
        cy = bestY;

        // Dodajemy nowe pole do sciezki
        result.add(Point(cx, cy));
    }
}
