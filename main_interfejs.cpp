#include "InterfejsUzytkownika.h"
#include <iostream>

/**
 * @brief Główna funkcja programu - uruchamia interfejs użytkownika dla generatora sygnałów
 * @return 0 jeśli program zakończył się pomyślnie
 */
int main()
{
    try
    {
        InterfejsUzytkownika interfejs;
        interfejs.uruchom();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Błąd: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Nieznany błąd!" << std::endl;
        return 1;
    }
    
    return 0;
}
