#define ARDUINO_JSON_ENABLE_STD_STRING
#include "arduinojson.h"
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

const int MAX_PLAYERS = 50;
const char* FILENAME = "ranking.json";

void start(char userInput);
void drawMenu();
void showOptions(StaticJsonDocument<1024>& doc);
void loadCredits();
void loadSettings(char userInput);
void saveRanking(int losowy, string nazwaGracza);
void showRanking();

int main()
{
    system("chcp 1250");
    system("cls");

    int losowy;
    char userInput = '0';
    srand(time(NULL));
    string nazwaGracza;

    start(userInput);

    while (userInput != '5')
    {
        cin >> userInput;

        switch (userInput)
        {
        case '1':
            losowy = rand() % 1000;

            system("cls");
            cout << "Podaj nazwę gracza: ";
            cin >> nazwaGracza;

            system("cls");
            cout << "Gracz " << nazwaGracza << " uzyskał wynik " << losowy << " punktów!" << endl;

            saveRanking(losowy, nazwaGracza);

            cout << endl << "1. Powrót" << endl << "2. Wyjście" << endl;
            cin >> userInput;

            if (userInput == '1')
                drawMenu();
            else
                exit(0);

            break;

        case '2':
            system("cls");
            cout << "SAVE CORRUPTED, PLEASE START A NEW GAME\n";
            cout << "1. OK\n";

            cin >> userInput;

            drawMenu();

            break;

        case '3':
            system("cls");
            showRanking();
            cout << endl << "1. Powrót" << endl << "2. Wyjście" << endl;

            cin >> userInput;

            if (userInput == '1')
                drawMenu();
            else
                exit(0);

            break;

        case '4':
            system("cls");
            cout << "1. Opcje" << endl << "2. Autor" << endl << "3. Powrót" << endl;

            cin >> userInput;

            switch (userInput)
            {
            case '1':
                loadSettings(userInput);
                cin >> userInput;
                break;

            case '2':
                loadCredits();
                cout << endl << "1. Powrót" << endl;
                cin >> userInput;
                drawMenu();
                break;

            case '3':
                drawMenu();
                break;

            default:
                drawMenu();
                cin >> userInput;
            }
            break;

        case '5':
            exit(0);

        default:
            drawMenu();
            cin >> userInput;
        }
    }  
    return 0;
}


void start(char userInput) {
    cout << "Menu Główne Gry\n";
    cout << "\n"; 
    cout << "Wykonał: \n";
    cout << "Wiktor Pieprzowski\n";
    cout << "Numer Indeksu: 156657\n";
    cout << "Semestr: 2\n";
    cout << "Rok Akademicki: 1\n";
    cout << "Tryb: Dzienne\n";
    cout << "\n";
    cout << "Wciśnij dowolny przycisk!\n";

    cin >> userInput;

    drawMenu();
}

void drawMenu()
{
    system("cls");
    cout << "1. Nowa Gra\n";
    cout << "2. Wczytaj Grę\n";
    cout << "3. Ranking\n";
    cout << "4. Ustawienia\n";
    cout << "5. Wyjdź z gry\n";
}

void showOptions(StaticJsonDocument<1024>& doc)
{
    int i = 1;
    for (JsonPair p : doc.as<JsonObject>())
    {
        cout << i << ". " << p.key() << " " << p.value() << '\n';
        i++;
    }
}

void loadCredits()
{
    fstream cred;
    StaticJsonDocument<1024> credits;
    cred.open("credits.json", ios::in);
    if (!cred.good())
    {
        cout << "Nie udało się otworzyć pliku!\n";
        exit(0);
    }
    else
    {
        string fileContent;
        string line;
        while (getline(cred, line))
        {
            fileContent += line;
        }

        deserializeJson(credits, fileContent);

        system("cls");
        cout << "---CREDITS---\n";

        showOptions(credits);

        cred.close();
    }
}

StaticJsonDocument<1024> rankingDoc;
JsonArray rankingArray = rankingDoc.to<JsonArray>();

void showRanking() 
{
    int i = 1;

    cout << "---RANKING---" << endl;

    for (const auto& entry : rankingArray) 
    {
        cout << i << ". " << entry["gracz"].as<string>() << " " << entry["wartosc"].as<int>() << '\n';
        i++;
    }
}

void saveRanking(int losowy, string nazwaGracza) 
{
    if (rankingArray.size() >= MAX_PLAYERS) 
    {
        cout << "Osiągnięto maksymalną liczbę graczy w rankingu" << endl;
        exit(0);
    }

    JsonObject nowyWpis = rankingArray.createNestedObject();
    nowyWpis["gracz"] = nazwaGracza;
    nowyWpis["wartosc"] = losowy;

    fstream file(FILENAME, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        cout << "Błąd podczas otwierania pliku" << endl;
        exit(0);
    }

    serializeJson(rankingDoc, file);

    file.close();
}

void loadSettings(char userInput)
{
    fstream sett;
    StaticJsonDocument<1024> settings;
    sett.open("settings.json", ios::in);
    if (!sett.good())
    {
        cout << "cannot open file!\n";
        exit(0);
    }
    else
    {
        string fileContent;
        string line;
        while (getline(sett, line))
        {
            fileContent += line;
        }

        deserializeJson(settings, fileContent);

        system("cls");
        cout << "---SETTINGS---\n";

        showOptions(settings);

        cout << endl << "1. Edytuj" << endl << "2. Powrót" << endl;
        cin >> userInput;

        if (userInput == '1')
        {
            system("cls");
            cout << "---SETTINGS---\n";

            showOptions(settings);

            cout << endl << "Podaj nową wartość, bądź wciśnij 'n' żeby przejść do następnej opcji" << endl;

            for (JsonPair p : settings.as<JsonObject>())
            {
                string newValue;
                cout << "Podaj nowa wartość dla " << p.key() << ": ";
                cin >> newValue;

                if (newValue == "n") continue;
                settings[p.key()] = newValue;

            }
            sett.close();

            fstream file;
            file.open("settings.json", ios::out);
            if (file.good())
            {
                string tmp;
                serializeJson(settings, tmp);
                file << tmp;
                file.close();
            }

            cout << endl << "Wciśnij dowolny przycisk, aby wrócić do menu głównego!" << endl;
            cin >> userInput;
            drawMenu();
        }
        else
        {
            drawMenu();
        }
    }
}

//POLIGON
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
*/
/*
void saveRanking(int losowy, string nazwaGracza)
{
    fstream file;
    StaticJsonDocument<1024> saveRanking;
    file.open("ranking.json", ios::out);
    if (file.good())
    {
        JsonObject nowyWpis = saveRanking.createNestedObject();
        nowyWpis["gracz"] = nazwaGracza;
        nowyWpis["wartosc"] = losowy;

        // Serializuj dokument JSON do łańcucha znaków
        string nowyJson;
        serializeJson(saveRanking, nowyJson);
    }
    else
    {
        cout << "dupa";
    }
    file.close();
}
*/