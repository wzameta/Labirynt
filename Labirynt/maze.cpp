#include "maze.h"


std::ostream& operator<<(std::ostream& out, const Maze& m)
{
    // Przechodzimy przez kazdy wiersz labiryntu
    for (unsigned y = 0; y < m.height(); y++)
    {
        // Przechodzimy przez kazda kolumne w wierszu
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

    return out; // zwracamy strumien
}
