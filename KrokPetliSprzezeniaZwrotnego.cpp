
#include "KrokPetliSprzezeniaZwrotnego.h"

double KrokPetliSprzezeniaZwrotnego::operator()(RegulatorPID &regulator, ModelARX &model, double poprzednieWyjscie)
{
    const double wartoscZadana = 1.0;

    // 1. Oblicz uchyb
    double uchyb = wartoscZadana - poprzednieWyjscie;

    // 2. Wykonaj kilka kroków regulatora (np. 3 kroki, żeby pokazać "działanie w czasie")
    double sterowanie = 0.0;
    for (int i = 0; i < 3; ++i)
    {
        sterowanie = regulator.symuluj(uchyb); // Regulator przetwarza uchyb na sterowanie
    }

    // 3. Przekaż sterowanie do modelu
    double wyjscie = model.symuluj(sterowanie);

    // 4. Zwróć wartość regulowaną (nowe wyjście modelu)
    return wyjscie;
}