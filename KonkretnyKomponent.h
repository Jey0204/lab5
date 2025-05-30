#ifndef KONKRETNY_KOMPONENT_H
#define KONKRETNY_KOMPONENT_H

#include "Komponent.h"

/**
 * @author Jessica Adamczyk
 * @class KonkretnyKomponent
 * @brief Przykładowa implementacja konkretnego komponentu (liść w drzewie kompozytu)
 */
class KonkretnyKomponent : public Komponent
{
private:
    double wspolczynnik;

public:
    KonkretnyKomponent(double wsp = 1.0) : wspolczynnik(wsp) {}

    double symuluj(double u) override
    {
        return u * wspolczynnik;
    }

    void ustawWspolczynnik(double wsp) { wspolczynnik = wsp; }

    double pobierzWspolczynnik() const { return wspolczynnik; }
};

#endif // KONKRETNY_KOMPONENT_H
