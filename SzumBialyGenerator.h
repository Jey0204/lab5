#ifndef SZUMBIALYGENERATOR_H
#define SZUMBIALYGENERATOR_H

#include "SygnalDekorator.h"
#include <random> // For random number generation
/**
 * @class SzumBialyGenerator
 * @brief Dekorator generujący sygnał białego szumu o równomiernym rozkładzie losowym i zadanej amplitudzie lub wariancji.
 * @author Jessica Adamczyk
 */

class SzumBialyGenerator : public SygnalDekorator
{
private:
    double m_amplituda_lub_wariancja;
    std::mt19937 m_generatorLiczbLosowych;
    std::uniform_real_distribution<double> m_dystrybucja;

public:
    SzumBialyGenerator(SygnalGenerator *dekorowanySygnal, double amplituda);
    double generuj() override;
    void zapisz(std::ostream &os) const override;
    std::string getType() const override { return "SzumBialyGenerator"; }

    void ustawParametry(double amplituda)
    {
        m_amplituda_lub_wariancja = amplituda;
        m_dystrybucja = std::uniform_real_distribution<double>(-m_amplituda_lub_wariancja, m_amplituda_lub_wariancja);
    }
    double pobierzAmplitudeLubWariancje() const { return m_amplituda_lub_wariancja; }
};

#endif // SZUMBIALYGENERATOR_H
