#include <iostream>
#include <memory>
#include <iomanip> // Dla std::fixed i std::setprecision
#include "Komponent.h"
#include "KompozytSzeregowy.h"
#include "KompozytRownolegl.h"
#include "KonkretnyKomponent.h"
#include "PetlaSprzezeniaZwrotnego.h" // Dodajemy nowy nagłówek

int main()
{
    std::cout << std::fixed << std::setprecision(2); // Ustawienie formatowania dla double

    std::cout << "=== Przykład użycia wzorca Kompozyt (istniejące testy) ===" << std::endl;

    auto komponent1 = std::make_shared<KonkretnyKomponent>(2.0);
    auto komponent2 = std::make_shared<KonkretnyKomponent>(3.0);
    auto komponent3 = std::make_shared<KonkretnyKomponent>(0.5);
    auto komponent4 = std::make_shared<KonkretnyKomponent>(1.5);

    std::cout << "\n1. Test kompozytu szeregowego:" << std::endl;
    auto kompozytSzeregowy = std::make_shared<KompozytSzeregowy>();
    kompozytSzeregowy->dodaj(komponent1);
    kompozytSzeregowy->dodaj(komponent2);
    kompozytSzeregowy->dodaj(komponent3);

    double wejscie = 5.0;
    double wyjscieSzeregowe = kompozytSzeregowy->symuluj(wejscie);
    std::cout << "Wejście: " << wejscie << std::endl;
    std::cout << "Wyjście (5 * 2 * 3 * 0.5): " << wyjscieSzeregowe << std::endl;

    std::cout << "\n2. Test kompozytu równoległego:" << std::endl;
    auto kompozytRownolegl = std::make_shared<KompozytRownolegl>();
    kompozytRownolegl->dodaj(komponent1);
    kompozytRownolegl->dodaj(komponent2);
    kompozytRownolegl->dodaj(komponent4);

    double wyjscieRownolegle = kompozytRownolegl->symuluj(wejscie);
    std::cout << "Wejście: " << wejscie << std::endl;
    std::cout << "Wyjście (5*2 + 5*3 + 5*1.5): " << wyjscieRownolegle << std::endl;

    std::cout << "\n3. Test kompozytu zagnieżdżonego:" << std::endl;
    auto kompozytZagniezdzony = std::make_shared<KompozytSzeregowy>();
    kompozytZagniezdzony->dodaj(komponent1);
    kompozytZagniezdzony->dodaj(kompozytRownolegl);

    double wyjscieZagniezdzony = kompozytZagniezdzony->symuluj(wejscie);
    std::cout << "Wejście: " << wejscie << std::endl;
    std::cout << "Wyjście ((5*2) -> równoległy): " << wyjscieZagniezdzony << std::endl;

    std::cout << "\n4. Test usuwania komponentu:" << std::endl;
    kompozytRownolegl->usun(komponent2);
    double wyjsciePoUsunieciu = kompozytRownolegl->symuluj(wejscie);
    std::cout << "Wejście: " << wejscie << std::endl;
    std::cout << "Wyjście po usunięciu (5*2 + 5*1.5): " << wyjsciePoUsunieciu << std::endl;

    std::cout << "\n\n=== Testy Petli Sprzezenia Zwrotnego (ze stabilnymi parametrami) ===" << std::endl;

    std::cout << "\n5. Prosta Petla Sprzezenia Zwrotnego (Stabilna):" << std::endl;
    auto petla1 = std::make_shared<PetlaSprzezeniaZwrotnego>();

    // Parametry dla stabilności: |K*H| < 1
    // K=1.0, H=0.5. K*H = 0.5. Stabilne.
    // y_ss = K*u / (1+K*H) = 1.0*u / (1 + 1.0*0.5) = u / 1.5
    double K_petla1 = 1.0;
    double H_petla1 = 0.5;
    auto sciezkaProstaPetli1 = std::make_shared<KonkretnyKomponent>(K_petla1);
    auto sciezkaSprzezeniaPetli1 = std::make_shared<KonkretnyKomponent>(H_petla1);

    petla1->ustawSciezkeProsta(sciezkaProstaPetli1);
    petla1->ustawSciezkeSprzezenia(sciezkaSprzezeniaPetli1);

    double wejsciePetli = 10.0; // u
    std::cout << "Wejście do pętli (u): " << wejsciePetli << std::endl;
    std::cout << "Parametry: K=" << K_petla1 << ", H=" << H_petla1 << std::endl;
    double oczekiwane_y_ustalone_petla1 = (K_petla1 * wejsciePetli / (1 + K_petla1 * H_petla1));
    std::cout << "Oczekiwane y_ustalone = " << oczekiwane_y_ustalone_petla1 << std::endl;

    petla1->resetuj(0.0);
    std::cout << "Symulacja krok po kroku:" << std::endl;
    for (int i = 0; i < 15; ++i) { // Zwiększono liczbę kroków dla lepszej zbieżności
        double wyjsciePetliKrok = petla1->symuluj(wejsciePetli);
        std::cout << "Krok " << i + 1 << ": y_n = " << wyjsciePetliKrok << std::endl;
    }

    std::cout << "\n6. Petla Sprzezenia Zwrotnego z Kompozytem Szeregowym (Stabilna):" << std::endl;
    auto petla2 = std::make_shared<PetlaSprzezeniaZwrotnego>(0.0);

    // K_prosta = K1*K2 = 0.5 * 0.8 = 0.4
    // H_petla2 = 0.5
    // K_prosta*H_petla2 = 0.4 * 0.5 = 0.2. Stabilne.
    // y_ss = K_prosta*u / (1+K_prosta*H) = 0.4*u / (1 + 0.4*0.5) = 0.4*u / 1.2
    double K1_petla2 = 0.5;
    double K2_petla2 = 0.8;
    double K_prosta_petla2 = K1_petla2 * K2_petla2;
    double H_petla2 = 0.5;

    auto kompozytSzeregowyPetla = std::make_shared<KompozytSzeregowy>();
    kompozytSzeregowyPetla->dodaj(std::make_shared<KonkretnyKomponent>(K1_petla2));
    kompozytSzeregowyPetla->dodaj(std::make_shared<KonkretnyKomponent>(K2_petla2));

    petla2->ustawSciezkeProsta(kompozytSzeregowyPetla);
    petla2->ustawSciezkeSprzezenia(std::make_shared<KonkretnyKomponent>(H_petla2));

    std::cout << "Wejście do pętli 2 (u): " << wejsciePetli << std::endl;
    std::cout << "Parametry: K_prosta=" << K_prosta_petla2 << " (K1=" << K1_petla2 << ", K2=" << K2_petla2 << "), H=" << H_petla2 << std::endl;
    double oczekiwane_y_ustalone_petla2 = (K_prosta_petla2 * wejsciePetli / (1 + K_prosta_petla2 * H_petla2));
    std::cout << "Oczekiwane y_ustalone = " << oczekiwane_y_ustalone_petla2 << std::endl;

    petla2->resetuj(0.0);
    std::cout << "Symulacja krok po kroku:" << std::endl;
    for (int i = 0; i < 20; ++i) { // Więcej kroków dla zbieżności
        double wyjsciePetliKrok = petla2->symuluj(wejsciePetli);
        std::cout << "Krok " << i + 1 << ": y_n = " << wyjsciePetliKrok << std::endl;
    }

    std::cout << "\n7. Zagnieżdżenie Petli1 (teraz stabilnej K="<< K_petla1 <<", H="<< H_petla1 <<") w Kompozycie Szeregowym:" << std::endl;
    // petla1 jest już skonfigurowana (K=1.0, H=0.5). Jej y_ss dla u_petli=10 to 6.67.
    // K_przed = 0.5. K_za = 1.2.

    auto kompozytZawierajacyPetle = std::make_shared<KompozytSzeregowy>();
    double K_przed_petla_zagn = 0.5;
    double K_za_petla_zagn = 1.2;
    auto wzmocnieniePrzedPetla = std::make_shared<KonkretnyKomponent>(K_przed_petla_zagn);
    kompozytZawierajacyPetle->dodaj(wzmocnieniePrzedPetla);
    kompozytZawierajacyPetle->dodaj(petla1); // petla1 (K=1.0, H=0.5)
    auto wzmocnienieZaPetla = std::make_shared<KonkretnyKomponent>(K_za_petla_zagn);
    kompozytZawierajacyPetle->dodaj(wzmocnienieZaPetla);

    double wejscieGlowne = 20.0;
    // u_petli = wejscieGlowne * K_przed = 20.0 * 0.5 = 10.0.
    // y_petli_ss dla u_petli=10 (z petla1) to 6.67.
    // y_calkowite_ss = y_petli_ss * K_za = 6.67 * 1.2 = 8.00.

    petla1->resetuj(0.0);

    std::cout << "Wejście główne do kompozytu: " << wejscieGlowne << std::endl;
    double u_petli_dla_kompozytu = wejscieGlowne * K_przed_petla_zagn; // =10.0
    // oczekiwane_y_ustalone_petla1 było liczone dla wejsciePetli=10.0, co jest równe u_petli_dla_kompozytu
    double oczekiwane_y_calkowite = oczekiwane_y_ustalone_petla1 * K_za_petla_zagn;
    std::cout << "Oczekiwane y_ustalone calkowite = " << oczekiwane_y_calkowite << std::endl;
    std::cout << "(Pętla wewnętrzna powinna stabilizować się na y_petli=" << oczekiwane_y_ustalone_petla1 << ")" << std::endl;

    std::cout << "Symulacja kompozytu zagnieżdżającego pętlę (krok po kroku):" << std::endl;
    for (int i = 0; i < 20; ++i) {
        double wyjscieZagn = kompozytZawierajacyPetle->symuluj(wejscieGlowne);
         std::cout << "Krok " << i + 1 << ": Wyjście kompozytu = " << wyjscieZagn
                  << " (wew. y_petli1 = " << petla1->pobierzPoprzednieWyjscie() << ")" << std::endl;
    }

    std::cout << "\n8. Test Petli bez sciezki sprzezenia (powinna dzialac jak sciezka prosta):" << std::endl;
    auto petlaBezSprzezenia = std::make_shared<PetlaSprzezeniaZwrotnego>();
    auto k_prosta_test8 = std::make_shared<KonkretnyKomponent>(5.0);
    petlaBezSprzezenia->ustawSciezkeProsta(k_prosta_test8);
    petlaBezSprzezenia->resetuj(0.0);
    double wejscieDoProstej = 4.0;
    double wyjscieProstej = petlaBezSprzezenia->symuluj(wejscieDoProstej);
    std::cout << "Wejscie: " << wejscieDoProstej << ", Wyjscie petli bez sprzezenia (K=5): " << wyjscieProstej
              << " (Oczekiwane: " << (4.0 * 5.0) << ")" << std::endl;

    std::cout << "\n9. Test Petli bez sciezki prostej (ale ze sprzezeniem - uchyb jako wyjscie):" << std::endl;
    auto petlaBezProstej = std::make_shared<PetlaSprzezeniaZwrotnego>();
    auto h_test9 = std::make_shared<KonkretnyKomponent>(1.0);
    petlaBezProstej->ustawSciezkeSprzezenia(h_test9);
    double y_prev_test9 = 10.0;
    petlaBezProstej->resetuj(y_prev_test9);
    double wejscieDoBezProstej = 15.0;
    double oczekiwane_test9 = wejscieDoBezProstej - 1.0 * y_prev_test9;
    double wyjscieBezProstej = petlaBezProstej->symuluj(wejscieDoBezProstej); // y_n = u - H*y_{n-1}
    std::cout << "Wejscie: " << wejscieDoBezProstej << ", y_prev (na starcie kroku)="<< y_prev_test9 <<", H=1."<<std::endl;
    std::cout << "Wyjscie petli (uchyb): " << wyjscieBezProstej
              << " (Oczekiwane: " << oczekiwane_test9 << ")" << std::endl;
    std::cout << "Nowe poprzednieWyjsciePetli (po kroku): " << petlaBezProstej->pobierzPoprzednieWyjscie()
              << " (Oczekiwane: " << oczekiwane_test9 << ")" << std::endl;

    std::cout << "\n10. Test Petli bez zadnych sciezek (powinna dzialac jak przekaznik u->y):" << std::endl;
    auto petlaPusta = std::make_shared<PetlaSprzezeniaZwrotnego>();
    double y_prev_test10 = 5.0;
    petlaPusta->resetuj(y_prev_test10);
    double wejscieDoPustej = 25.0;
    double wyjsciePustej = petlaPusta->symuluj(wejscieDoPustej); // y_n = u
    std::cout << "Wejscie: " << wejscieDoPustej << ", y_prev (na starcie kroku)=" << y_prev_test10 <<"."<<std::endl;
    std::cout << "Wyjscie petli pustej: " << wyjsciePustej
              << " (Oczekiwane: " << wejscieDoPustej << ")" << std::endl;
    std::cout << "Nowe poprzednieWyjsciePetli (po kroku): " << petlaPusta->pobierzPoprzednieWyjscie()
              << " (Oczekiwane: " << wejscieDoPustej << ")" << std::endl;

    return 0;
}
