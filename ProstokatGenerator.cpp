#include "ProstokatGenerator.h"
#include <cmath> // For fmod

ProstokatGenerator::ProstokatGenerator(SygnalGenerator *dekorowanySygnal, double amplituda, double czestotliwosc, double wypelnienie)
    : SygnalDekorator(dekorowanySygnal), m_amplituda(amplituda), m_czestotliwosc(czestotliwosc), m_wypelnienie(wypelnienie), m_czas(0.0)
{
    if (m_czestotliwosc > 0)
    {
        m_okres = 1.0 / m_czestotliwosc;
    }
    else
    {
        m_okres = 0.0;
    }
}

double ProstokatGenerator::generuj()
{
    double wartoscGenerowana = 0.0;
    if (m_okres > 0.0)
    {
        double czasWOkresie = fmod(m_czas, m_okres);
        if (czasWOkresie < m_wypelnienie * m_okres)
        {
            wartoscGenerowana = m_amplituda;
        }
        else
        {
            wartoscGenerowana = -m_amplituda;
        }
        // Zakładamy próbkowanie z częstotliwością 1 Hz (dt = 1.0)
        // W rzeczywistej implementacji dt powinno być parametrem
        double dt = 0.1;  // 10 próbek na sekundę dla lepszej wizualizacji
        m_czas += dt;
    }
    else
    {
        wartoscGenerowana = (m_wypelnienie > 0) ? m_amplituda : -m_amplituda;
    }
    return wartoscGenerowana + SygnalDekorator::generuj();
}

void ProstokatGenerator::zapisz(std::ostream &os) const
{
    os << getType() << std::endl;
    os << m_amplituda << std::endl;
    os << m_czestotliwosc << std::endl;
    os << m_wypelnienie << std::endl;
    os << m_czas << std::endl;
    if (m_dekorowanySygnal)
    {
        m_dekorowanySygnal->zapisz(os);
    }
    else
    {
        os << "NULL" << std::endl;
    }
}
