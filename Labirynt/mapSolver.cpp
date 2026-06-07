#include "mapSolver.h"


MapSolver::MapSolver()
    : _distMap(nullptr)
{
}


MapSolver::~MapSolver()
{

    delete[] _distMap;
    _distMap = nullptr;
}


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


void MapSolver::_buildMap(const Maze& m, Point finish)
{
    unsigned width = m.width();
    unsigned height = m.height();
    unsigned total = width * height;

    // Zwalniamy stara mape
    delete[] _distMap;

    // Alokujemy nowa mape i wypelniamy wartoscia -1 
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

            // Pomijamy pola juz odwiedzone 
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

            // Sprawdzamy czy sasiad ma mniejsza odleglosc
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
