#ifndef MAZE_H
#define MAZE_H

#include <iostream>

/*
 * Interfejs Maze - abstrakcyjna klasa bazowa reprezentujaca labirynt.
 *
 * "Interfejs" w C++ to klasa, ktora zawiera wylacznie czyste metody wirtualne (pure virtual).
 * Oznacza to, ze klasa Maze sama w sobie NIE moze byc uzyta bezposrednio - trzeba
 * stworzyc klase pochodna, ktora zaimplementuje wszystkie te metody.
 *
 * Labirynt skladaja sie z pol wolnych i scian. Wspolrzedne (x, y) oznaczaja:
 * - x: kolumna (0 = lewa krawedz, width-1 = prawa krawedz)
 * - y: wiersz   (0 = gorny wiersz, height-1 = dolny wiersz)
 */
class Maze
{
public:
    /*
     * Wirtualny destruktor - konieczny w klasach bazowych (interfejsach).
     * Bez niego usuniecie obiektu przez wskaznik na klase bazowa moze nie
     * wywolac destruktora klasy pochodnej (wycieki pamieci).
     */
    virtual ~Maze() {}

    /*
     * Zwraca szerokosc labiryntu (liczba kolumn)
     *
     * @return szerokosc labiryntu
     */
    virtual unsigned width() const = 0;

    /*
     * Zwraca wysokosc labiryntu (liczba wierszy)
     *
     * @return wysokosc labiryntu
     */
    virtual unsigned height() const = 0;

    /*
     * Sprawdza czy pole o podanych wspolrzednych jest sciana
     *
     * @param x kolumna (0 do width-1)
     * @param y wiersz  (0 do height-1)
     * @return true jezeli pole jest sciana, false jezeli jest wolne
     */
    virtual bool isWall(unsigned x, unsigned y) const = 0;

    /*
     * Ustawia pole o podanych wspolrzednych jako sciane lub pole wolne
     *
     * @param x kolumna (0 do width-1)
     * @param y wiersz  (0 do height-1)
     * @param value true = ustaw sciane, false = ustaw pole wolne
     */
    virtual void setWall(unsigned x, unsigned y, bool value) = 0;
};

/*
 * Przeciazenie operatora << dla klasy Maze.
 * Pozwala wypisac labirynt do strumienia np: cout << *maze;
 *
 * Konwencja wyswietlania:
 * - '#' oznacza sciane
 * - '.' oznacza pole wolne
 * Kazdy wiersz labiryntu jest wypisywany w nowej linii.
 *
 * @param out strumien wyjsciowy (np. cout)
 * @param m   referencja na labirynt do wypisania
 * @return    referencja na strumien (umozliwia laczenie: cout << m1 << m2)
 */
std::ostream& operator<<(std::ostream& out, const Maze& m);

#endif // MAZE_H
