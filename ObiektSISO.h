
#ifndef OBIEKT_SISO_H
#define OBIEKT_SISO_H
/**
 * @author Jessica Adamczyk
 * @class ObiektSISO
 * @brief Wirtualna klasa interfejsu (jedno wejście i jedno wyjście)
 */
class ObiektSISO
{
public:
    virtual double symuluj(double u) = 0;
    virtual ~ObiektSISO() = default;
};

#endif // OBIEKT_SISO_H
