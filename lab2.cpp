#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <string>	 // For FabrykaSygnalu error
#include <stdexcept> // For FabrykaSygnalu error
#include <limits>	 // Required for std::numeric_limits

#include "RegulatorPID.h"
#include "ModelARX.h"
#include "KrokPetliSprzezeniaZwrotnego.h"
#include "SygnalGenerator.h"
#include "WartoscStalaGenerator.h"
#include "SygnalDekorator.h"
#include "SinusGenerator.h"
#include "ProstokatGenerator.h"
#include "TrojkatGenerator.h"
#include "SzumBialyGenerator.h"
#include "OgranicznikAmplitudy.h"
#include "FabrykaSygnalu.h" // For deserialization test

#ifdef DEBUG

// Funkcje pomocnicze dla testów:

void raportBleduSekwencji(std::vector<double> &spodz, std::vector<double> &fakt)
{
	constexpr size_t PREC = 3;
	std::cerr << std::fixed << std::setprecision(PREC);
	std::cerr << "  Spodziewany:\t";
	for (auto &el : spodz)
		std::cerr << el << ", ";
	std::cerr << "\n  Faktyczny:\t";
	for (auto &el : fakt)
		std::cerr << el << ", ";
	std::cerr << std::endl
			  << std::endl;
}

bool porownanieSekwencji(std::vector<double> &spodz, std::vector<double> &fakt)
{
	constexpr double TOL = 1e-3; // tolerancja dla porównań zmiennoprzecinkowych
	bool result = fakt.size() == spodz.size();
	for (size_t i = 0; result && i < fakt.size(); i++)
		result = fabs(fakt[i] - spodz[i]) < TOL;
	return result;
}

void test_RegulatorP_brakPobudzenia()
{
	// Sygnatura testu:
	std::cerr << "RegP (k = 0.5) -> test zerowego pobudzenia: ";
	try
	{
		// Przygotowanie danych:
		RegulatorPID instancjaTestowa(0.5);
		constexpr size_t LICZ_ITER = 30;
		std::vector<double> sygWe(LICZ_ITER);	   // pobudzenie modelu (tu same 0)
		std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy (tu same 0)
		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

		// Symulacja modelu:

		for (size_t i = 0; i < LICZ_ITER; i++)
			faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

		// Walidacja poprawności i raport:
		if (porownanieSekwencji(spodzSygWy, faktSygWy))
			std::cerr << "OK!\n";
		else
		{
			std::cerr << "FAIL!\n";
			raportBleduSekwencji(spodzSygWy, faktSygWy);
		}
	}
	catch (...)
	{
		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
	}
}

void test_RegulatorP_skokJednostkowy()
{
	// Sygnatura testu:
	std::cerr << "RegP (k = 0.5) -> test skoku jednostkowego: ";

	try
	{
		// Przygotowanie danych:
		RegulatorPID instancjaTestowa(0.5);
		constexpr size_t LICZ_ITER = 30;
		std::vector<double> sygWe(LICZ_ITER);	   // pobudzenie modelu
		std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy
		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

		// Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
		for (size_t i = 0; i < LICZ_ITER; i++)
			sygWe[i] = !!i;
		spodzSygWy = {0.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};

		// Symulacja modelu:
		for (size_t i = 0; i < LICZ_ITER; i++)
			faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

		// Walidacja poprawności i raport:
		if (porownanieSekwencji(spodzSygWy, faktSygWy))
			std::cerr << "OK!\n";
		else
		{
			std::cerr << "FAIL!\n";
			raportBleduSekwencji(spodzSygWy, faktSygWy);
		}
	}
	catch (...)
	{
		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
	}
}

void test_RegulatorPI_skokJednostkowy_1()
{
	// Sygnatura testu:
	std::cerr << "RegPI (k = 0.5, TI = 1.0) -> test skoku jednostkowego nr 1: ";

	try
	{
		// Przygotowanie danych:
		RegulatorPID instancjaTestowa(0.5, 1.0);
		constexpr size_t LICZ_ITER = 30;
		std::vector<double> sygWe(LICZ_ITER);	   // pobudzenie modelu
		std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy
		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

		// Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
		for (size_t i = 0; i < LICZ_ITER; i++)
			sygWe[i] = !!i;
		spodzSygWy = {0, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 16.5, 17.5, 18.5, 19.5, 20.5, 21.5, 22.5, 23.5, 24.5, 25.5, 26.5, 27.5, 28.5, 29.5};

		// Symulacja modelu:
		for (size_t i = 0; i < LICZ_ITER; i++)
			faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

		// Walidacja poprawności i raport:
		if (porownanieSekwencji(spodzSygWy, faktSygWy))
			std::cerr << "OK!\n";
		else
		{
			std::cerr << "FAIL!\n";
			raportBleduSekwencji(spodzSygWy, faktSygWy);
		}
	}
	catch (...)
	{
		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
	}
}

void test_RegulatorPI_skokJednostkowy_2()
{
	// Sygnatura testu:
	std::cerr << "RegPI (k = 0.5, TI = 10.0) -> test skoku jednostkowego nr 2: ";

	try
	{
		// Przygotowanie danych:
		RegulatorPID instancjaTestowa(0.5, 10.0);
		constexpr size_t LICZ_ITER = 30;
		std::vector<double> sygWe(LICZ_ITER);	   // pobudzenie modelu
		std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy
		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

		// Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
		for (size_t i = 0; i < LICZ_ITER; i++)
			sygWe[i] = !!i;
		spodzSygWy = {0, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3, 3.1, 3.2, 3.3, 3.4};

		// Symulacja modelu:
		for (size_t i = 0; i < LICZ_ITER; i++)
			faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

		// Walidacja poprawności i raport:
		if (porownanieSekwencji(spodzSygWy, faktSygWy))
			std::cerr << "OK!\n";
		else
		{
			std::cerr << "FAIL!\n";
			raportBleduSekwencji(spodzSygWy, faktSygWy);
		}
	}
	catch (...)
	{
		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
	}
}

void test_RegulatorPID_skokJednostkowy()
{
	// Sygnatura testu:
	std::cerr << "RegPID (k = 0.5, TI = 10.0, TD = 0.2) -> test skoku jednostkowego: ";

	try
	{
		// Przygotowanie danych:
		RegulatorPID instancjaTestowa(0.5, 10.0, 0.2);
		constexpr size_t LICZ_ITER = 30;
		std::vector<double> sygWe(LICZ_ITER);	   // pobudzenie modelu
		std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy
		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

		// Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
		for (size_t i = 0; i < LICZ_ITER; i++)
			sygWe[i] = !!i;
		spodzSygWy = {0, 0.8, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3, 3.1, 3.2, 3.3, 3.4};

		// Symulacja modelu:
		for (size_t i = 0; i < LICZ_ITER; i++)
			faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

		// Walidacja poprawności i raport:
		if (porownanieSekwencji(spodzSygWy, faktSygWy))
			std::cerr << "OK!\n";
		else
		{
			std::cerr << "FAIL!\n";
			raportBleduSekwencji(spodzSygWy, faktSygWy);
		}
	}
	catch (...)
	{
		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
	}
}
void test_Petli() // Changed name slightly to avoid potential issues with special chars
{
	std::cerr << "\n--- Test Petli Sprzezenia Zwrotnego ---\n";
	std::cerr << std::fixed << std::setprecision(5); // Set precision for output

	try
	{
		// 1. Parametry i instancje obiektów
		// ModelARX
		std::vector<double> a = {-0.6, 0.1};
		std::vector<double> b = {0.5, 0.2};
		unsigned int delay = 1;
		double sigma = 0.0;

		ModelARX model(a, b, delay, sigma);

		// RegulatorPID (przykładowe nastawy)
		double k_p = 0.8;
		double Ti = 5.0;
		double Td = 0.1;
		RegulatorPID regulator(k_p, Ti, Td);

		// Funktor kroku pętli
		KrokPetliSprzezeniaZwrotnego krok;

		// 2. Symulacja pętli
		double poprzednieWyjscie = 0.0;	 // Początkowa wartość wyjścia obiektu
		constexpr int liczbaKrokow = 50; // Liczba kroków symulacji

		std::cout << "Symulacja petli sprzezenia zwrotnego (wartosc zadana = 1.0):\n";
		std::cout << "Krok\tWyjscie Obiektu (y)\n";
		std::cout << "----\t--------------------\n";
		std::cout << -1 << "\t" << poprzednieWyjscie << " (stan poczatkowy)\n"; // Show initial state

		for (int i = 0; i < liczbaKrokow; ++i)
		{
			// Wykonaj jeden krok pętli używając funktora
			double aktualneWyjscie = krok(regulator, model, poprzednieWyjscie);

			// Zapisz/Wyświetl wynik
			std::cout << i << "\t" << aktualneWyjscie << std::endl;

			// Zaktualizuj stan na następną iterację
			poprzednieWyjscie = aktualneWyjscie;
		}
		std::cerr << "--- Koniec Testu Petli ---\n";
	}
	catch (const std::exception &e) // Catch standard exceptions
	{
		std::cerr << "TEST PETLI PRZERWANY! (" << e.what() << ")\n";
	}
	catch (...)
	{
		std::cerr << "TEST PETLI PRZERWANY!\n";
	}
	std::cerr << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield); // Reset precision formatting
}

// --- Nowe funkcje testowe dla generatora sygnałów ---

void test_GeneratorSygnalow_Symulacja()
{
	std::cerr << "\n--- Test Generatora Sygnałów w Pętli Regulacji --- \n";
	std::cerr << std::fixed << std::setprecision(5);

	SygnalGenerator *sygnalWartosciZadanej = nullptr;
	try
	{
		// 1. Tworzenie złożonego generatora sygnału wartości zadanej
		sygnalWartosciZadanej = new OgranicznikAmplitudy(
			new SzumBialyGenerator(
				new TrojkatGenerator(
					new ProstokatGenerator(
						new SinusGenerator(
							new WartoscStalaGenerator(0.0), // stala
							4.0, 0.05),						// Sinus (amp, freq)
						3.0, 0.05, 0.5),					// Prostokat (amp, freq, fill)
					3.0, 0.05, 0.5),						// Trojkat (amp, freq, fill=0.5)
				1.0),										// Szum (amp)
			10.0);											// Ogranicznik (limit)

		std::cout << "Złożony generator sygnału wartości zadanej został utworzony." << std::endl;

		// 2. Parametry i instancje obiektów pętli regulacji
		// ModelARX
		std::vector<double> a = {-0.6, 0.1};
		std::vector<double> b = {0.5, 0.2};
		unsigned int delay = 1;
		double sigma = 0.0; // Szum procesowy, tu zakładamy brak
		ModelARX model(a, b, delay, sigma);

		// RegulatorPID
		double k_p = 0.8;
		double Ti = 5.0;
		double Td = 0.1;
		RegulatorPID regulator(k_p, Ti, Td);

		// 3. Symulacja pętli z użyciem generatora
		double poprzednieWyjscieObiektu = 0.0;
		constexpr int liczbaKrokow = 100; // Zwiększona liczba kroków dla lepszej obserwacji

		std::cout << "\nSymulacja pętli sprzężenia zwrotnego z generatorem wartości zadanej:\n";
		std::cout << "Krok\tWartoscZadana\tWyjscieObiektu(y)\tUchyb\tSterowanie\n";
		std::cout << "----\t-------------\t-------------------\t-----\t----------\n";
		std::cout << -1 << "\t" << "N/A" << "\t" << poprzednieWyjscieObiektu << " (stan pocz.)" << "\tN/A\tN/A\n";

		for (int i = 0; i < liczbaKrokow; ++i)
		{
			double wartoscZadana = sygnalWartosciZadanej->generuj();
			double uchyb = wartoscZadana - poprzednieWyjscieObiektu;
			double sterowanie = regulator.symuluj(uchyb);
			double aktualneWyjscieObiektu = model.symuluj(sterowanie);

			std::cout << i << "\t"
					  << wartoscZadana << "\t"
					  << aktualneWyjscieObiektu << "\t"
					  << uchyb << "\t"
					  << sterowanie << std::endl;

			poprzednieWyjscieObiektu = aktualneWyjscieObiektu;
		}
		std::cerr << "--- Koniec Testu Generatora Sygnałów w Pętli --- \n";
	}
	catch (const std::exception &e)
	{
		std::cerr << "TEST GENERATORA SYGNAŁÓW (SYMULACJA) PRZERWANY! (" << e.what() << ")\n";
	}
	catch (...)
	{
		std::cerr << "TEST GENERATORA SYGNAŁÓW (SYMULACJA) PRZERWANY! (Nieznany wyjątek)\n";
	}

	delete sygnalWartosciZadanej; // Zwolnienie pamięci
	std::cerr << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
}

void test_GeneratorSygnalow_Serializacja()
{
	std::cerr << "\n--- Test Serializacji i Deserializacji Generatora Sygnałów --- \n";
	std::cerr << std::fixed << std::setprecision(5);
	const char *nazwaPliku = "generator_stan.txt";

	SygnalGenerator *genOrg = nullptr;
	SygnalGenerator *genWczytany = nullptr;

	try
	{
		// 1. Utwórz oryginalny generator (może być ten złożony lub prostszy dla testu)
		genOrg = new OgranicznikAmplitudy(
			new SzumBialyGenerator(
				new TrojkatGenerator(
					new ProstokatGenerator(
						new SinusGenerator(
							new WartoscStalaGenerator(0.123), // stala
							1.5, 0.2),						  // Sinus (amp, freq)
						0.8, 0.1, 0.3),						  // Prostokat (amp, freq, fill)
					1.2, 0.08, 0.6),						  // Trojkat (amp, freq, fill=0.5)
				0.25),										  // Szum (amp)
			5.0);

		std::cout << "Oryginalny generator (przed serializacją):" << std::endl;
		for (int k = 0; k < 3; ++k)
			std::cout << "  GenOrg[" << k << "]: " << genOrg->generuj() << std::endl;

		// 2. Serializuj do pliku
		std::ofstream ofs(nazwaPliku);
		if (!ofs.is_open())
		{
			throw std::runtime_error("Nie można otworzyć pliku do zapisu: " + std::string(nazwaPliku));
		}
		genOrg->zapisz(ofs);
		ofs.close();
		std::cout << "Generator zserializowany do pliku: " << nazwaPliku << std::endl;

		// Resetuj stan oryginalnego generatora (lub użyj innego) by pokazać, że wczytany jest niezależny
		// Dla tego testu, po prostu wygenerujemy więcej wartości z oryginalnego, aby jego stan się zmienił
		// zanim wczytamy nowy.
		std::cout << "Oryginalny generator (po serializacji, przed usunięciem):" << std::endl;
		for (int k = 0; k < 2; ++k)
			std::cout << "  GenOrg[" << k + 3 << "]: " << genOrg->generuj() << std::endl;

		// 3. Deserializuj z pliku
		std::ifstream ifs(nazwaPliku);
		if (!ifs.is_open())
		{
			throw std::runtime_error("Nie można otworzyć pliku do odczytu: " + std::string(nazwaPliku));
		}
		genWczytany = FabrykaSygnalu::wczytaj(ifs);
		ifs.close();
		if (!genWczytany)
		{
			throw std::runtime_error("Deserializacja zwróciła nullptr.");
		}
		std::cout << "Generator zdeserializowany z pliku: " << nazwaPliku << std::endl;

		// 4. Porównaj (generując wartości)
		// Wartości powinny być takie same jak pierwsze wartości z genOrg,
		// jeśli stan wewnętrzny (np. czas, x1,x2 dla sinusa) jest poprawnie zapisywany i odczytywany.
		std::cout << "Wczytany generator (po deserializacji):" << std::endl;
		for (int k = 0; k < 3; ++k)
		{ // Generujemy tyle samo wartości co na początku z genOrg
			std::cout << "  GenWczytany[" << k << "]: " << genWczytany->generuj() << std::endl;
		}
		std::cerr << "--- Koniec Testu Serializacji --- \n";
	}
	catch (const std::exception &e)
	{
		std::cerr << "TEST GENERATORA SYGNAŁÓW (SERIALIZACJA) PRZERWANY! (" << e.what() << ")\n";
	}
	catch (...)
	{
		std::cerr << "TEST GENERATORA SYGNAŁÓW (SERIALIZACJA) PRZERWANY! (Nieznany wyjątek)\n";
	}

	delete genOrg;
	delete genWczytany;
	std::cerr << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
}

using namespace std;

int main()
{
	test_RegulatorP_brakPobudzenia();
	test_RegulatorP_skokJednostkowy();
	test_RegulatorPI_skokJednostkowy_1();
	test_RegulatorPI_skokJednostkowy_2();
	test_RegulatorPID_skokJednostkowy();
	test_Petli();

	// Wywołanie nowych testów
	test_GeneratorSygnalow_Symulacja();
	test_GeneratorSygnalow_Serializacja();

	std::cout << "\nNaciśnij Enter, aby zakończyć..." << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return 0;
}

#endif

#ifdef MAIN

using namespace std;

int main()
{
}
#endif
