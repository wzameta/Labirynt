#include "maze.h"

/*
 * Implementacja operatora << dla klasy Maze.
 *
 * Petla zewnetrzna przechodzi przez wiersze (y od 0 do height-1).
 * Petla wewnetrzna przechodzi przez kolumny (x od 0 do width-1).
 * Dla kazdego pola sprawdzamy czy jest sciana i wypisujemy odpowiedni znak.
 */
std::ostream& operator<<(std::ostream& out, const Maze& m)
{
    // Przechodzimy przez kazdy wiersz labiryntu (od gory do dolu)
    for (unsigned y = 0; y < m.height(); y++)
    {
        // Przechodzimy przez kazda kolumne w wierszu (od lewej do prawej)
        for (unsigned x = 0; x < m.width(); x++)
        {
            // Sprawdzamy czy dane pole jest sciana
            if (m.isWall(x, y))
            {
                out << '#'; // sciana
            }
            else
            {
                out << '.'; // pole wolne
            }
        }

        // Po kazdym wierszu przechodzimy do nowej linii
        out << '\n';
    }

    return out; // zwracamy strumien, aby mozna bylo laczyc: cout << m1 << m2
}
