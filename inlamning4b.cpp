//
//  main.cpp
//  inlamning4b
//
//  Created by Louise Kanizsai Ståhl on 2022-07-15.
//

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Globala konstanter:
const int ANTAL_BOKSTAVER = 26;  //A-Z
const int ANTAL_SPRAK = 4;

// 2d-arrayen TOLK_HJALP innehåller bokstavsfrekvensen i %
// för fyra språk.
const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER]=
       {{8.27,1.48,2.94,4.03,11.78,2.22,1.72,6.77, //engelska
         7.39,0.12,0.81,3.76,2.85,6.71,7.79,1.54,
         0.05,5.95,6.69,9.07,2.66,1.13,2.14,0.19,
         1.89,0.03},
        {7.97,1.40,3.55,3.79,16.89,1.02,1.00,0.75, //franska
         7.08,0.38,0.04,5.51,2.82,8.11,5.19,2.78,
         1.01,6.69,8.35,7.22,6.09,1.35,0.02,0.54,
         0.30,0.15},
        {9.50,1.11,1.53,5.30,8.94,1.74,3.57,3.94,  //svenska
         3.98,0.89,3.26,4.93,3.41,8.46,5.01,1.77,
         0.00,6.73,5.56,9.20,1.94,2.42,0.00,0.05,
         0.45,0.00},
        {5.12,1.95,3.57,5.07,16.87,1.35,3.00,5.79, //tyska
         8.63,0.19,1.14,3.68,3.12,10.64,1.74,0.42,
         0.01,6.30,6.99,5.19,3.92,0.77,1.79,0.01,
         0.69,1.24}};

//--------------------------------------------------------
// Funktionsdeklarationer:

// Funktionen berakna_histogram_abs
int berakna_histogram_abs(string &text, double frekvens[], int &totaltAntal);

// Funktionen abs_till_rel
void abs_till_rel(double frekvens[], int totaltAntal);

// Funktionen plotta_histogram_rel
void plotta_histogram_rel(double frekvens[]);

// Funktionen tolkning
void tolkning(double frekvens[]);

// Funktionen namn_pa_fil
string namn_pa_fil();

// Funktionen inlasning
string inlasning(string &filnamn);

//--------------------------------------------------------
// Huvudprogram:
int main()
{
    // Deklarera variabler
    string text;
    string fil;
    int totaltAntal = 0; // Räknar totalt antal bokstäver i texten
    double frekvens[ANTAL_BOKSTAVER];
    
    // Inläsning av filer med funktionerna namn_pa_fil och inlasning
    fil = namn_pa_fil();
    text = inlasning(fil);
    
    // Om filen inte finns returnerar funktionen inlasning strängen "finns ej" och programmet avslutas
    if (text == "finns ej")
        return 0;

    // Funktionsanrop
    berakna_histogram_abs(text, frekvens, totaltAntal);
    abs_till_rel(frekvens, totaltAntal);
    tolkning(frekvens);
    plotta_histogram_rel(frekvens);
    
    return 0;
}
//--------------------------------------------------------
// Funktionsdefinitioner:

int berakna_histogram_abs(string &text, double frekvens[], int &totaltAntal)
{
    // Nollställer histogram
    for (int i = 0; i < ANTAL_BOKSTAVER; i++)
        frekvens[i] = 0;
    
    // Loopar igenom hela texten
    for (int i = 0; i <text.length(); i++)
    {
        text.at(i) = toupper(text.at(i)); // Gör om varje index/i till versal
        
        int index; // Variabel för att hålla räkningen på index i frekvens
        
        if (text.at(i)>='A' && text.at(i)<='Z') // Om i är en bokstav A-Z...
        {
            index = text.at(i) -'A'; // ... så får index värdet av den bokstav vi hittat
            frekvens[index]++; // ... och lägger till +1 för den bokstaven
            totaltAntal++; // +1 till totalt antal bokstäver
        }
    }
    
    // Utskrift
    cout << endl << "Resultat för bokstäverna A-Z" << endl << endl;
    cout << "Totala antalet bokstäver: " << totaltAntal << endl;
    
    return totaltAntal; // Funktionen returnerar totala antalet bokstäver
}

void abs_till_rel(double frekvens[], int totaltAntal)
{
    for (int i = 0; i < ANTAL_BOKSTAVER; i++)
        frekvens[i] = (frekvens[i]/(double)totaltAntal)*100; // Gör om till relativt värde (procent)
}

void plotta_histogram_rel(double frekvens[])
{
    cout << endl << "Bokstavsfördelning: " << endl << endl;
    
    // Loop som går igenom varje bokstav
    for (int i = 0; i < ANTAL_BOKSTAVER; i++)
    {
        char bokstav;
        bokstav = (i+'A'); // "bokstav" blir den bokstav som motsvaras av det index vi är på
        cout << bokstav << ": ";
        
        // Nästlad loop för varje bokstav
        for (int j = 0; j < trunc(frekvens[i]/0.5); j++) // frekvens[i] blir nu antal symboler som ska skrivas ut (delar procentuell andel med 0.5 och trunkerar)
            cout << "*"; // Skriver ut en * för varje gång loopen körs
        cout << endl;
    }
}

void tolkning(double frekvens[])
{
    double kvadratsummor[ANTAL_SPRAK]; // Array som sparar kvadratsummorna för varje språk
    string spraknamn[4] = {"engelska","franska","svenska","tyska"};
    int minst = 0; // Antar att första kvadratsumman är den minsta
    
    // Loop för varje språk
    for (int i = 0; i < ANTAL_SPRAK; i++)
    {
        // Nollställer skillnad och summa för varje språk
        double skillnad, summa = 0.0;
        
        // Inre loop (för varje bokstav)
        for (int j = 0; j < ANTAL_BOKSTAVER; j++)
        {
            skillnad = (TOLK_HJALP[i][j]-frekvens[j]); // Beräknar skillnad
            summa += skillnad*skillnad; // Beräknar kvadratsumma
            kvadratsummor[i] = summa; // Lägger till kvadratsumma i arrayen
        }
        // Utskrift språk och motsvarande kvadratsumma
        cout << spraknamn[i] << " har kvadratsumma: " << kvadratsummor[i] << endl;
        
        // Uppdaterar "minst" om nästa kvadratsumma är mindre
        if (kvadratsummor[i] < kvadratsummor[minst])
            minst = i;
    }
    // Utskrift mest troliga språk
    cout << "Det mest troliga språket är " << spraknamn[minst] << ". " << endl;
}

string namn_pa_fil()
{
    string filnamn;
    
    cout << "Ange filnamn: " << endl;
    getline(cin, filnamn);
    
    // Letar efter .txt, börjar längst bak
    int pos = filnamn.rfind(".txt");
    
    // Lägger till .txt i slutet om det inte hittades
    if (pos == string::npos)
        filnamn.append(".txt");
    
    return filnamn;
}

string inlasning (string &filnamn)
{
    // Öppna fil för läsning
    ifstream fin(filnamn.c_str());
    
    // Om inget fel inträffat: läser in tecken för tecken (c), lägger till sist i sträng (text), returnerar text
    if (fin.good())
    {
        char c;
        string text;
        while (fin.get(c))
            text.push_back(c);
        return text;
    }
    else // Om fel
    {
        cout << "Det finns ingen fil med namnet " << filnamn << endl;
        return "finns ej";
    }
}
// -------------------------------------------------------
// Rapport om uppgiften
// Se separat pdf för programkörningar och svar på kompletterande frågor.
