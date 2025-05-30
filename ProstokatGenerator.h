#ifndef PROSTOKATGENERATOR_H
#define PROSTOKATGENERATOR_H

#include "SygnalDekorator.h"
#include <cmath>

/**
 * @author Jessica Adamczyk
 * @class ProstokatGenerator
 * @brief Dekorator generujący sygnał prostokątny o zadanej amplitudzie, częstotliwości i wypełnieniu.
 */

class ProstokatGenerator : public SygnalDekorator
{
private:
    double m_amplituda;
    double m_czestotliwosc;
    double m_wypelnienie;
    double m_okres;
    double m_czas;

public:
    ProstokatGenerator(SygnalGenerator *dekorowanySygnal, double amplituda, double czestotliwosc, double wypelnienie);
    double generuj() override;
    void zapisz(std::ostream &os) const override;
    std::string getType() const override { return "ProstokatGenerator"; }

    void ustawParametry(double amplituda, double czestotliwosc, double wypelnienie)
    {
        m_amplituda = amplituda;
        m_czestotliwosc = czestotliwosc;
        m_wypelnienie = wypelnienie;
        m_okres = (m_czestotliwosc > 0) ? 1.0 / m_czestotliwosc : 0.0;
    }
    double pobierzAmplitude() const { return m_amplituda; }
    double pobierzCzestotliwosc() const { return m_czestotliwosc; }
    double pobierzWypelnienie() const { return m_wypelnienie; }
    double pobierzCzas() const { return m_czas; }
    void ustawCzas(double czas) { m_czas = czas; }
};

#endif // PROSTOKATGENERATOR_H
