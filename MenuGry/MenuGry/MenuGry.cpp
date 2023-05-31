#define ARDUINO_JSON_ENABLE_STD_STRING
#include "arduinojson.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

// Struktura przechowująca dane gry
struct GameData {
    string result;
};

// Funkcja do zapisu danych gry do pliku JSON
void saveGame(const GameData& gameData) {
    StaticJsonDocument<128> doc;
    doc["result"] = gameData.result;

    ofstream file("menu.json");
    if (file) {
        serializeJson(doc, file);
        file.close();
        cout << "Gra została zapisana.\n";
    }
    else {
        cout << "Błąd zapisu gry.\n";
    }
}

// Funkcja do wczytania danych gry z pliku JSON
GameData loadGame() {
    ifstream file("menu.json");
    if (file) {
        StaticJsonDocument<128> doc;
        deserializeJson(doc, file);
        file.close();

        GameData gameData;
        gameData.result = doc["result"].as<string>();

        return gameData;
    }
    else {
        cout << "SAVE CORRUPTED PLEASE START A NEW GAME\n";
        return GameData();
    }
}

// Funkcja do wyświetlenia rankingów
void showRanking() {
    ifstream file("menu.json");
    if (file) {
        StaticJsonDocument<128> doc;
        deserializeJson(doc, file);
        file.close();

        vector<string> rankings;
        for (const auto& element : doc.as<JsonObject>()) {
            rankings.push_back(element.key().c_str());
        }

        sort(rankings.begin(), rankings.end(), greater<string>());

        cout << "Ranking:\n";
        for (const auto& ranking : rankings) {
            cout << ranking << "\n";
        }
    }
    else {
        cout << "Brak rankingów.\n";
    }
}

int main() {
    system("chcp 1250");
    system("cls");

    int choice;

    do {
        cout << "Menu Główne:\n";
        cout << "1. Nowa Gra\n";
        cout << "2. Wczytaj Grę\n";
        cout << "3. Ranking\n";
        cout << "4. Ustawienia\n";
        cout << "5. Wyjdź z Gry\n";
        cout << "Wybierz opcję: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            // Generowanie losowego wyniku i zapis do pliku
            string randomResult = "ABCD"; // Przykład losowego wyniku
            GameData gameData;
            gameData.result = randomResult;
            saveGame(gameData);
            break;
        }
        case 2: {
            // Wczytanie gry
            GameData gameData = loadGame();
            // Przetwarzanie wczytanych danych gry...
            break;
        }
        case 3: {
            // Wyświetlanie rankingów
            showRanking();
            break;
        }
        case 4: {
            // Ustawienia
            // TODO: Zaimplementuj funkcjonalność ustawień
            break;
        }
        case 5: {
            // Wyjście z gry
            char confirm;
            cout << "Czy na pewno chcesz wyjść z gry? (y/n): ";
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y') {
                cout << "Wyłączanie programu...\n";
                return 0;
            }
            break;
        }
        default:
            cout << "Niepoprawny wybór. Spróbuj ponownie.\n";
            break;
        }

        cout << "\n";
    } while (true);

    return 0;
}








/*
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool start();
int drawMenu(StaticJsonDocument<1024> doc);

void drawMenu2()
{
    cout << "1. Nowa Gra\n"; //UŻYTKOWNIK PODAJE NAZWĘ, A NASTĘPNIE ZAPISUJE SIE RANDOMOWA WARTOSC DO RANKINGU
    cout << "2. Wczytaj Grę\n"; //"SAVE CORRUPTED PLEASE STAR A NEW GAME"
    cout << "3. Ranking\n"; //WYŚWIETLA RANKING{NAZWA GRACZA : WYNIK}
    cout << "4. Ustawienia\n"; //USTAWIENIA GRAFICZNE{PRESET, ROZDZIELCZOSC, TEKSTURY, CIENIE, ODLEGLOSC RYSOWANIA, POLE WIDZENIA, DLSS}, STEROWANIE{CHODZENIE, CZULOSC MYSZY, TYP STEROWANIA}, DŹWIĘK{TYP URZĄDZENIA, ROZPIĘTOŚĆ TONALNA, GŁOŚNOŚĆ}, AUTORZY
    cout << "5. Wyjdź z gry\n"; //POTWIERDZENIE CZY NA PEWNO
}

int main()
{
    system("chcp 1250");
    system("cls");
    string temp;
    int menuGlowne;
    bool wyjscie;

    //cout << menu;
    //cin >> temp;

    fstream f;
    StaticJsonDocument<1024> doc;
    f.open("menu.json", ios::in);
    if (!f.good())
    {
        cout << "cannot open file!\n";
        exit;
    }
    else
    {
        //cout << "File opened\n";

        std::string fileContent;
        std::string line;
        while (getline(f, line))
        {
            fileContent += line;
        }

        //cout << fileContent << '\n';

        deserializeJson(doc, fileContent);
        /*
        cout << "Wszystkie klucze i wartości z obiektu info:\n";
        for (JsonPair keyValue : doc["info"].as<JsonObject>())
        {
            cout << keyValue.key() << " : " << keyValue.value() <<"\n";
        }

        cout << "Wszystkie klucze i wartości z dokumentu:\n";
        for (JsonPair keyValue : doc.as<JsonObject>())
        {
            cout << keyValue.key() << " : " << keyValue.value() << "\n";
        }
        
    }
    wyjscie = start();
    
    if (wyjscie == false)
        menuGlowne = drawMenu(doc);
    else
        exit;

    f.close();
    return 0;
}

bool start() {
    char wybor;
    bool wyjscie;

        cout << "Menu Główne Gry\n";
        cout << "\n";
        cout << "Wykonał: \n";
        cout << "Wiktor Pieprzowski\n";
        cout << "Numer Indeksu: 156657\n";
        cout << "Semestr: 2\n";
        cout << "Rok Akademicki: 1\n";
        cout << "Tryb: Dzienne\n";
        cout << "\n";
        cout << "Wciśnij dowolny przycisk aby zacząć, bądź 1, by wyjść z programu!\n";
        cin >> wybor;
        if (wybor == '1')
            wyjscie = true;
        else
            wyjscie = false;

    return wyjscie;
}

int drawMenu(StaticJsonDocument<1024> doc)
{
    int menu;
    bool dziala = true;
    string nazwaGracza;
    string ok;
    char wybor;

    while (dziala == true)
    {
        srand(time(NULL));
        int wynik = rand() % 100;
        JsonObject obj = doc.createNestedObject("ranking");

        system("cls");
        cout << "1. Nowa Gra\n"; //UŻYTKOWNIK PODAJE NAZWĘ, A NASTĘPNIE ZAPISUJE SIE RANDOMOWA WARTOSC DO RANKINGU
        cout << "2. Wczytaj Grę\n"; //"SAVE CORRUPTED PLEASE STAR A NEW GAME"
        cout << "3. Ranking\n"; //WYŚWIETLA RANKING{NAZWA GRACZA : WYNIK}
        cout << "4. Ustawienia\n"; //USTAWIENIA GRAFICZNE{PRESET, ROZDZIELCZOSC, TEKSTURY, CIENIE, ODLEGLOSC RYSOWANIA, POLE WIDZENIA, DLSS}, STEROWANIE{CHODZENIE, CZULOSC MYSZY, TYP STEROWANIA}, DŹWIĘK{TYP URZĄDZENIA, ROZPIĘTOŚĆ TONALNA, GŁOŚNOŚĆ}, AUTORZY
        cout << "5. Wyjdź z gry\n"; //POTWIERDZENIE CZY NA PEWNO
        cin >> menu;

        switch (menu)
        {
        case 1:
            system("cls");
            cout << "Podaj nazwę gracza: ";
            cin >> nazwaGracza;

            obj[nazwaGracza] = wynik;

            cout << endl;
            cout << "1. Powrót do menu\n";
            cin >> ok;
            break;

        case 2:
            system("cls");
            cout << "PLIK ZAPISU USZKODZONY, ROZPOCZNIJ NOWĄ GRĘ\n 1. OK\n";
            cin >> ok;
            break;

        case 3:
            system("cls");
            cout << "Ranking graczy:\n";

            for (JsonPair keyValue : doc["ranking"].as<JsonObject>())
            {
                cout << keyValue.key() << " : " << keyValue.value() << "\n";
            }

            cout << endl;
            cout << "1. Powrót do menu\n";
            cin >> ok;
            break;
        case 4:

            system("cls");
            cout << "OPCJA 4\n";
            break;
        case 5:

            system("cls");
            cout << "Czy na pewno chcesz wyjść?" << endl << "Wciśnij dowolny przycisk żeby wyjść, bądź 1 żeby zostać\n";
            cin >> wybor;
            if (wybor == '1')
                dziala = true;
            else
                dziala = false;
            break;

        default:
            cout << "Podano niewłaściwą opcję\n";
        }
    }

    
        
    return menu;
}
*/