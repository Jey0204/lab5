#ifndef KOMPONENT_H
#define KOMPONENT_H

#include "ObiektSISO.h"
#include <vector>
#include <memory>

/**
 * @author Jessica Adamczyk
 * @class Komponent
 * @brief Bazowa klasa dla wzorca Kompozyt dziedzicząca z ObiektSISO
 */
class Komponent : public ObiektSISO
{
public:
    virtual ~Komponent() = default;

    virtual double symuluj(double u) override = 0;

    virtual void dodaj(std::shared_ptr<Komponent> komponent) {}
    virtual void usun(std::shared_ptr<Komponent> komponent) {}

protected:
    std::vector<std::shared_ptr<Komponent>> komponenty;
};

#endif // KOMPONENT_H
