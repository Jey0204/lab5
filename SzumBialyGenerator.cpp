#include "SzumBialyGenerator.h"
#include <chrono> // For seeding random generator

SzumBialyGenerator::SzumBialyGenerator(SygnalGenerator *dekorowanySygnal, double amplituda)
    : SygnalDekorator(dekorowanySygnal), m_amplituda_lub_wariancja(amplituda)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    m_dystrybucja = std::uniform_real_distribution<double>(-m_amplituda_lub_wariancja, m_amplituda_lub_wariancja);
}

double SzumBialyGenerator::generuj()
{
    double szum = m_dystrybucja(m_generatorLiczbLosowych); // Corrected variable name
    return szum + SygnalDekorator::generuj();
}

void SzumBialyGenerator::zapisz(std::ostream &os) const
{
    os << getType() << std::endl;
    os << m_amplituda_lub_wariancja << std::endl;
    if (m_dekorowanySygnal)
    {
        m_dekorowanySygnal->zapisz(os);
    }
    else
    {
        os << "NULL" << std::endl;
    }
}
