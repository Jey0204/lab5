
#ifndef REGULATORPID_H
#define REGULATORPID_H

#include <string>
#include "ObiektSISO.h"
/**
 * @author Jessica Adamczyk
 * @class RegulatorPID
 * @brief Klasa implementująca regulator PID.
 */

class RegulatorPID : public ObiektSISO
{
private:
    double k;  // Wzmocnienie proporcjonalne
    double Ti; // Czas całkowania
    double Td; // Czas różniczkowania

    double sumaUchybow;    // Pamięć części całkującej
    double poprzedniUchyb; // Pamięć części różniczkującej

    bool czyPI;
    bool czyPID;

    void sprawdzDodatnie(double wartosc, const std::string &nazwa);

public:
    // Konstruktor regulatora P
    RegulatorPID(double k);

    // Konstruktor regulatora PI
    RegulatorPID(double k, double Ti);

    // Konstruktor regulatora PID
    RegulatorPID(double k, double Ti, double Td);

    // Settery
    void setK(double k);
    void setTi(double Ti);
    void setTd(double Td);

    // Symulacja
    double symuluj(double uchyb) override;
};

#endif // REGULATORPID_H
