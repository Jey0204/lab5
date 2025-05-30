#ifndef TROJKATGENERATOR_H
#define TROJKATGENERATOR_H

#include "SygnalDekorator.h"
#include <cmath>
/**
 * @class TrojkatGenerator
 * @brief Dekorator generujący sygnał o kształcie fali trójkątnej z regulowaną amplitudą, częstotliwością i współczynnikiem wypełnienia.
 * @author Jessica Adamczyk
 */

class TrojkatGenerator : public SygnalDekorator
{
private:
    double m_amplituda;
    double m_czestotliwosc; // w Hz
    double m_wypelnienie;   // (0, 1), punkt szczytu w okresie
    double m_okres;
    double m_czas;

public:
    TrojkatGenerator(SygnalGenerator *dekorowanySygnal, double amplituda, double czestotliwosc, double wypelnienie = 0.5);
    double generuj() override;
    void zapisz(std::ostream &os) const override;
    std::string getType() const override { return "TrojkatGenerator"; }

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

#endif
