#include "KompozytSzeregowy.h"
#include <algorithm>

double KompozytSzeregowy::symuluj(double u)
{
    double wynik = u;

    for (auto &komponent : listaKomponentow)
    {
        if (komponent != nullptr)
        {
            wynik = komponent->symuluj(wynik);
        }
    }

    return wynik;
}

void KompozytSzeregowy::dodaj(std::shared_ptr<Komponent> komponent)
{
    if (komponent != nullptr)
    {
        listaKomponentow.push_back(komponent);
    }
}

void KompozytSzeregowy::usun(std::shared_ptr<Komponent> komponent)
{
    if (komponent != nullptr)
    {
        auto it = std::find(listaKomponentow.begin(), listaKomponentow.end(), komponent);
        if (it != listaKomponentow.end())
        {
            listaKomponentow.erase(it);
        }
    }
}
