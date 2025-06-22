#include "InterfejsUzytkownika.h"
#include <limits>
#include <fstream>
#include <cmath>
#include <iomanip>

InterfejsUzytkownika::InterfejsUzytkownika() : m_generator(nullptr) {}

InterfejsUzytkownika::~InterfejsUzytkownika() {}

void InterfejsUzytkownika::uruchom()
{
    std::cout << "=== GENERATOR SYGNALOW - INTERFEJS UZYTKOWNIKA ===" << std::endl;
    std::cout << "Witaj w interaktywnym generatorze sygnalow!" << std::endl << std::endl;
    
    bool kontynuuj = true;
    while (kontynuuj)
    {
        wyswietlMenu();
        int wybor = pobierzWybor(1, 6);
        
        switch (wybor)
        {
            case 1:
                wyswietlMenuSygnalow();
                break;
            case 2:
                if (m_generator)
                    dodajOgranicznikAmplitudy();
                else
                    std::cout << "Najpierw wybierz sygnal!" << std::endl;
                break;
            case 3:
                if (m_generator)
                    generujProbki();
                else
                    std::cout << "Najpierw wybierz sygnal!" << std::endl;
                break;
            case 4:
                if (m_generator)
                    zapiszDoPliku();
                else
                    std::cout << "Najpierw wybierz sygnal!" << std::endl;
                break;
            case 5:
                if (m_generator)
                    wyswietlParametry();
                else
                    std::cout << "Brak aktywnego sygnalu." << std::endl;
                break;
            case 6:
                kontynuuj = false;
                std::cout << "Dziekuje za korzystanie z programu!" << std::endl;
                break;
        }
        std::cout << std::endl;
    }
}

void InterfejsUzytkownika::wyswietlMenu()
{
    std::cout << "=== MENU GLOWNE ===" << std::endl;
    std::cout << "1. Wybierz typ sygnalu" << std::endl;
    std::cout << "2. Dodaj ogranicznik amplitudy" << std::endl;
    std::cout << "3. Generuj probki sygnalu" << std::endl;
    std::cout << "4. Zapisz sygnal do pliku" << std::endl;
    std::cout << "5. Wyswietl parametry aktualnego sygnalu" << std::endl;
    std::cout << "6. Wyjscie" << std::endl;
    std::cout << "Wybierz opcje (1-6): ";
}

void InterfejsUzytkownika::wyswietlMenuSygnalow()
{
    std::cout << "\n=== WYBOR TYPU SYGNALU ===" << std::endl;
    std::cout << "1. Wartosc stala" << std::endl;
    std::cout << "2. Sygnal sinusoidalny" << std::endl;
    std::cout << "3. Sygnal prostokatny" << std::endl;
    std::cout << "4. Sygnal trojkatny" << std::endl;
    std::cout << "5. Szum bialy" << std::endl;
    std::cout << "Wybierz typ sygnalu (1-5): ";
    
    int wybor = pobierzWybor(1, 5);
    
    switch (wybor)
    {
        case 1:
            m_generator.reset(stworzWartoscStala());
            break;
        case 2:
            m_generator.reset(stworzSinus());
            break;
        case 3:
            m_generator.reset(stworzProstokat());
            break;
        case 4:
            m_generator.reset(stworzTrojkat());
            break;
        case 5:
            m_generator.reset(stworzSzumBialy());
            break;
    }
    
    if (m_generator)
    {
        std::cout << "Sygnal zostal utworzony pomyslnie!" << std::endl;
    }
}

int InterfejsUzytkownika::pobierzWybor(int min, int max)
{
    int wybor;
    while (true)
    {
        std::cin >> wybor;
        
        if (std::cin.fail() || wybor < min || wybor > max)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Nieprawidlowy wybor. Podaj liczbe z zakresu " << min << "-" << max << ": ";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return wybor;
        }
    }
}

double InterfejsUzytkownika::pobierzLiczbe(const std::string& prompt)
{
    double liczba;
    while (true)
    {
        std::cout << prompt;
        std::cin >> liczba;
        
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Nieprawidlowa wartosc. Podaj liczbe: ";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return liczba;
        }
    }
}

int InterfejsUzytkownika::pobierzLiczbeCalkowita(const std::string& prompt)
{
    int liczba;
    while (true)
    {
        std::cout << prompt;
        std::cin >> liczba;
        
        if (std::cin.fail() || liczba < 1)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Nieprawidlowa wartosc. Podaj liczbe calkowita wieksza od 0: ";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return liczba;
        }
    }
}

SygnalGenerator* InterfejsUzytkownika::stworzWartoscStala()
{
    std::cout << "\n=== KONFIGURACJA WARTOSCI STALEJ ===" << std::endl;
    double wartosc = pobierzLiczbe("Podaj wartosc stala: ");
    
    return new WartoscStalaGenerator(wartosc);
}

SygnalGenerator* InterfejsUzytkownika::stworzSinus()
{
    std::cout << "\n=== KONFIGURACJA SYGNALU SINUSOIDALNEGO ===" << std::endl;
    double amplituda = pobierzLiczbe("Podaj amplitude: ");
    double czestotliwosc = pobierzLiczbe("Podaj czestotliwosc [Hz]: ");
    
    // Sinus jest dekoratorem, wiec potrzebuje sygnalu bazowego (wartosc stala = 0)
    SygnalGenerator* bazowy = new WartoscStalaGenerator(0.0);
    return new SinusGenerator(bazowy, amplituda, czestotliwosc);
}

SygnalGenerator* InterfejsUzytkownika::stworzProstokat()
{
    std::cout << "\n=== KONFIGURACJA SYGNALU PROSTOKATNEGO ===" << std::endl;
    double amplituda = pobierzLiczbe("Podaj amplitude: ");
    double okres = pobierzLiczbe("Podaj okres [s]: ");
    double wypelnienie = pobierzLiczbe("Podaj wypelnienie (0.0-1.0): ");
    
    // Sprawdzenie zakresu wypelnienia
    while (wypelnienie < 0.0 || wypelnienie > 1.0)
    {
        std::cout << "Wypelnienie musi byc w zakresie 0.0-1.0!" << std::endl;
        wypelnienie = pobierzLiczbe("Podaj wypelnienie (0.0-1.0): ");
    }
    
    // Konwersja okresu na częstotliwość
    double czestotliwosc = (okres > 0.0) ? (1.0 / okres) : 0.0;
    
    SygnalGenerator* bazowy = new WartoscStalaGenerator(0.0);
    return new ProstokatGenerator(bazowy, amplituda, czestotliwosc, wypelnienie);
}

SygnalGenerator* InterfejsUzytkownika::stworzTrojkat()
{
    std::cout << "\n=== KONFIGURACJA SYGNALU TROJKATNEGO ===" << std::endl;
    double amplituda = pobierzLiczbe("Podaj amplitude: ");
    double okres = pobierzLiczbe("Podaj okres [s]: ");
    double wypelnienie = pobierzLiczbe("Podaj wypelnienie (0.0-1.0): ");
    
    // Sprawdzenie zakresu wypelnienia
    while (wypelnienie < 0.0 || wypelnienie > 1.0)
    {
        std::cout << "Wypelnienie musi byc w zakresie 0.0-1.0!" << std::endl;
        wypelnienie = pobierzLiczbe("Podaj wypelnienie (0.0-1.0): ");
    }
    
    // Konwersja okresu na częstotliwość
    double czestotliwosc = (okres > 0.0) ? (1.0 / okres) : 0.0;
    
    SygnalGenerator* bazowy = new WartoscStalaGenerator(0.0);
    return new TrojkatGenerator(bazowy, amplituda, czestotliwosc, wypelnienie);
}

SygnalGenerator* InterfejsUzytkownika::stworzSzumBialy()
{
    std::cout << "\n=== KONFIGURACJA SZUMU BIALEGO ===" << std::endl;
    double amplituda = pobierzLiczbe("Podaj amplitude szumu: ");
    
    SygnalGenerator* bazowy = new WartoscStalaGenerator(0.0);
    return new SzumBialyGenerator(bazowy, amplituda);
}

void InterfejsUzytkownika::dodajOgranicznikAmplitudy()
{
    std::cout << "\n=== DODAWANIE OGRANICZNIKA AMPLITUDY ===" << std::endl;
    double minAmplituda = pobierzLiczbe("Podaj minimalna amplitude: ");
    double maxAmplituda = pobierzLiczbe("Podaj maksymalna amplitude: ");
      if (minAmplituda > maxAmplituda)
    {
        std::swap(minAmplituda, maxAmplituda);
        std::cout << "Zamieniono wartosci - min: " << minAmplituda << ", max: " << maxAmplituda << std::endl;
    }
    
    // OgranicznikAmplitudy uzywa symetrycznego ograniczenia wzgledem zera
    // Obliczamy limit jako maksymalna wartosc bezwzgledna
    double limit = std::max(std::abs(minAmplituda), std::abs(maxAmplituda));
    
    // Tworzenie nowego ogranicznika jako dekoratora
    SygnalGenerator* ograniczony = new OgranicznikAmplitudy(m_generator.release(), limit);
    m_generator.reset(ograniczony);
    
    std::cout << "Ogranicznik amplitudy zostal dodany!" << std::endl;
}

void InterfejsUzytkownika::generujProbki()
{
    std::cout << "\n=== GENEROWANIE PROBEK SYGNALU ===" << std::endl;
    int liczbaProbek = pobierzLiczbeCalkowita("Podaj liczbe probek do wygenerowania: ");
    
    std::cout << "\nWygenerowane probki:" << std::endl;
    std::cout << std::fixed << std::setprecision(6);
    
    for (int i = 0; i < liczbaProbek; ++i)
    {
        double wartosc = m_generator->generuj();
        std::cout << "Probka " << std::setw(4) << (i + 1) << ": " << std::setw(12) << wartosc << std::endl;
        
        // Przerwij po 20 probkach i zapytaj czy kontynuowac
        if ((i + 1) % 20 == 0 && (i + 1) < liczbaProbek)
        {
            std::cout << "\nWyswietlono " << (i + 1) << " probek. Czy kontynuowac? (t/n): ";
            char odpowiedz;
            std::cin >> odpowiedz;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            if (odpowiedz != 't' && odpowiedz != 'T')
            {
                break;
            }
            std::cout << std::endl;
        }
    }
}

void InterfejsUzytkownika::zapiszDoPliku()
{
    std::cout << "\n=== ZAPIS SYGNALU DO PLIKU ===" << std::endl;
    std::cout << "Podaj nazwe pliku (bez rozszerzenia): ";
    std::string nazwaPliku;
    std::getline(std::cin, nazwaPliku);
    nazwaPliku += ".txt";
    
    int liczbaProbek = pobierzLiczbeCalkowita("Podaj liczbe probek do zapisania: ");
    
    std::ofstream plik(nazwaPliku);
    if (!plik.is_open())
    {
        std::cout << "Blad: Nie mozna utworzyc pliku " << nazwaPliku << std::endl;
        return;
    }
    
    plik << "# Wygenerowany sygnal - " << m_generator->getType() << std::endl;
    plik << "# Liczba probek: " << liczbaProbek << std::endl;
    plik << "# Format: numer_probki wartosc" << std::endl;
    plik << std::fixed << std::setprecision(6);
    
    std::cout << "\nWygenerowane probki (zapisywane do pliku):" << std::endl;
    std::cout << std::fixed << std::setprecision(6);
    
    for (int i = 0; i < liczbaProbek; ++i)
    {
        double wartosc = m_generator->generuj();
        plik << (i + 1) << "\t" << wartosc << std::endl;
        std::cout << "Probka " << std::setw(4) << (i + 1) << ": " << std::setw(12) << wartosc << std::endl;
        
        // Przerwij wyswietlanie po 20 probkach i zapytaj czy kontynuowac
        if ((i + 1) % 20 == 0 && (i + 1) < liczbaProbek)
        {
            std::cout << "\nWyswietlono " << (i + 1) << " probek. Czy kontynuowac wyswietlanie? (t/n): ";
            char odpowiedz;
            std::cin >> odpowiedz;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            if (odpowiedz != 't' && odpowiedz != 'T')
            {
                std::cout << "Kontynuuje zapis do pliku bez wyswietlania..." << std::endl;
                // Kontynuuj zapisywanie do pliku bez wyswietlania
                for (int j = i + 1; j < liczbaProbek; ++j)
                {
                    double wartoscBezWyswietlania = m_generator->generuj();
                    plik << (j + 1) << "\t" << wartoscBezWyswietlania << std::endl;
                }
                break;
            }
            std::cout << std::endl;
        }
    }
    
    plik.close();
    std::cout << "\nSygnal zostal zapisany do pliku: " << nazwaPliku << std::endl;
}

void InterfejsUzytkownika::wyswietlParametry()
{
    std::cout << "\n=== PARAMETRY AKTUALNEGO SYGNALU ===" << std::endl;
    std::cout << "Typ sygnalu: " << m_generator->getType() << std::endl;
    
    // Mozna by dodac wiecej szczegolow, ale wymagaloby to rozszerzenia interfejsu klas
    std::cout << "Aby zobaczyc szczegolowe parametry, mozna zapisac konfiguracje sygnalu." << std::endl;
}
