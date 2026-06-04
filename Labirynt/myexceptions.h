#ifndef MYEXCEPTIONS_H
#define MYEXCEPTIONS_H

#include <exception>
#include <string>

/*
 * Klasa MyExceptions zawiera definicje wyjatkow uzywanych w projekcie.
 * Kazdy wyjatek dziedziczy po std::exception i nadpisuje metode what(),
 * ktora zwraca opis bledu jako tekst.
 *
 * Wyjatki sa zdefiniowane jako klasy wewnetrzne (nested classes) klasy MyExceptions.
 */
class MyExceptions
{
public:

    /*
     * Wyjatek rzucany gdy indeks tablicy lub wspolrzedna jest poza zakresem.
     * Np. gdy probujemy odczytac pole (x, y) ktore nie istnieje w labiryncie.
     */
    class OutOfBounds : public std::exception
    {
    private:
        std::string _message; // przechowuje opis bledu

    public:
        /*
         * Konstruktor domyslny - ustawia ogolny komunikat bledu
         */
        OutOfBounds();

        /*
         * Konstruktor z wiadomoscia - pozwala podac wlasny opis bledu
         *
         * @param message tresc komunikatu o bledzie
         */
        OutOfBounds(const std::string& message);

        /*
         * Metoda what() - zwraca opis bledu jako tekst
         * Jest to metoda wirtualna odziedziczona z std::exception
         *
         * @return tekst opisujacy blad
         */
        virtual const char* what() const noexcept override;
    };

    /*
     * Wyjatek rzucany gdy przekazano niepoprawny argument do funkcji.
     * Np. gdy podajemy ujemny rozmiar tablicy lub wskaznik nullptr.
     */
    class InvalidArgument : public std::exception
    {
    private:
        std::string _message; // przechowuje opis bledu

    public:
        /*
         * Konstruktor domyslny - ustawia ogolny komunikat bledu
         */
        InvalidArgument();

        /*
         * Konstruktor z wiadomoscia - pozwala podac wlasny opis bledu
         *
         * @param message tresc komunikatu o bledzie
         */
        InvalidArgument(const std::string& message);

        /*
         * Metoda what() - zwraca opis bledu jako tekst
         *
         * @return tekst opisujacy blad
         */
        virtual const char* what() const noexcept override;
    };

    /*
     * Wyjatek rzucany gdy nie istnieje droga w labiryncie od startu do mety.
     */
    class NoPath : public std::exception
    {
    private:
        std::string _message; // przechowuje opis bledu

    public:
        /*
         * Konstruktor domyslny - ustawia ogolny komunikat bledu
         */
        NoPath();

        /*
         * Konstruktor z wiadomoscia - pozwala podac wlasny opis bledu
         *
         * @param message tresc komunikatu o bledzie
         */
        NoPath(const std::string& message);

        /*
         * Metoda what() - zwraca opis bledu jako tekst
         *
         * @return tekst opisujacy blad
         */
        virtual const char* what() const noexcept override;
    };
};

#endif // MYEXCEPTIONS_H
