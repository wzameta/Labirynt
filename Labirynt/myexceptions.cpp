#include "myexceptions.h"

// ============================================================
// Implementacja wyjatku OutOfBounds
// ============================================================

/*
 * Konstruktor domyslny - ustawia ogolny komunikat bledu
 */
MyExceptions::OutOfBounds::OutOfBounds()
    : _message("Index out of bounds")
{
}

/*
 * Konstruktor z wiadomoscia - ustawia podany komunikat bledu
 */
MyExceptions::OutOfBounds::OutOfBounds(const std::string& message)
    : _message(message)
{
}

/*
 * Metoda what() - zwraca opis bledu jako tekst (wymagane przez std::exception)
 */
const char* MyExceptions::OutOfBounds::what() const noexcept
{
    return _message.c_str();
}

// ============================================================
// Implementacja wyjatku InvalidArgument
// ============================================================

/*
 * Konstruktor domyslny - ustawia ogolny komunikat bledu
 */
MyExceptions::InvalidArgument::InvalidArgument()
    : _message("Invalid argument")
{
}

/*
 * Konstruktor z wiadomoscia - ustawia podany komunikat bledu
 */
MyExceptions::InvalidArgument::InvalidArgument(const std::string& message)
    : _message(message)
{
}

/*
 * Metoda what() - zwraca opis bledu jako tekst (wymagane przez std::exception)
 */
const char* MyExceptions::InvalidArgument::what() const noexcept
{
    return _message.c_str();
}

// ============================================================
// Implementacja wyjatku NoPath
// ============================================================

/*
 * Konstruktor domyslny - ustawia ogolny komunikat bledu
 */
MyExceptions::NoPath::NoPath()
    : _message("No path found in maze")
{
}

/*
 * Konstruktor z wiadomoscia - ustawia podany komunikat bledu
 */
MyExceptions::NoPath::NoPath(const std::string& message)
    : _message(message)
{
}

/*
 * Metoda what() - zwraca opis bledu jako tekst (wymagane przez std::exception)
 */
const char* MyExceptions::NoPath::what() const noexcept
{
    return _message.c_str();
}
