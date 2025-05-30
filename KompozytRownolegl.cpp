#include "KompozytRownolegl.h"
#include <algorithm>

double KompozytRownolegl::symuluj(double u)
{
    double suma = 0.0;

    for (auto &komponent : listaKomponentow)
    {
        if (komponent != nullptr)
        {
            suma += komponent->symuluj(u);
        }
    }

    return suma;
}

void KompozytRownolegl::dodaj(std::shared_ptr<Komponent> komponent)
{
    if (komponent != nullptr)
    {
        listaKomponentow.push_back(komponent);
    }
}

void KompozytRownolegl::usun(std::shared_ptr<Komponent> komponent)
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
