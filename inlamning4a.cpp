//
//  main.cpp
//  inlamning4a
//
//  Created by Louise Kanizsai Ståhl on 2022-07-15.

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

const int ANTAL_BOKSTAVER = 26;  //A-Z

//--------------------------------------------------------
// Funktionsdeklarationer:

// Funktion som beräknar histogrammet
int berakna_histogram_abs(string &text, int frekvens[], int &totaltAntal);

// Funktion som skriver ut histogrammet
void skriv_histogram_abs(int frekvens[], int totaltAntal);

//--------------------------------------------------------
// Huvudprogram:

int main()
{
  // Deklarera variabler
    string text;
    int totaltAntal = 0; // Räknar totalt antal bokstäver i texten
    int frekvens[ANTAL_BOKSTAVER];
    
  // Läs in en rad med text från tangentbordet
    cout << "Ge en rad med text: " << endl;
    getline(cin,text);

  // Anropa funktionen berakna_histogram_abs som beräknar histogrammet
  // och antalet bokstäver.
    berakna_histogram_abs(text, frekvens, totaltAntal);
 
  // Anropa funktionen skriv_histogram_abs som skriver ut histogrammet
    skriv_histogram_abs(frekvens, totaltAntal);
    
    return 0;
}
//--------------------------------------------------------
// Funktionsdefinitioner:
int berakna_histogram_abs(string &text, int frekvens[], int &totaltAntal)
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
    return totaltAntal; // Funktionen returnerar totala antalet bokstäver
}

void skriv_histogram_abs(int frekvens[], int totaltAntal) {
    
    cout << endl << "Resultat för bokstäverna A-Z: " << endl << endl;
    cout << "Totala antalet bokstäver: " << totaltAntal << endl;
    cout << "Bokstavsfördelning: " << endl << endl;
    
    // Loop för utskrivning av frekvens/histogram
    for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
        char bokstav;
        bokstav = (i+'A'); // Bokstav blir den bokstav som motsvaras av det index vi är på
        cout << bokstav << ": " << frekvens[i] << endl;
    }
}
// Redovisning av uppgiften i ord.

// Programkörningar redovisas i separat pdf.
// Där skriver jag också svaren på de kompletterande frågorna.
