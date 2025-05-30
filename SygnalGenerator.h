#ifndef SYGNALGENERATOR_H
#define SYGNALGENERATOR_H

#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

/**
 * @class SygnalGenerator
 * @brief Abstrakcyjna klasa bazowa reprezentująca interfejs dla wszystkich generatorów sygnału. Umożliwia generowanie i zapisywanie sygnałów.
 * @author Jessica Adamczyk
 */

class FabrykaSygnalu;

class SygnalGenerator
{
public:
    virtual ~SygnalGenerator() {}
    virtual double generuj() = 0;
    virtual void zapisz(std::ostream &os) const = 0;
    virtual std::string getType() const = 0;
};

#endif // SYGNALGENERATOR_H
