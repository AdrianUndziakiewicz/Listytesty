#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>    
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>
#include <memory>
#include <random>

#include "array_list.h"
#include "singly_linked_list.h"
#include "doubly_linked_list.h"

//funkcja do wyœwietlania elementów struktury
template <typename T>
void displayStructure(const T& list) {
    if (list.getSize() == 0) {
        std::cout << "Struktura jest pusta." << std::endl;
        return;
    }   
        
    std::cout << "Elementy struktury (" << list.getSize() << "): ";
    //ograniczenie wyœwietlania do max. 100 elementów
    int displayLimit = std::min(100, list.getSize());

    for (int i = 0; i < displayLimit; i++) {
        std::cout << list.get(i);   
        if (i < displayLimit - 1) {
            std::cout << ", ";
        }
    }

    if (list.getSize() > displayLimit) {
        std::cout << ", ... (i " << (list.getSize() - displayLimit) << " wiecej)";
    }

    std::cout << std::endl;
}

// Funkcja do losowego generowania struktury
template <typename T>
void generateRandomStructure(T& list, int size) {
    //u¿ycie silnika MT19837 dla lepszej jakoœci liczb losowych 
    std::random_device rd;  //zmienna do generowania ziarna
    std::mt19937 gen(rd()); //silnik z losowym ziarnem
    std::uniform_int_distribution<> distrib(0, 999); //rozk³ad jednostajny od 0 do 999
            
    list.clear();
    for (int i = 0; i < size; i++) {
        list.addLast(distrib(gen));  //generowanie losowej liczby przy u¿yciu mt19937
    }
    std::cout << "Wygenerowano strukture z " << size << " losowymi elementami." << std::endl;
}

//funkcja do wczytywania danych z pliku 
template <typename T>
void loadFromFile(T& list, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku: " << filename << std::endl;
        return;
    }

    list.clear();  //wyczyœc liste przed wczytaniem nowych danych
    int value;
    while (file >> value) {
        list.addLast(value);
    }

    file.close();
    std::cout << "Wczytano " << list.getSize() << " elementow z pliku." << std::endl;
}       
    
//funkcja do zapisywania danych do pliku    
template <typename T>
void saveToFile(const T& list, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku do zapisu: " << filename << std::endl;
        return;
    }

    for (int i = 0; i < list.getSize(); i++) {
        file << list.get(i) << std::endl;
    }

    file.close();
    std::cout << "Zapisano " << list.getSize() << " elementow do pliku." << std::endl;
}

//ogólna funkcja menu dla dowolnego typu listy
template <typename T>   
void listMenu(T& list, const std::string& listName) {
    int choice = 0; 
    int value, index, size;     
    std::string filename;
        
    while (true) {
        std::cout << "\n=== MENU " << listName << " ===" << std::endl;
        std::cout << "1. Dodaj element na poczatku" << std::endl;   
        std::cout << "2. Dodaj element na koncu" << std::endl;
        std::cout << "3. Dodaj element na pozycji" << std::endl;
        std::cout << "4. Usun element z poczatku" << std::endl;
        std::cout << "5. Usun element z konca" << std::endl;    
        std::cout << "6. Usun element z pozycji" << std::endl;  
        std::cout << "7. Wyszukaj element" << std::endl;
        std::cout << "8. Wyœwietl strukture" << std::endl;
        std::cout << "9. Wczytaj z pliku" << std::endl; 
        std::cout << "10. Zapisz do pliku" << std::endl;
        std::cout << "11. Generuj losowo" << std::endl;
        std::cout << "12. Wyczysc strukture" << std::endl;  
        std::cout << "0. Powrot do glownego menu" << std::endl;
        std::cout << "Wybierz opcje: ";     
        std::cin >> choice;

        if (std::cin.fail()) {  
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Nieprawidlowe dane wejsciowe. Sprobuj ponownie." << std::endl;
            continue;   
        }

        switch (choice) {
        case 0: 
            return;
        case 1: 
            std::cout << "Podaj wartosc: ";
            std::cin >> value;  
            list.addFirst(value);
            std::cout << "Dodano element " << value << " na poczatku." << std::endl;
            break;
        case 2: 
            std::cout << "Podaj wartosc: ";
            std::cin >> value;
            list.addLast(value);
            std::cout << "Dodano element " << value << " na koncu." << std::endl;   
            break;
        case 3:
            std::cout << "Podaj indeks (0-" << list.getSize() << "): "; 
            std::cin >> index;  
            std::cout << "Podaj wartosc: ";
            std::cin >> value;
            try {
                list.addAt(index, value);       
                std::cout << "Dodano element " << value << " na pozycji " << index << "." << std::endl; 
            }
            catch (const std::out_of_range& e) {    
                std::cout << "Blad: " << e.what() << std::endl;
            }
            break;  
        case 4:
            try {   
                value = list.removeFirst(); 
                std::cout << "Usunieto element " << value << " z poczatku." << std::endl;
            }   
            catch (const std::out_of_range& e) {
                std::cout << "Blad: " << e.what() << std::endl;
            }
            break;  
        case 5:
            try {
                value = list.removeLast();  
                std::cout << "Usunieto element " << value << " z konca." << std::endl;
            }
            catch (const std::out_of_range& e) {    
                std::cout << "Blad: " << e.what() << std::endl;
            }   
            break;
        case 6:
            std::cout << "Podaj indeks (0-" << (list.getSize() - 1) << "): ";   
            std::cin >> index;  
            try {
                value = list.removeAt(index);
                std::cout << "Usunieto element " << value << " z pozycji " << index << "." << std::endl;    
            }
            catch (const std::out_of_range& e) {
                std::cout << "Blad: " << e.what() << std::endl;
            }
            break;  
        case 7:
            std::cout << "Podaj wartosc do wyszukania: ";
            std::cin >> value;  
            if (list.search(value)) {
                std::cout << "Element " << value << " znajduje siê w strukturze." << std::endl;
            }   
            else {
                std::cout << "Element " << value << " nie zostal znaleziony." << std::endl;
            }
            break;
        case 8: 
            displayStructure(list);
            break;
        case 9:
            std::cout << "Podaj nazwê pliku: ";
            std::cin >> filename;   
            loadFromFile(list, filename);
            break;
        case 10:
            std::cout << "Podaj nazwê pliku: ";
            std::cin >> filename;   
            saveToFile(list, filename);
            break;
        case 11:    
            std::cout << "Podaj rozmiar: ";
            std::cin >> size;
            generateRandomStructure(list, size);    
            break;
        case 12:
            list.clear();
            std::cout << "Struktura zostala wyczyszczona." << std::endl;    
            break;
        default:
            std::cout << "Nieprawidlowa opcja. Sprobuj ponownie." << std::endl;
        }
    }
}   

//funkcja do tworzenia wype³nionej tabllicy dynamicznej
ArrayList<int> createFilledArrayList(int size, int rep, const std::vector<std::vector<int>>& randomInitialValues) {
    ArrayList<int> list;    
    for (int i = 0; i < size; i++) {
        list.addLast(randomInitialValues[rep][i]);  
    }
    return list;
}

//funkcja do tworzenia wype³nionej listy jednokierunkowej
SinglyLinkedList<int> createFilledSinglyLinkedList(int size, int rep, const std::vector<std::vector<int>>& randomInitialValues) {   
    SinglyLinkedList<int> list;
    for (int i = 0; i < size; i++) {
        list.addLast(randomInitialValues[rep][i]);
    }
    return list;
}   

//funkcja do tworzenia wype³nionej listy dwukierunkowej
DoublyLinkedList<int> createFilledDoublyLinkedList(int size, int rep, const std::vector<std::vector<int>>& randomInitialValues) {
    DoublyLinkedList<int> list;
    for (int i = 0; i < size; i++) {
        list.addLast(randomInitialValues[rep][i]);  
    }
    return list;
}

//funkcja generuj¹ca losowe tablice
void generateRandomArrays(std::vector<std::vector<int>>& randomInitialValues,   
    std::vector<std::vector<int>>& randomPositionsAdd,
    std::vector<std::vector<int>>& randomPositionsRemove,
    std::vector<std::vector<int>>& randomValuesSearch) {
    //sta³e dla testów
    const int REPETITIONS = 100;
    const std::vector<int> TEST_SIZES = { 5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000 };

    //znajdŸ maksymalny rozmiar
    int maxSize = *std::max_element(TEST_SIZES.begin(), TEST_SIZES.end());  

    //dla ka¿dego runa, generuj tablice losowych pozycji, wartoœci i wartoœci pocz¹tkowych
    for (int rep = 0; rep < REPETITIONS; rep++) {
        std::vector<int> positionsAdd;  
        std::vector<int> positionsRemove;
        std::vector<int> valuesSearch;  
        std::vector<int> initialValues;

        //generuj losowe wartoœci do pocz¹tkowego wype³nienia struktur danych
        for (int i = 0; i < maxSize; i++) {
            initialValues.push_back(std::rand() % (maxSize * 10));  
        }
            
        //generuj losowe pozycje do dodawania   
        for (int i = 0; i < maxSize / 10; i++) {
            positionsAdd.push_back(std::rand() % (maxSize + 1));
        }

        //generuj losowe pozycje do usuwania    
        for (int i = 0; i < maxSize / 20; i++) {
            positionsRemove.push_back(std::rand() % maxSize);
        }
            
        //generuj losowe wartoœci do wyszukiwania
        for (int i = 0; i < maxSize / 100; i++) {
            valuesSearch.push_back(std::rand() % (maxSize * 10));   
        }

        randomInitialValues.push_back(initialValues);
        randomPositionsAdd.push_back(positionsAdd); 
        randomPositionsRemove.push_back(positionsRemove);
        randomValuesSearch.push_back(valuesSearch);
    }
}   
//szablon funkcji testuj¹cej wydajnoœæ dla dowolnego typu listy - pojedyncze operacje
template <typename T, typename CreateFilledListFunc>
void testListPerformance(std::ofstream& resultsFile,
    const std::string& listName,    
    CreateFilledListFunc createFilledList,
    const std::vector<std::vector<int>>& randomInitialValues,
    const std::vector<std::vector<int>>& randomPositionsAdd,    
    const std::vector<std::vector<int>>& randomPositionsRemove,
    const std::vector<std::vector<int>>& randomValuesSearch) {
    //sta³e dla testów  
    const int REPETITIONS = 100;
    const std::vector<int> TEST_SIZES = { 5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000 };  

    std::cout << "\n=== TESTOWANIE " << listName << " ===" << std::endl;
    resultsFile << "\n=== " << listName << " ===" << std::endl; 

    //nag³ówki do pliku CSV
    resultsFile << "Rozmiar,DodajPocz¹tek(ms),DodajKoniec(ms),DodajLosowo(ms),UsuñPocz¹tek(ms),UsuñKoniec(ms),UsuñLosowo(ms),Wyszukaj(ms)" << std::endl;    

    for (int size : TEST_SIZES) {
        std::cout << "Testowanie dla rozmiaru: " << size << std::endl;

        //zmienne do przechowywania czasów  
        double totalAddFirstTime = 0;
        double totalAddLastTime = 0;
        double totalAddRandomTime = 0;
        double totalRemoveFirstTime = 0;
        double totalRemoveLastTime = 0; 
        double totalRemoveRandomTime = 0;
        double totalSearchTime = 0;
            
        //tworzymy bazow¹ listê dla zadanego rozmiaru
        T baseList = createFilledList(size, 0, randomInitialValues);

        for (int rep = 0; rep < REPETITIONS; rep++) {
            //test dodawania na pocz¹tku    
            {
                T listCopy = baseList; //kopia do testu
                auto start = std::chrono::high_resolution_clock::now();
                listCopy.addFirst(randomInitialValues[rep % randomInitialValues.size()][0]);
                auto end = std::chrono::high_resolution_clock::now();   
                std::chrono::duration<double, std::micro> duration = end - start;
                totalAddFirstTime += duration.count();
            }

            //test dodawania na koñcu   
            {
                T listCopy = baseList;
                auto start = std::chrono::high_resolution_clock::now(); 
                listCopy.addLast(randomInitialValues[rep % randomInitialValues.size()][0]); 
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::micro> duration = end - start;   
                totalAddLastTime += duration.count();
            }

            //test dodawania na losowej pozycji
            {
                T listCopy = baseList;
                int randomPos = randomPositionsAdd[rep % randomPositionsAdd.size()][0] % (listCopy.getSize() + 1);  
                auto start = std::chrono::high_resolution_clock::now();
                listCopy.addAt(randomPos, randomInitialValues[rep % randomInitialValues.size()][0]);
                auto end = std::chrono::high_resolution_clock::now();   
                std::chrono::duration<double, std::micro> duration = end - start;
                totalAddRandomTime += duration.count();
            }

            //test usuwania z pocz¹tku
            {   
                T listCopy = baseList;
                if (listCopy.getSize() > 0) {
                    auto start = std::chrono::high_resolution_clock::now(); 
                    listCopy.removeFirst();
                    auto end = std::chrono::high_resolution_clock::now();   
                    std::chrono::duration<double, std::micro> duration = end - start;
                    totalRemoveFirstTime += duration.count();
                }
            }
                
            //test usuwania z koñca
            {
                T listCopy = baseList;
                if (listCopy.getSize() > 0) {   
                    auto start = std::chrono::high_resolution_clock::now();
                    listCopy.removeLast();  
                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::micro> duration = end - start;   
                    totalRemoveLastTime += duration.count();
                }       
            }

            //test usuwania z losowej pozycji
            {
                T listCopy = baseList;
                if (listCopy.getSize() > 0) {   
                    int randomPos = randomPositionsRemove[rep % randomPositionsRemove.size()][0] % listCopy.getSize();
                    auto start = std::chrono::high_resolution_clock::now();
                    listCopy.removeAt(randomPos);   
                    auto end = std::chrono::high_resolution_clock::now();   
                    std::chrono::duration<double, std::micro> duration = end - start;
                    totalRemoveRandomTime += duration.count();  
                }
            }

            //test wyszukiwania 
            {
                int randomValue = randomValuesSearch[rep % randomValuesSearch.size()][0];
                auto start = std::chrono::high_resolution_clock::now();
                baseList.search(randomValue);   
                auto end = std::chrono::high_resolution_clock::now();   
                std::chrono::duration<double, std::micro> duration = end - start;
                totalSearchTime += duration.count();
            }   
        }

        //obliczanie œrednich czasów    
        double avgAddFirstTime = totalAddFirstTime / REPETITIONS;
        double avgAddLastTime = totalAddLastTime / REPETITIONS; 
        double avgAddRandomTime = totalAddRandomTime / REPETITIONS;
        double avgRemoveFirstTime = totalRemoveFirstTime / REPETITIONS;
        double avgRemoveLastTime = totalRemoveLastTime / REPETITIONS;   
        double avgRemoveRandomTime = totalRemoveRandomTime / REPETITIONS;
        double avgSearchTime = totalSearchTime / REPETITIONS;   

        //wyniki
        std::cout << "Rozmiar: " << size << std::endl;  
        std::cout << "  Dodaj na poczatku: " << avgAddFirstTime << " mis" << std::endl;
        std::cout << "  Dodaj na koncu: " << avgAddLastTime << " mis" << std::endl; 
        std::cout << "  Dodaj losowo: " << avgAddRandomTime << " mis" << std::endl;
        std::cout << "  Usun z poczatku: " << avgRemoveFirstTime << " mis" << std::endl;
        std::cout << "  Usun z konca: " << avgRemoveLastTime << " mis" << std::endl;    
        std::cout << "  Usun losowo: " << avgRemoveRandomTime << " mis" << std::endl;   
        std::cout << "  Wyszukaj: " << avgSearchTime << " mis" << std::endl;

        //zapis do pliku
        resultsFile << size << ","  
            << avgAddFirstTime << ","
            << avgAddLastTime << ","    
            << avgAddRandomTime << ","
            << avgRemoveFirstTime << ","    
            << avgRemoveLastTime << ","
            << avgRemoveRandomTime << ","
            << avgSearchTime << std::endl;  
    }
}
//funkcja do przeprowadzenia testów
void runPerformanceTests() {    
    //inicjalizacja generatora liczb losowych
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    //wektory do przechowywania wygenerowanych losowych danych
    std::vector<std::vector<int>> randomInitialValues;  
    std::vector<std::vector<int>> randomPositionsAdd;
    std::vector<std::vector<int>> randomPositionsRemove;    
    std::vector<std::vector<int>> randomValuesSearch;

    //generowanie losowych tablic przed uruchomieniem testów    
    std::cout << "Generowanie losowych tablic..." << std::endl;
    generateRandomArrays(randomInitialValues, randomPositionsAdd, randomPositionsRemove, randomValuesSearch);   

    std::cout << "TESTOWANIE WYDAJNOŒCI STRUKTUR DANYCH" << std::endl;
    std::cout << "=====================================" << std::endl;  

    //otwarcie pliku do zapisywania wyników
    std::ofstream resultsFile("wyniki_struktur_danych.csv");
    if (!resultsFile.is_open()) {   
        std::cerr << "B³¹d: Nie mo¿na otworzyæ pliku wyników." << std::endl;    
        return;
    }

    //zapis nag³ówka
    resultsFile << "TESTOWANIE WYDAJNOŒCI STRUKTUR DANYCH" << std::endl;
            
    try {
        //uruchomienie testów dla ka¿dego typu listy
        std::cout << "Testowanie ArrayList..." << std::endl;
        testListPerformance<ArrayList<int>>(    
            resultsFile,
            "TABLICA DYNAMICZNA (ARRAYLIST)",
            createFilledArrayList,
            randomInitialValues,    
            randomPositionsAdd,
            randomPositionsRemove,  
            randomValuesSearch
        );  
        //upewniamy siê, ¿e dane zosta³y zapisane do pliku
        resultsFile.flush();

        std::cout << "Testowanie SinglyLinkedList..." << std::endl;
        testListPerformance<SinglyLinkedList<int>>( 
            resultsFile,
            "LISTA JEDNOKIERUNKOWA (SINGLY LINKED LIST)",
            createFilledSinglyLinkedList,
            randomInitialValues,
            randomPositionsAdd, 
            randomPositionsRemove,
            randomValuesSearch
        );
        resultsFile.flush();    

        std::cout << "Testowanie DoublyLinkedList..." << std::endl;
        testListPerformance<DoublyLinkedList<int>>(
            resultsFile,    
            "LISTA DWUKIERUNKOWA (DOUBLY LINKED LIST)",
            createFilledDoublyLinkedList,
            randomInitialValues,
            randomPositionsAdd, 
            randomPositionsRemove,
            randomValuesSearch  
        );
        resultsFile.flush();
    }
    catch (const std::exception& e) {
        std::cerr << "Wyst¹pi³ b³¹d podczas testowania: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Wyst¹pi³ nieznany b³¹d podczas testowania." << std::endl;
    }
    //zamkniêcie pliku
    resultsFile.close();    
    std::cout << "\nWyniki zosta³y zapisane do pliku wyniki_struktur_danych.csv" << std::endl;
}   

//g³ówna funkcja programu
int main() {
    //inicjalizacja generatora liczb losowych
    std::srand(static_cast<unsigned int>(std::time(nullptr)));  
    //tworzenie struktur danych
    ArrayList<int> arrayList;
    SinglyLinkedList<int> singlyLinkedList; 
    DoublyLinkedList<int> doublyLinkedList;

    int choice = 0;
        
    while (true) {
        std::cout << "\n=== G£ÓWNE MENU ===" << std::endl;
        std::cout << "1. Tablica dynamiczna (ArrayList)" << std::endl;
        std::cout << "2. Lista jednokierunkowa (Singly Linked List)" << std::endl;
        std::cout << "3. Lista dwukierunkowa (Doubly Linked List)" << std::endl;
        std::cout << "4. Przeprowadz testy wydajnosciowe" << std::endl; 
        std::cout << "0. Wyjscie" << std::endl;
        std::cout << "Wybierz opcje: ";
        std::cin >> choice;

        if (std::cin.fail()) {  
            std::cin.clear();   
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Nieprawidlowe dane wejsciowe. Sprobuj ponownie." << std::endl;
            continue;   
        }

        switch (choice) {
        case 0:
            std::cout << "Koniec programu." << std::endl;
            return 0;
        case 1: 
            listMenu(arrayList, "TABLICY DYNAMICZNEJ (ARRAYLIST)");
            break;
        case 2:
            listMenu(singlyLinkedList, "LISTY JEDNOKIERUNKOWEJ (SINGLY LINKED LIST)");
            break;  
        case 3:
            listMenu(doublyLinkedList, "LISTY DWUKIERUNKOWEJ (DOUBLY LINKED LIST)");    
            break;
        case 4: 
            runPerformanceTests();
            break;
        default:
            std::cout << "Nieprawidlowa opcja. Sprobuj ponownie." << std::endl;
        }   
    }
    return 0;   
}