#include "SygnalDekorator.h"

SygnalDekorator::SygnalDekorator(SygnalGenerator *dekorowanySygnal) : m_dekorowanySygnal(dekorowanySygnal) {}

SygnalDekorator::~SygnalDekorator()
{
    delete m_dekorowanySygnal;
}

double SygnalDekorator::generuj()
{
    if (m_dekorowanySygnal)
    {
        return m_dekorowanySygnal->generuj();
    }
    return 0.0;
}
