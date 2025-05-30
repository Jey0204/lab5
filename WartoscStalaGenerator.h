#ifndef WARTOSCSTALAGENERATOR_H
#define WARTOSCSTALAGENERATOR_H

#include "SygnalGenerator.h"

/**
 * @class WartoscStalaGenerator
 * @brief Generator sygnału zwracający stałą wartość w każdej próbce.
 * @author Jessica Adamczyk
 */

class WartoscStalaGenerator : public SygnalGenerator
{
private:
    double m_wartosc;

public:
    WartoscStalaGenerator(double wartosc);
    double generuj() override;
    void zapisz(std::ostream &os) const override;
    std::string getType() const override { return "WartoscStalaGenerator"; }

    void ustawWartosc(double wartosc) { m_wartosc = wartosc; }
    double pobierzWartosc() const { return m_wartosc; }
};

#endif // WARTOSCSTALAGENERATOR_H
