#include "InterfejsUzytkownika.h"
#include <limits>
#include <fstream>
#include <cmath>
#include <iomanip>

InterfejsUzytkownika::InterfejsUzytkownika() : m_generator(nullptr) {}

InterfejsUzytkownika::~InterfejsUzytkownika() {}

void InterfejsUzytkownika::uruchom()
{
    std::cout << "=== GENERATOR SYGNAŁÓW - INTERFEJS UŻYTKOWNIKA ===" << std::endl;
    std::cout << "Witaj w interaktywnym generatorze sygnałów!" << std::endl << std::endl;
    
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
                    std::cout << "Najpierw wybierz sygnał!" << std::endl;
                break;
            case 3:
                if (m_generator)
                    generujProbki();
                else
                    std::cout << "Najpierw wybierz sygnał!" << std::endl;
                break;
            case 4:
                if (m_generator)
                    zapiszDoPliku();
                else
                    std::cout << "Najpierw wybierz sygnał!" << std::endl;
                break;
            case 5:
                if (m_generator)
                    wyswietlParametry();
                else
                    std::cout << "Brak aktywnego sygnału." << std::endl;
                break;
            case 6:
                kontynuuj = false;
                std::cout << "Dziękuję za korzystanie z programu!" << std::endl;
                break;
        }
        std::cout << std::endl;
    }
}

void InterfejsUzytkownika::wyswietlMenu()
{
    std::cout << "=== MENU GŁÓWNE ===" << std::endl;
    std::cout << "1. Wybierz typ sygnału" << std::endl;
    std::cout << "2. Dodaj ogranicznik amplitudy" << std::endl;
    std::cout << "3. Generuj próbki sygnału" << std::endl;
    std::cout << "4. Zapisz sygnał do pliku" << std::endl;
    std::cout << "5. Wyświetl parametry aktualnego sygnału" << std::endl;
    std::cout << "6. Wyjście" << std::endl;
    std::cout << "Wybierz opcję (1-6): ";
}

void InterfejsUzytkownika::wyswietlMenuSygnalow()
{
    std::cout << "\n=== WYBÓR TYPU SYGNAŁU ===" << std::endl;
    std::cout << "1. Wartość stała" << std::endl;
    std::cout << "2. Sygnał sinusoidalny" << std::endl;
    std::cout << "3. Sygnał prostokątny" << std::endl;
    std::cout << "4. Sygnał trójkątny" << std::endl;
    std::cout << "5. Szum biały" << std::endl;
    std::cout << "Wybierz typ sygnału (1-5): ";
    
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
        std::cout << "Sygnał został utworzony pomyślnie!" << std::endl;
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
            std::cout << "Nieprawidłowy wybór. Podaj liczbę z zakresu " << min << "-" << max << ": ";
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
            std::cout << "Nieprawidłowa wartość. Podaj liczbę: ";
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
            std::cout << "Nieprawidłowa wartość. Podaj liczbę całkowitą większą od 0: ";
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
    std::cout << "\n=== KONFIGURACJA WARTOŚCI STAŁEJ ===" << std::endl;
    double wartosc = pobierzLiczbe("Podaj wartość stałą: ");
    
    return new WartoscStalaGenerator(wartosc);
}

SygnalGenerator* InterfejsUzytkownika::stworzSinus()
{
    std::cout << "\n=== KONFIGURACJA SYGNAŁU SINUSOIDALNEGO ===" << std::endl;
    double amplituda = pobierzLiczbe("Podaj amplitudę: ");
    double czestotliwosc = pobierzLiczbe("Podaj częstotliwość [Hz]: ");
    
    // Sinus jest dekoratorem, więc potrzebuje sygnału bazowego (wartość stała = 0)
    SygnalGenerator* bazowy = new WartoscStalaGenerator(0.0);
    return new SinusGenerator(bazowy, amplituda, czestotliwosc);
}

SygnalGenerator* InterfejsUzytkownika::stworzProstokat()
{
    std::cout << "\n=== KONFIGURACJA SYGNAŁU PROSTOKĄTNEGO ===" << std::endl;
    double amplituda = pobierzLiczbe("Podaj amplitudę: ");
    double okres = pobierzLiczbe("Podaj okres [s]: ");
    double wypelnienie = pobierzLiczbe("Podaj wypełnienie (0.0-1.0): ");
    
    // Sprawdzenie zakresu wypełnienia
    while (wypelnienie < 0.0 || wypelnienie > 1.0)
    {
        std::cout << "Wypełnienie musi być w zakresie 0.0-1.0!" << std::endl;
        wypelnienie = pobierzLiczbe("Podaj wypełnienie (0.0-1.0): ");
    }
    
    // Konwersja okresu na częstotliwość
    double czestotliwosc = (okres > 0.0) ? (1.0 / okres) : 0.0;
    
    SygnalGenerator* bazowy = new WartoscStalaGenerator(0.0);
    return new ProstokatGenerator(bazowy, amplituda, czestotliwosc, wypelnienie);
}

SygnalGenerator* InterfejsUzytkownika::stworzTrojkat()
{
    std::cout << "\n=== KONFIGURACJA SYGNAŁU TRÓJKĄTNEGO ===" << std::endl;
    double amplituda = pobierzLiczbe("Podaj amplitudę: ");
    double okres = pobierzLiczbe("Podaj okres [s]: ");
    double wypelnienie = pobierzLiczbe("Podaj wypełnienie (0.0-1.0): ");
    
    // Sprawdzenie zakresu wypełnienia
    while (wypelnienie < 0.0 || wypelnienie > 1.0)
    {
        std::cout << "Wypełnienie musi być w zakresie 0.0-1.0!" << std::endl;
        wypelnienie = pobierzLiczbe("Podaj wypełnienie (0.0-1.0): ");
    }
    
    // Konwersja okresu na częstotliwość
    double czestotliwosc = (okres > 0.0) ? (1.0 / okres) : 0.0;
    
    SygnalGenerator* bazowy = new WartoscStalaGenerator(0.0);
    return new TrojkatGenerator(bazowy, amplituda, czestotliwosc, wypelnienie);
}

SygnalGenerator* InterfejsUzytkownika::stworzSzumBialy()
{
    std::cout << "\n=== KONFIGURACJA SZUMU BIAŁEGO ===" << std::endl;
    double amplituda = pobierzLiczbe("Podaj amplitudę szumu: ");
    
    SygnalGenerator* bazowy = new WartoscStalaGenerator(0.0);
    return new SzumBialyGenerator(bazowy, amplituda);
}

void InterfejsUzytkownika::dodajOgranicznikAmplitudy()
{
    std::cout << "\n=== DODAWANIE OGRANICZNIKA AMPLITUDY ===" << std::endl;
    double minAmplituda = pobierzLiczbe("Podaj minimalną amplitudę: ");
    double maxAmplituda = pobierzLiczbe("Podaj maksymalną amplitudę: ");
      if (minAmplituda > maxAmplituda)
    {
        std::swap(minAmplituda, maxAmplituda);
        std::cout << "Zamieniono wartości - min: " << minAmplituda << ", max: " << maxAmplituda << std::endl;
    }
    
    // OgranicznikAmplitudy używa symetrycznego ograniczenia względem zera
    // Obliczamy limit jako maksymalną wartość bezwzględną
    double limit = std::max(std::abs(minAmplituda), std::abs(maxAmplituda));
    
    // Tworzenie nowego ogranicznika jako dekoratora
    SygnalGenerator* ograniczony = new OgranicznikAmplitudy(m_generator.release(), limit);
    m_generator.reset(ograniczony);
    
    std::cout << "Ogranicznik amplitudy został dodany!" << std::endl;
}

void InterfejsUzytkownika::generujProbki()
{
    std::cout << "\n=== GENEROWANIE PRÓBEK SYGNAŁU ===" << std::endl;
    int liczbaProbek = pobierzLiczbeCalkowita("Podaj liczbę próbek do wygenerowania: ");
    
    std::cout << "\nWygenerowane próbki:" << std::endl;
    std::cout << std::fixed << std::setprecision(6);
    
    for (int i = 0; i < liczbaProbek; ++i)
    {
        double wartosc = m_generator->generuj();
        std::cout << "Próbka " << std::setw(4) << (i + 1) << ": " << std::setw(12) << wartosc << std::endl;
        
        // Przerwij po 20 próbkach i zapytaj czy kontynuować
        if ((i + 1) % 20 == 0 && (i + 1) < liczbaProbek)
        {
            std::cout << "\nWyświetlono " << (i + 1) << " próbek. Czy kontynuować? (t/n): ";
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
    std::cout << "\n=== ZAPIS SYGNAŁU DO PLIKU ===" << std::endl;
    std::cout << "Podaj nazwę pliku (bez rozszerzenia): ";
    std::string nazwaPliku;
    std::getline(std::cin, nazwaPliku);
    nazwaPliku += ".txt";
    
    int liczbaProbek = pobierzLiczbeCalkowita("Podaj liczbę próbek do zapisania: ");
    
    std::ofstream plik(nazwaPliku);
    if (!plik.is_open())
    {
        std::cout << "Błąd: Nie można utworzyć pliku " << nazwaPliku << std::endl;
        return;
    }
    
    plik << "# Wygenerowany sygnał - " << m_generator->getType() << std::endl;
    plik << "# Liczba próbek: " << liczbaProbek << std::endl;
    plik << "# Format: numer_probki wartosc" << std::endl;
    plik << std::fixed << std::setprecision(6);
    
    std::cout << "\nWygenerowane próbki (zapisywane do pliku):" << std::endl;
    std::cout << std::fixed << std::setprecision(6);
    
    for (int i = 0; i < liczbaProbek; ++i)
    {
        double wartosc = m_generator->generuj();
        plik << (i + 1) << "\t" << wartosc << std::endl;
        std::cout << "Próbka " << std::setw(4) << (i + 1) << ": " << std::setw(12) << wartosc << std::endl;
        
        // Przerwij wyświetlanie po 20 próbkach i zapytaj czy kontynuować
        if ((i + 1) % 20 == 0 && (i + 1) < liczbaProbek)
        {
            std::cout << "\nWyświetlono " << (i + 1) << " próbek. Czy kontynuować wyświetlanie? (t/n): ";
            char odpowiedz;
            std::cin >> odpowiedz;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            if (odpowiedz != 't' && odpowiedz != 'T')
            {
                std::cout << "Kontynuuję zapis do pliku bez wyświetlania..." << std::endl;
                // Kontynuuj zapisywanie do pliku bez wyświetlania
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
    std::cout << "\nSygnał został zapisany do pliku: " << nazwaPliku << std::endl;
}

void InterfejsUzytkownika::wyswietlParametry()
{
    std::cout << "\n=== PARAMETRY AKTUALNEGO SYGNAŁU ===" << std::endl;
    std::cout << "Typ sygnału: " << m_generator->getType() << std::endl;
    
    // Można by dodać więcej szczegółów, ale wymagałoby to rozszerzenia interfejsu klas
    std::cout << "Aby zobaczyć szczegółowe parametry, można zapisać konfigurację sygnału." << std::endl;
}
