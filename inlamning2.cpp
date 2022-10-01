//
//  inlamning2.cpp
//  inlamning2
//
//  Created by Louise Kanizsai Ståhl on 2022-06-23.
//

#include <iostream>
using namespace std;

int main(){
    int startnr, starttimme, startminut, startsekund; // variabler för startnummer resp starttid
    int maltimme, malminut, malsekund; // variabler för måltid
    int startsekunder, malsekunder; // variabler för starttid och måltid konverterat till sekunder
    int totalsekunder; // variabel för tid mellan starttid och måltid
    int totalminuter = 0, totaltimmar = 0, minuter, slutsekunder = 0; // variabler för konvertering av sekunder till tim, min, sek av vinnarens tid
    int vinnartid = 999999999, vinnarnr = 0, antal = 0; // variabler för vinnarberäkningar resp antal deltagare
    
    // Frågar efter första startnumret
    cout << "Startnummer? ";
    cin >> startnr;
    
    // Kontrollerar om startnummer är större än 0
    while (startnr > 0){
        
        antal ++; // +1 antal deltagare
        
        //Frågar efter starttid och måltid
        cout << "Starttid? ";
        cin >> starttimme >> startminut >> startsekund;
        cout << "Måltid? ";
        cin >> maltimme >> malminut >> malsekund;
        
        // Beräknar totala antalet sekunder för starttid resp måltid
        startsekunder = startsekund + (startminut*60) + (starttimme*3600);
        malsekunder = malsekund + (malminut*60) + (maltimme*3600);
        
        // Om startsekunder är större än målsekunder har man passerat midnatt
        // Adderar då 86400 sekunder (24 h) till målsekunder
        if (startsekunder > malsekunder)
            malsekunder = malsekunder + 86400;
        
        // Beräknar total tid
        totalsekunder = (malsekunder - startsekunder);
        
        // Kontrollerar om snabbaste tiden
        if (totalsekunder < vinnartid) {
            vinnartid = totalsekunder;
            vinnarnr = startnr;
        }
        
        // Frågar efter startnummer igen så att loopen körs om eller avslutas
        cout << "Startnummer? ";
        cin >> startnr;
    }
    
    // Om antal tävlande är fler än 0
    if (antal > 0) {
        
        // Beräknar vinnarens tid till timmar, minuter, sekunder
        totaltimmar = vinnartid/3600;
        minuter = vinnartid/60;
        totalminuter = minuter % 60;
        slutsekunder = vinnartid % 60;
  
        // Skriver ut vinnarens startnummer, dens tid samt antalet deltagare
        cout << "Vinnaren är startnr: " << vinnarnr << endl;
        cout << "Tim: " << totaltimmar << " Min: " << totalminuter << " Sek: " << slutsekunder << endl;
        cout << "Antalet deltagare: " << antal << endl;
        cout << "Programmet avslutas" << endl;
    }
    
    else {
        
        // Om inga tävlande
        cout << "Inga tävlande" << endl;
        cout << "Programmet avslutas" << endl;
    }

  return 0;
}
