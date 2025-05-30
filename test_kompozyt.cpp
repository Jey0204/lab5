#include <iostream>
#include <memory>
#include "Komponent.h"
#include "KompozytSzeregowy.h"
#include "KompozytRownolegl.h"
#include "KonkretnyKomponent.h"

int main()
{
    std::cout << "=== Przykład użycia wzorca Kompozyt ===" << std::endl;
    
    // Tworzenie konkretnych komponentów
    auto komponent1 = std::make_shared<KonkretnyKomponent>(2.0);  // Mnoży przez 2
    auto komponent2 = std::make_shared<KonkretnyKomponent>(3.0);  // Mnoży przez 3
    auto komponent3 = std::make_shared<KonkretnyKomponent>(0.5);  // Mnoży przez 0.5
    auto komponent4 = std::make_shared<KonkretnyKomponent>(1.5);  // Mnoży przez 1.5
    
    std::cout << "\n1. Test kompozytu szeregowego:" << std::endl;
    // Tworzenie kompozytu szeregowego
    auto kompozytSzeregowy = std::make_shared<KompozytSzeregowy>();
    kompozytSzeregowy->dodaj(komponent1);  // * 2.0
    kompozytSzeregowy->dodaj(komponent2);  // * 3.0
    kompozytSzeregowy->dodaj(komponent3);  // * 0.5
    
    double wejscie = 5.0;
    double wyjscieSzeregowe = kompozytSzeregowy->symuluj(wejscie);
    std::cout << "Wejście: " << wejscie << std::endl;
    std::cout << "Wyjście (5 * 2 * 3 * 0.5): " << wyjscieSzeregowe << std::endl;
    
    std::cout << "\n2. Test kompozytu równoległego:" << std::endl;
    // Tworzenie kompozytu równoległego
    auto kompozytRownolegl = std::make_shared<KompozytRownolegl>();
    kompozytRownolegl->dodaj(komponent1);  // * 2.0
    kompozytRownolegl->dodaj(komponent2);  // * 3.0
    kompozytRownolegl->dodaj(komponent4);  // * 1.5
    
    double wyjscieRownolegle = kompozytRownolegl->symuluj(wejscie);
    std::cout << "Wejście: " << wejscie << std::endl;
    std::cout << "Wyjście (5*2 + 5*3 + 5*1.5): " << wyjscieRownolegle << std::endl;
    
    std::cout << "\n3. Test kompozytu zagnieżdżonego:" << std::endl;
    // Tworzenie zagnieżdżonego kompozytu (szeregowy zawierający równoległy)
    auto kompozytZagniezdzony = std::make_shared<KompozytSzeregowy>();
    kompozytZagniezdzony->dodaj(komponent1);           // Najpierw * 2.0
    kompozytZagniezdzony->dodaj(kompozytRownolegl);    // Potem kompozyt równoległy
    
    double wyjscieZagniezdzony = kompozytZagniezdzony->symuluj(wejscie);
    std::cout << "Wejście: " << wejscie << std::endl;
    std::cout << "Wyjście ((5*2) -> równoległy): " << wyjscieZagniezdzony << std::endl;
    
    std::cout << "\n4. Test usuwania komponentu:" << std::endl;
    kompozytRownolegl->usun(komponent2);  // Usuwamy komponent2 (współczynnik 3.0)
    double wyjsciePoUsunieciu = kompozytRownolegl->symuluj(wejscie);
    std::cout << "Wejście: " << wejscie << std::endl;
    std::cout << "Wyjście po usunięciu (5*2 + 5*1.5): " << wyjsciePoUsunieciu << std::endl;
    
    return 0;
}
