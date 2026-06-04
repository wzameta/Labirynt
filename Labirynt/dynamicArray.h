#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "myexceptions.h"

/*
 * Szablon klasy DynamicArray - dynamiczna tablica o zmiennym rozmiarze.
 *
 * Jest to "template" (szablon) - oznacza to, ze mozemy uzyc tej klasy
 * dla roznych typow danych. Np. DynamicArray<Point> lub DynamicArray<int>.
 *
 * Klasa dziala podobnie do std::vector:
 * - przechowuje elementy w dynamicznie alokowanej tablicy
 * - automatycznie zwieksza rozmiar gdy jest za mala (capacity)
 *
 * Wazna roznica: _size = ile elementow aktualnie przechowujemy
 *               _capacity = ile elementow zmiesci sie bez realokacji
 *
 * Cale cialo szablonu musi byc w pliku .h (nie mozna rozdzielic na .h/.cpp
 * w tradycyjny sposob - kompilator musi widziec cala definicje szablonu).
 */
template <typename T>
class DynamicArray
{
private:
    T* _data;     // wskaznik na dynamicznie alokowana tablice
    unsigned _size;     // aktualna liczba przechowywanych elementow
    unsigned _capacity; // pojemnosc tablicy (ile sie zmiesci zanim bedziemy rozszerzac)

    /*
     * Rozszerza tablice dwukrotnie gdy jest pelna.
     * Alokuje nowa, wieksza tablice, kopiuje dane, usuwa stara.
     */
    void resize()
    {
        // Podwajamy pojemnosc (lub ustawiamy na 1 jesli byla 0)
        unsigned newCapacity = (_capacity == 0) ? 1 : _capacity * 2;

        // Alokujemy nowa, wieksza tablice
        T* newData = new T[newCapacity];

        // Kopiujemy wszystkie istniejace elementy do nowej tablicy
        for (unsigned i = 0; i < _size; i++)
        {
            newData[i] = _data[i];
        }

        // Usuwamy stara tablice
        delete[] _data;

        // Ustawiamy nowy wskaznik i pojemnosc
        _data = newData;
        _capacity = newCapacity;
    }

public:
    /*
     * Konstruktor domyslny - tworzy pusta tablice
     */
    DynamicArray()
        : _data(nullptr), _size(0), _capacity(0)
    {
    }

    /*
     * Destruktor - zwalnia pamiec
     */
    ~DynamicArray()
    {
        delete[] _data;
        _data = nullptr;
    }

    /*
     * Konstruktor kopiujacy - tworzy niezalezna kopie tablicy.
     * Konieczny bo przechowujemy wskaznik (_data) - bez tego
     * dwa obiekty wskazywaylyby na ten sam obszar pamieci!
     *
     * @param other tablica do skopiowania
     */
    DynamicArray(const DynamicArray<T>& other)
        : _data(nullptr), _size(other._size), _capacity(other._capacity)
    {
        if (_capacity > 0)
        {
            _data = new T[_capacity];
            for (unsigned i = 0; i < _size; i++)
            {
                _data[i] = other._data[i];
            }
        }
    }

    /*
     * Operator przypisania - kopiuje zawartosc innej tablicy.
     * Konieczny z tych samych powodow co konstruktor kopiujacy.
     *
     * @param other tablica do skopiowania
     * @return referencja na siebie (umozliwia a = b = c)
     */
    DynamicArray<T>& operator=(const DynamicArray<T>& other)
    {
        // Sprawdzamy czy nie przypisujemy do siebie samego (a = a)
        if (this == &other)
        {
            return *this;
        }

        // Usuwamy stare dane
        delete[] _data;

        // Kopiujemy rozmiar i pojemnosc
        _size = other._size;
        _capacity = other._capacity;

        // Kopiujemy dane
        if (_capacity > 0)
        {
            _data = new T[_capacity];
            for (unsigned i = 0; i < _size; i++)
            {
                _data[i] = other._data[i];
            }
        }
        else
        {
            _data = nullptr;
        }

        return *this;
    }

    /*
     * Dodaje element na koniec tablicy.
     * Jezeli tablica jest pelna, automatycznie ja rozszerza.
     *
     * @param item element do dodania
     */
    void add(const T& item)
    {
        // Sprawdzamy czy jest miejsce, jezeli nie - rozszerzamy
        if (_size == _capacity)
        {
            resize();
        }

        // Dodajemy element na koniec i zwiekszamy licznik
        _data[_size] = item;
        _size++;
    }

    /*
     * Usuwa wszystkie elementy z tablicy (ale nie zwalnia pamieci).
     * Po wywolaniu clear() rozmiar = 0, ale pojemnosc zostaje.
     */
    void clear()
    {
        _size = 0; // ustawiamy licznik na 0 (dane dalej sa w pamieci ale "ignorujemy" je)
    }

    /*
     * Zwraca aktualna liczbe przechowywanych elementow
     *
     * @return liczba elementow
     */
    unsigned size() const
    {
        return _size;
    }

    /*
     * Operator [] - dostep do elementu po indeksie (tylko odczyt).
     *
     * @param i indeks elementu (0 do size-1)
     * @return element pod danym indeksem
     *
     * @throws MyExceptions::OutOfBounds gdy indeks jest poza zakresem
     */
    T operator[](unsigned i) const
    {
        if (i >= _size)
        {
            throw MyExceptions::OutOfBounds("DynamicArray index out of bounds");
        }
        return _data[i];
    }
};

#endif // DYNAMICARRAY_H
