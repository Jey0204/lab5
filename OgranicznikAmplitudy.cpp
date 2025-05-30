#include "OgranicznikAmplitudy.h"

OgranicznikAmplitudy::OgranicznikAmplitudy(SygnalGenerator *dekorowanySygnal, double limit)
    : SygnalDekorator(dekorowanySygnal)
{
    if (limit < 0)
        limit = -limit;
    m_limitGowny = limit;
    m_limitDolny = -limit;
}

double OgranicznikAmplitudy::generuj()
{
    double wartoscNielimitowana = SygnalDekorator::generuj();
    return std::max(m_limitDolny, std::min(wartoscNielimitowana, m_limitGowny));
}

void OgranicznikAmplitudy::zapisz(std::ostream &os) const
{
    os << getType() << std::endl;
    os << m_limitGowny << std::endl;
    if (m_dekorowanySygnal)
    {
        m_dekorowanySygnal->zapisz(os);
    }
    else
    {
        os << "NULL" << std::endl;
    }
}
