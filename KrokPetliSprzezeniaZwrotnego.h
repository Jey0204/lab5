
#ifndef KROK_PETLI_SPRZEZENIA_ZWROTNEGO_H
#define KROK_PETLI_SPRZEZENIA_ZWROTNEGO_H

#include "RegulatorPID.h"
#include "ModelARX.h"

class KrokPetliSprzezeniaZwrotnego
{
public:
    double operator()(RegulatorPID &regulator, ModelARX &model, double poprzednieWyjscie);
};

#endif // KROK_PETLI_SPRZEZENIA_ZWROTNEGO_H
