#ifndef INTERFEJSUZYTKOWNIKA_H
#define INTERFEJSUZYTKOWNIKA_H

#include "SygnalGenerator.h"
#include "WartoscStalaGenerator.h"
#include "SinusGenerator.h"
#include "ProstokatGenerator.h"
#include "TrojkatGenerator.h"
#include "SzumBialyGenerator.h"
#include "OgranicznikAmplitudy.h"
#include "SygnalDekorator.h"
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <iomanip>

/**
 * @class InterfejsUzytkownika
 * @brief Klasa odpowiedzialna za interakcję z użytkownikiem w terminalu
 * @author Assistant
 */
class InterfejsUzytkownika
{
private:
    std::unique_ptr<SygnalGenerator> m_generator;
    
    void wyswietlMenu();
    void wyswietlMenuSygnalow();
    int pobierzWybor(int min, int max);
    double pobierzLiczbe(const std::string& prompt);
    int pobierzLiczbeCalkowita(const std::string& prompt);
    
    SygnalGenerator* stworzWartoscStala();
    SygnalGenerator* stworzSinus();
    SygnalGenerator* stworzProstokat();
    SygnalGenerator* stworzTrojkat();
    SygnalGenerator* stworzSzumBialy();
    
    void dodajOgranicznikAmplitudy();
    void generujProbki();
    void zapiszDoPliku();
    void wyswietlParametry();

public:
    InterfejsUzytkownika();
    ~InterfejsUzytkownika();
    
    void uruchom();
};

#endif // INTERFEJSUZYTKOWNIKA_H
