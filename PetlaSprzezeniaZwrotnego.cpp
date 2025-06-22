#include "PetlaSprzezeniaZwrotnego.h"
#include <stdexcept> // For std::runtime_error if needed

PetlaSprzezeniaZwrotnego::PetlaSprzezeniaZwrotnego(double poczatkoweWyjscie)
    : poprzednieWyjsciePetli(poczatkoweWyjscie), sciezkaProsta(nullptr), sciezkaSprzezenia(nullptr) {
    // Inicjalizacja inteligentnych wskaźników na nullptr jest dobra praktyką,
    // chociaz domyślnie też by tak było.
}

double PetlaSprzezeniaZwrotnego::symuluj(double u) {
    // Sprawdzenie, czy ścieżki są ustawione
    if (!sciezkaProsta) {
        // Można rzucić wyjątek, zwrócić u, lub inną domyślną wartość,
        // w zależności od oczekiwanego zachowania.
        // Rzucenie wyjątku jest często bezpieczniejsze, aby zasygnalizować problem konfiguracyjny.
        // throw std::runtime_error("PetlaSprzezeniaZwrotnego: sciezkaProsta nie jest ustawiona.");
        // Alternatywnie, jeśli pętla ma działać "przezroczyscie" bez konfiguracji:
        // poprzednieWyjsciePetli = u;
        // return u;
        // Na potrzeby tego zadania, przyjmijmy, że bez sciezkiProstej pętla nie działa poprawnie
        // i powinna to jakoś zasygnalizować. Dla uproszczenia, jeśli nie ma ścieżki prostej,
        // potraktujmy ją jako wzmocnienie jednostkowe na uchybie.
        // Jednakże, typowo pętla bez ścieżki prostej nie ma sensu.
        // Załóżmy, że logika biznesowa wymaga istnienia sciezkiProstej.
        // Jeśli nie, to zwrócimy uchyb (lub u jeśli nie ma też sprzężenia)
        if (!sciezkaSprzezenia) {
             poprzednieWyjsciePetli = u; // Jeśli nie ma nic, wyjście = wejście
             return u;
        }
    }

    double sygnalSprzezenia = 0.0;
    if (sciezkaSprzezenia) {
        sygnalSprzezenia = sciezkaSprzezenia->symuluj(poprzednieWyjsciePetli);
    }

    double uchyb = u - sygnalSprzezenia;
    double wyjscieSciezkiProstej;

    if (sciezkaProsta) {
        wyjscieSciezkiProstej = sciezkaProsta->symuluj(uchyb);
    } else {
        // Jeśli nie ma sciezkiProstej, ale jest sprzężenie, wyjściem staje się uchyb.
        // To zachowanie może wymagać doprecyzowania zgodnie z wymaganiami.
        wyjscieSciezkiProstej = uchyb;
    }

    poprzednieWyjsciePetli = wyjscieSciezkiProstej;
    return wyjscieSciezkiProstej;
}

void PetlaSprzezeniaZwrotnego::ustawSciezkeProsta(std::shared_ptr<Komponent> sciezka) {
    sciezkaProsta = sciezka;
}

void PetlaSprzezeniaZwrotnego::ustawSciezkeSprzezenia(std::shared_ptr<Komponent> sciezka) {
    sciezkaSprzezenia = sciezka;
}

double PetlaSprzezeniaZwrotnego::pobierzPoprzednieWyjscie() const {
    return poprzednieWyjsciePetli;
}

void PetlaSprzezeniaZwrotnego::resetuj(double poczatkoweWyjscie) {
    poprzednieWyjsciePetli = poczatkoweWyjscie;
    // Można by też chcieć zresetować stan wewnętrzny komponentów w ścieżkach,
    // jeśli mają one stan (np. inne pętle, regulatory PID z członem całkującym).
    // To wymagałoby dodania metody resetuj() do interfejsu Komponent/ObiektSISO
    // i wywołania jej rekursywnie. Na razie tego nie robimy.
    if (sciezkaProsta) {
        // np. sciezkaProsta->resetuj(); // jeśli Komponent miałby taką metodę
    }
    if (sciezkaSprzezenia) {
        // np. sciezkaSprzezenia->resetuj(); // jeśli Komponent miałby taką metodę
    }
}

// Implementacje dodaj/usun pozostają puste, zgodnie z komentarzem w .h
// Jeśli chcielibyśmy, aby `dodaj` dodawało do `sciezkaProsta` (jeśli jest to np. `KompozytSzeregowy`),
// to musielibyśmy użyć `dynamic_cast` i sprawdzić typ.
// void PetlaSprzezeniaZwrotnego::dodaj(std::shared_ptr<Komponent> komponent) {
//     if (sciezkaProsta) {
//         // Próba dodania do ścieżki prostej, jeśli jest to kompozyt
//         // To wymagałoby, aby Komponent miał publiczną metodę dodaj, co ma.
//         // Należałoby jednak upewnić się, że sciezkaProsta jest faktycznie kompozytem
//         // który może przyjmować inne komponenty.
//         // std::shared_ptr<KompozytSzeregowy> kompozyt = std::dynamic_pointer_cast<KompozytSzeregowy>(sciezkaProsta);
//         // if (kompozyt) {
//         //     kompozyt->dodaj(komponent);
//         // } else {
//         //     // Obsługa błędu lub inna logika
//         // }
//     }
//     // Jeśli nie, można by rzucić wyjątek lub zignorować.
// }

// void PetlaSprzezeniaZwrotnego::usun(std::shared_ptr<Komponent> komponent) {
//     // Analogicznie do dodaj
// }
