#ifndef PETLA_SPRZEZENIA_ZWROTNEGO_H
#define PETLA_SPRZEZENIA_ZWROTNEGO_H

#include "Komponent.h"
#include <memory> // For std::shared_ptr

/**
 * @class PetlaSprzezeniaZwrotnego
 * @brief Reprezentuje pętlę sprzężenia zwrotnego jako Komponent.
 *
 * Pętla składa się z ścieżki prostej i ścieżki sprzężenia zwrotnego.
 * Sygnał wejściowy 'u' jest porównywany z sygnałem ze ścieżki sprzężenia,
 * tworząc sygnał uchybu 'e'. Ten uchyb jest następnie przetwarzany przez
 * ścieżkę prostą, dając sygnał wyjściowy 'y'.
 * y_poprzednie jest używane jako wejście do ścieżki sprzężenia.
 */
class PetlaSprzezeniaZwrotnego : public Komponent {
private:
    std::shared_ptr<Komponent> sciezkaProsta;
    std::shared_ptr<Komponent> sciezkaSprzezenia;
    double poprzednieWyjsciePetli;

public:
    /**
     * @brief Konstruktor.
     * @param poczatkoweWyjscie Opcjonalna wartość początkowa dla poprzedniego wyjścia pętli.
     */
    PetlaSprzezeniaZwrotnego(double poczatkoweWyjscie = 0.0);

    virtual ~PetlaSprzezeniaZwrotnego() = default;

    /**
     * @brief Symuluje jeden krok pętli sprzężenia zwrotnego.
     * @param u Sygnał wejściowy (np. wartość zadana).
     * @return Sygnał wyjściowy pętli.
     */
    double symuluj(double u) override;

    /**
     * @brief Ustawia komponent dla ścieżki prostej pętli.
     * @param sciezka Komponent (może być Kompozyt) dla ścieżki prostej.
     */
    void ustawSciezkeProsta(std::shared_ptr<Komponent> sciezka);

    /**
     * @brief Ustawia komponent dla ścieżki sprzężenia zwrotnego.
     * @param sciezka Komponent (może być Kompozyt) dla ścieżki sprzężenia.
     */
    void ustawSciezkeSprzezenia(std::shared_ptr<Komponent> sciezka);

    /**
     * @brief Pobiera aktualną wartość poprzedniego wyjścia pętli.
     * @return Wartość poprzedniego wyjścia.
     */
    double pobierzPoprzednieWyjscie() const;

    /**
     * @brief Resetuje stan pętli (np. poprzednieWyjsciePetli do wartości początkowej).
     * @param poczatkoweWyjscie Wartość, na którą zresetować poprzednie wyjście.
     */
    void resetuj(double poczatkoweWyjscie = 0.0);

    // Metody dodaj/usun z Komponent - tutaj mogą nie mieć sensu lub wymagać specyficznej implementacji.
    // Na razie pozostawiamy domyślne (puste) lub można zgłosić błąd.
    // Jeśli chcemy, aby dodaj/usun modyfikowały np. sciezkaProsta (jeśli jest to kompozyt),
    // wymagałoby to dodatkowej logiki i rzutowania.
    // Dla jasności API, dedykowane metody ustawSciezkeProsta/Sprzezenia są lepsze.
    void dodaj(std::shared_ptr<Komponent> komponent) override {
        // Można zaimplementować, np. dodawanie do sciezkiProsta, jeśli jest to Kompozyt
        // lub zgłosić wyjątek, że ta operacja nie jest wspierana w ten sposób.
        // Na razie pozostawiamy puste, aby nie komplikować.
        // Komponent::dodaj(komponent); // Domyślna implementacja nic nie robi.
    }

    void usun(std::shared_ptr<Komponent> komponent) override {
        // Podobnie jak w dodaj.
        // Komponent::usun(komponent); // Domyślna implementacja nic nie robi.
    }
};

#endif // PETLA_SPRZEZENIA_ZWROTNEGO_H
