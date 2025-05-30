#ifndef FABRYKASYGNALU_H
#define FABRYKASYGNALU_H

/**
 * @author Jessica Adamczyk
 * @class FabrykaSygnalu
 * @brief Klasa odpowiedzialna za tworzenie obiektów generatorów sygnału na podstawie danych wejściowych (deserializacja).
 */

#include "SygnalGenerator.h"
#include "WartoscStalaGenerator.h"
#include "SinusGenerator.h"
#include "ProstokatGenerator.h"
#include "TrojkatGenerator.h"
#include "SzumBialyGenerator.h"
#include "OgranicznikAmplitudy.h"
#include <string>
#include <istream>
#include <stdexcept> // For std::runtime_error

class FabrykaSygnalu
{
public:
    static SygnalGenerator *wczytaj(std::istream &is);
};

#endif // FABRYKASYGNALU_H
