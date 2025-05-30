
#include "RegulatorPID.h"
#include <stdexcept>

RegulatorPID::RegulatorPID(double k)
    : k(k), Ti(0), Td(0), sumaUchybow(0), poprzedniUchyb(0), czyPI(false), czyPID(false)
{
    sprawdzDodatnie(k, "Wzmocnienie k");
}

RegulatorPID::RegulatorPID(double k, double Ti)
    : k(k), Ti(Ti), Td(0), sumaUchybow(0), poprzedniUchyb(0), czyPI(true), czyPID(false)
{
    sprawdzDodatnie(k, "Wzmocnienie k");
    sprawdzDodatnie(Ti, "Czas całkowania Ti");
}

RegulatorPID::RegulatorPID(double k, double Ti, double Td)
    : k(k), Ti(Ti), Td(Td), sumaUchybow(0), poprzedniUchyb(0), czyPI(true), czyPID(true)
{
    sprawdzDodatnie(k, "Wzmocnienie k");
    sprawdzDodatnie(Ti, "Czas całkowania Ti");
    sprawdzDodatnie(Td, "Czas różniczkowania Td");
}

void RegulatorPID::sprawdzDodatnie(double wartosc, const std::string &nazwa)
{
    if (wartosc <= 0.0)
    {
        throw std::invalid_argument(nazwa + " musi być większe od zera.");
    }
}

void RegulatorPID::setK(double k)
{
    sprawdzDodatnie(k, "Wzmocnienie k");
    this->k = k;
}

void RegulatorPID::setTi(double Ti)
{
    sprawdzDodatnie(Ti, "Czas całkowania Ti");
    this->Ti = Ti;
    czyPI = true;
}

void RegulatorPID::setTd(double Td)
{
    sprawdzDodatnie(Td, "Czas różniczkowania Td");
    this->Td = Td;
    czyPID = true;
}

double RegulatorPID::symuluj(double uchyb)
{
    // Proporcjonalna część
    double u = k * uchyb;

    // Całkująca część (PI)
    if (czyPI && Ti != 0.0)
    {
        sumaUchybow += uchyb;
        u += (1.0 / Ti) * sumaUchybow;
    }

    // Różniczkująca część (PID) jesli chcemy pierwszy wzor wystarczy usunac ta czesc bez return
    if (czyPID && Td != 0.0)
    {
        double rozniczka = uchyb - poprzedniUchyb;
        u += Td * rozniczka;
    }

    poprzedniUchyb = uchyb; // Zapisz uchyb do różniczkowania

    return u;
}
