#define _USE_MATH_DEFINES
#include "FabrykaSygnalu.h"
#include <iostream>

SygnalGenerator *FabrykaSygnalu::wczytaj(std::istream &is)
{
    std::string typSygnalu;
    is >> typSygnalu;
    is.ignore();

    if (typSygnalu == "NULL")
    {
        return nullptr;
    }

    SygnalGenerator *dekorowanySygnal = nullptr;
    SygnalGenerator *nowySygnal = nullptr;

    if (typSygnalu == "WartoscStalaGenerator")
    {
        double wartosc;
        is >> wartosc;
        is.ignore();
        nowySygnal = new WartoscStalaGenerator(wartosc);
    }
    else if (typSygnalu == "SinusGenerator")
    {
        double amplituda, czestotliwosc, x1, x2;
        is >> amplituda >> czestotliwosc >> x1 >> x2;
        is.ignore();
        dekorowanySygnal = wczytaj(is);
        SinusGenerator *sinGen = new SinusGenerator(dekorowanySygnal, amplituda, czestotliwosc);
        sinGen->ustawStanWewnetrzny(x1, x2);
        nowySygnal = sinGen;
    }
    else if (typSygnalu == "ProstokatGenerator")
    {
        double amplituda, czestotliwosc, wypelnienie, czas;
        is >> amplituda >> czestotliwosc >> wypelnienie >> czas;
        is.ignore();
        dekorowanySygnal = wczytaj(is);
        ProstokatGenerator *pGen = new ProstokatGenerator(dekorowanySygnal, amplituda, czestotliwosc, wypelnienie);
        pGen->ustawCzas(czas);
        nowySygnal = pGen;
    }
    else if (typSygnalu == "TrojkatGenerator")
    {
        double amplituda, czestotliwosc, wypelnienie, czas;
        is >> amplituda >> czestotliwosc >> wypelnienie >> czas;
        is.ignore();
        dekorowanySygnal = wczytaj(is);
        TrojkatGenerator *tGen = new TrojkatGenerator(dekorowanySygnal, amplituda, czestotliwosc, wypelnienie);
        tGen->ustawCzas(czas);
        nowySygnal = tGen;
    }
    else if (typSygnalu == "SzumBialyGenerator")
    {
        double ampWariancja;
        is >> ampWariancja;
        is.ignore();
        dekorowanySygnal = wczytaj(is);
        nowySygnal = new SzumBialyGenerator(dekorowanySygnal, ampWariancja);
    }
    else if (typSygnalu == "OgranicznikAmplitudy")
    {
        double limit;
        is >> limit;
        is.ignore();
        dekorowanySygnal = wczytaj(is);
        nowySygnal = new OgranicznikAmplitudy(dekorowanySygnal, limit);
    }
    else
    {
        throw std::runtime_error("Nieznany typ sygnału podczas deserializacji: " + typSygnalu);
    }
    return nowySygnal;
}
