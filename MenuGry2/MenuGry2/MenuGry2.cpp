// MenuGry2.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <map>

using namespace std;

void drawMenu()
{
    //system("cls");
    cout << "1. Nowa Gra\n"; //UŻYTKOWNIK PODAJE NAZWĘ, A NASTĘPNIE ZAPISUJE SIE RANDOMOWA WARTOSC DO RANKINGU
    cout << "2. Wczytaj Grę\n"; //"SAVE CORRUPTED PLEASE STAR A NEW GAME"
    cout << "3. Ranking\n"; //WYŚWIETLA RANKING{NAZWA GRACZA : WYNIK}
    cout << "4. Ustawienia\n"; //USTAWIENIA GRAFICZNE{PRESET, ROZDZIELCZOSC, TEKSTURY, CIENIE, ODLEGLOSC RYSOWANIA, POLE WIDZENIA, DLSS}, STEROWANIE{CHODZENIE, CZULOSC MYSZY, TYP STEROWANIA}, DŹWIĘK{TYP URZĄDZENIA, ROZPIĘTOŚĆ TONALNA, GŁOŚNOŚĆ}, AUTORZY
    cout << "5. Wyjdź z gry\n"; //POTWIERDZENIE CZY NA PEWNO
}

void loadConfig(string configName, map<string, string>& settings)
{
    fstream config;
    config.open("NAZZWA PLIKU ZAACZYTYWANEGO", std::ios::in);
    if (config.good())
    {
        while (!config.eof())
        {
            std::string t1, t2;
            config >> t1 >> t2;
            settings.insert({ t1, t2 });
        }
    }
    config.close();
}

void saveConfig(string configName, map<string, string>& settings)
{
    fstream config;
    config.open("NAZZWA PLIKU ZAACZYTYWANEGO", std::ios::out);
    if (config.good())
    {
        for (auto& el : settings)
        {
            config << el.first << " " << el.second;
        }

    }
    config.close();
}

int main()
{
    system("chcp 1250");

    char userInput;

    map <string, string> mapSettings;

    loadConfig("NAZWA WCZYTYWAQNEGO PLIKU", mapSettings);

    /*
    for (auto el : mapSettings)
        cout << el.first << " " << el.second;
    */

    while (true)
    {
        drawMenu();
        userInput = getchar();
        //getchar(); //niby że powinno działać bez tego

        switch (userInput)
        {
        case '1':
            cout << "Wybrano nowa gra\n";
            break;
        case '2':
            cout << "wybrano wczytanie\n";
            break;
        case '3':
            cout << "ranking\n";
            break;
        case '4':
            //WYRZUCIC DO OSOBNEJ FUNKCJI
            cout << "ustawienia\n";
            while (true)
            {
                cout << "press 0 to back\n";
                int i = 1;
                for (auto el : mapSettings)
                {
                    cout << i << el.first << " " << el.second;
                    i++;
                }
                int userInputOptions;
                cin >> userInputOptions;

                if (userInputOptions == 0) break;

                i = 1;
                for (auto& el : mapSettings)
                {
                    if (i == userInputOptions)
                    {
                        cout << "podaj nowa wartosc dla " << el.first << endl;
                        std::string newValue;
                        cin >> newValue;
                        el.second = newValue;
                        break;
                    }
                    i++;
                }
            }
            break;
        case '5':
            cout << "wyjscie";
            saveConfig("NAZWA PLIKU", mapSettings);
            exit(0);
            break;
        default:
            cout << "dupa";
            break;
        }
    }
    
    return 0;
}
