#ifndef SYGNALDEKORATOR_H
#define SYGNALDEKORATOR_H

#include "SygnalGenerator.h"

/**
 * @class SygnalDekorator
 * @brief Abstrakcyjna klasa bazowa dla dekoratorów sygnałów, umożliwiająca modyfikację działania innych generatorów sygnału.
 * @author Jessica Adamczyk
 */

class SygnalDekorator : public SygnalGenerator
{
protected:
    SygnalGenerator *m_dekorowanySygnal;

public:
    SygnalDekorator(SygnalGenerator *dekorowanySygnal);
    virtual ~SygnalDekorator();
    double generuj() override;
};

#endif // SYGNALDEKORATOR_H
