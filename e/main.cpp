#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Struktura z u¿yciem std::string
struct osoba {
    std::string imie;
    std::string nazwisko;
    int nr; // Tradycyjny int (zwykle 4 bajty) zamiast int32_t
};

int main() {
    // Usuniêto sync_with_stdio, ¿eby konsola Code::Blocks nie zamra¿a³a komunikatów

    unsigned int ilosc = 0;
    std::cout << "Podaj ilosc osob: ";
    std::cin >> ilosc;

    std::vector<osoba> klasa(ilosc);

    // Wprowadzanie danych - klasyczna pêtla for kompatybilna ze starym C++
    for (unsigned int i = 0; i < ilosc; ++i) {
        std::cout << "\n--- Osoba " << (i + 1) << " ---\n";
        std::cout << "Podaj imie: ";
        std::cin >> klasa[i].imie;
        std::cout << "Podaj nazwisko: ";
        std::cin >> klasa[i].nazwisko;
        std::cout << "Podaj numer: ";
        std::cin >> klasa[i].nr;
    }

    // Zapis do pliku binarnego ze stringami
    std::ofstream plikWy("baza_string.bin", std::ios::binary);
    if (plikWy.is_open()) {
        // 1. Zapis liczby osób (wymuszone 4 bajty przez rzutowanie)
        unsigned int lenIlosc = ilosc;
        plikWy.write(reinterpret_cast<const char*>(&lenIlosc), sizeof(lenIlosc));

        // 2. Zapis ka¿dej osoby osobno
        for (unsigned int i = 0; i < klasa.size(); ++i) {
            // Zapis imienia (najpierw d³ugoœæ tekstu jako unsigned int, potem sam tekst)
            unsigned int lenImie = klasa[i].imie.size();
            plikWy.write(reinterpret_cast<const char*>(&lenImie), sizeof(lenImie));
            plikWy.write(klasa[i].imie.data(), lenImie);

            // Zapis nazwiska
            unsigned int lenNazwisko = klasa[i].nazwisko.size();
            plikWy.write(reinterpret_cast<const char*>(&lenNazwisko), sizeof(lenNazwisko));
            plikWy.write(klasa[i].nazwisko.data(), lenNazwisko);

            // Zapis numeru
            plikWy.write(reinterpret_cast<const char*>(&klasa[i].nr), sizeof(klasa[i].nr));
        }

        plikWy.close();
        std::cout << "\n[Sukces] Zapisano dane ze stringami do 'baza_string.bin'.\n";
    } else {
        std::cerr << "[Blad] Nie udalo sie otworzyc pliku do zapisu!\n";
    }

    return 0;
}
