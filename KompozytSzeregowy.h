#ifndef KOMPOZYT_SZEREGOWY_H
#define KOMPOZYT_SZEREGOWY_H

#include "Komponent.h"
#include <vector>
#include <memory>

/**
 * @author Jessica Adamczyk
 * @class KompozytSzeregowy
 * @brief Kompozyt łączący komponenty szeregowo - wyjście jednego jest wejściem następnego
 */
class KompozytSzeregowy : public Komponent
{
private:
    std::vector<std::shared_ptr<Komponent>> listaKomponentow;

public:
    double symuluj(double u) override;

    void dodaj(std::shared_ptr<Komponent> komponent) override;

    void usun(std::shared_ptr<Komponent> komponent) override;

    size_t liczbaKomponentow() const { return listaKomponentow.size(); }
};

#endif // KOMPOZYT_SZEREGOWY_H
