#ifndef SINUSGENERATOR_H
#define SINUSGENERATOR_H

#define _USE_MATH_DEFINES
#include <cmath>

#include "SygnalDekorator.h"

/**
 * @class SinusGenerator
 * @brief Dekorator generujący sygnał sinusoidalny o zadanej amplitudzie i częstotliwości przy użyciu algorytmu różnicowego.
 * @author Jessica Adamczyk
 */

class SinusGenerator : public SygnalDekorator
{
private:
    double m_amplituda;
    double m_czestotliwosc;
    double m_omega;
    double m_x1;
    double m_x2;

public:
    SinusGenerator(SygnalGenerator *dekorowanySygnal, double amplituda, double czestotliwosc);
    double generuj() override;
    void zapisz(std::ostream &os) const override;
    std::string getType() const override { return "SinusGenerator"; }

    void ustawParametry(double amplituda, double czestotliwosc)
    {
        m_amplituda = amplituda;
        m_czestotliwosc = czestotliwosc;
        m_omega = 2.0 * M_PI * m_czestotliwosc;
        m_x1 = 0;
        m_x2 = m_amplituda * sin(m_omega);
    }
    double pobierzAmplitude() const { return m_amplituda; }
    double pobierzCzestotliwosc() const { return m_czestotliwosc; }

    void ustawStanWewnetrzny(double x1, double x2)
    {
        m_x1 = x1;
        m_x2 = x2;
    }
};

#endif
