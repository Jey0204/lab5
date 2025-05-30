#ifndef OGRANICZNIKAMPLITUDY_H
#define OGRANICZNIKAMPLITUDY_H

#include "SygnalDekorator.h"
#include <algorithm>

/**
 * @author Jessica Adamczyk
 * @class OgranicznikAmplitudy
 * @brief Dekorator sygnału ograniczający jego amplitudę do ustalonego przedziału symetrycznego względem zera.
 */

class OgranicznikAmplitudy : public SygnalDekorator
{
private:
    double m_limitGowny;
    double m_limitDolny;

public:
    OgranicznikAmplitudy(SygnalGenerator *dekorowanySygnal, double limit);

    double generuj() override;
    void zapisz(std::ostream &os) const override;
    std::string getType() const override { return "OgranicznikAmplitudy"; }

    void ustawLimit(double limit)
    {
        m_limitGowny = limit;
        m_limitDolny = -limit;
    }
    double pobierzLimit() const { return m_limitGowny; }
};

#endif
