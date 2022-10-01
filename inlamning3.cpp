//
//  main.cpp
//  inlamning3
//
//  Created by Louise Kanizsai Ståhl on 2022-06-29.
//

#include <iostream>
using namespace std;

// Deklarationer av funktionerna
void skrivInfo();
int lasEttTal();
char lasOp();
void ordna (int a, int b, int &min, int &max);
int berakna (int min, int max, char amk);
void skrivResultat (long svar);

// Huvudfunktion
int main()
{
    // Deklaration av variabler
    int tal1, tal2, min, max, svar;
    char op;
  
    // Anrop av funktioner
    skrivInfo();
    tal1 = lasEttTal();
    tal2 = lasEttTal();
    op = lasOp();
    ordna(tal1, tal2, min, max);
    svar = berakna(min, max, op);
    skrivResultat(svar);

    return 0;
}

// Definitioner av funktioner:

// skriver ut info
void skrivInfo()
{
    cout << "Hej! Det här programmet frågar efter två tal och en beräkningstyp (a = addition, m = multiplikation eller k = kvadratsumman). Alla tal, från det minsta till det största beräknas då efter vald beräkningstyp. Exempelvis talen 1 och 4 med valet m ger svaret 24 (1*2*3*4 = 24)." << endl;
}

// läser in tal
int lasEttTal()
{
    int tal;
    
    cout << "Ge ett tal: ";
    cin >> tal;
    
    return tal;
}

// läser in vald beräkning
char lasOp()
{
    char op;
    
    cout << "Ge en beräkningstyp (a, m, k): ";
    cin >> op;
    
    return op;
}

// ordnar inlästa tal i storleksordning
void ordna (int a, int b, int &min, int &max)
{
    if (a < b) {
        min = a;
        max = b;
    }
    else {
        min = b;
        max = a;
    }
}

// gör den valda beräkningen
int berakna (int min, int max, char amk)
{
    int svar = 0, i = 0;
    
    if (amk == 'a' || amk == 'A')
    {
        for (i=min; i <= max; i++) // loop som adderar varje tal till "svar" tills i blivit max (nått det största talet)
            {
                svar += i;
            }
        return svar;
    }
    
    if (amk == 'm' || amk == 'M')
    {
        svar = 1; // svar behöver börja på 1 eftersom allt * 0 = 0
        
        for (i=min; i <= max; i++) // loop som multiplicerar istället för adderar som ovan
            {
                svar *= i;
            }
        return svar;
    }
    
    if (amk == 'k' || amk == 'K')
    {
        for (i=min; i <= max; i++) // loop som multiplicerar det aktuella talet med sig själv och adderar detta till "svar", tills i blivit max
            {
                svar += i*i;
            }
        return svar;
    }
   
    else
    {
        // om felaktigt tecken skrivits in
        cout << "Vänligen skriv in a, m eller k som beräkning." << endl;
        
        return 0;
    }
    
}

// skriver ut resultat
void skrivResultat (long svar)
{
    cout << "Resultatet blev: " << svar << endl;
}
