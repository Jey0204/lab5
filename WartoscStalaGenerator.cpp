#include "WartoscStalaGenerator.h"

WartoscStalaGenerator::WartoscStalaGenerator(double wartosc) : m_wartosc(wartosc) {}

double WartoscStalaGenerator::generuj()
{
    return m_wartosc;
}

void WartoscStalaGenerator::zapisz(std::ostream &os) const
{
    os << getType() << std::endl;
    os << m_wartosc << std::endl;
}
