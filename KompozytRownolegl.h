#ifndef KOMPOZYT_ROWNOLEGL_H
#define KOMPOZYT_ROWNOLEGL_H

#include "Komponent.h"
#include <vector>
#include <memory>

/**
 * @author Jessica Adamczyk
 * @class KompozytRownolegl
 * @brief Kompozyt łączący komponenty równolegle - wszystkie otrzymują ten sam sygnał wejściowy
 *        i ich wyjścia są sumowane
 */
class KompozytRownolegl : public Komponent
{
private:
    std::vector<std::shared_ptr<Komponent>> listaKomponentow;

public:
    double symuluj(double u) override;

    void dodaj(std::shared_ptr<Komponent> komponent) override;

    void usun(std::shared_ptr<Komponent> komponent) override;

    size_t liczbaKomponentow() const { return listaKomponentow.size(); }
};

#endif // KOMPOZYT_ROWNOLEGL_H
