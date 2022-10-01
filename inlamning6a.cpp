//
//  main.cpp
//  inlamning6_a
//
//  Created by Louise Kanizsai Ståhl on 2022-08-11.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_PERSONER = 10;
const int MAX_TRANSAKTIONER = 30;

//--------------------------------------------------
//------------- Klassdeklarationer:

class Transaktion // Ett enda kvitto
{
    private:
        string datum;
        string typ; // transaktionstyp
        string namn; // den som betalade
        double belopp; // vad den betalade
        int    antal_kompisar; // hur många den betalade för (ej inkl sig själv)
        string kompisar[MAX_PERSONER]; // array med antal_kompisar st element inlagda

    public:
        Transaktion();
        ~Transaktion();
        string hamtaNamn();
        double hamtaBelopp();
        int    hamtaAntalKompisar();
        bool   finnsKompis(const string &namnet); // letar igenom arrayen kompisar, return true om namnet finns, annars false
        bool   lasIn(istream &is); // läser data om en transaktion (kvitto) från tangentbord eller en fil
        void   skrivUt(ostream &os); // skriver ut data om en transaktion
        void   skrivTitel(ostream &os); //skriver ut titeln som beskriver vad som står i kolonner för metoden skrivUt
 };

class Person
{
    private:
        string namn;
        double betalat_andras; // ligger ute med totalt
        double skyldig;        // skyldig totalt

    public:
        Person();
        Person(string innamn, double inbetalat_andras, double inskyldig);
        string hamtaNamn();
        double hamtaBetalat();
        double hamtaSkyldig();
        void   skrivUt();
};

class PersonLista
{
    private:
        int    antal_personer;
        Person personer[MAX_PERSONER];

    public:
        PersonLista();
        ~PersonLista();
        void   laggTill(Person ny_person); // tar ett personobjekt som inparameter, ny_person, och lägger till i arrayen personer, efter den sista personen
        void   skrivUtOchFixa(); // skriver ut information om varje personobjekt i arrayen personer + kollar att allt gick jämnt ut
        double summaSkyldig();
        double summaBetalat();
        bool   finnsPerson(const string& namn); // returnerar sant om "namn" finns bland personerna i listan (undviker dubletter)
 };

class TransaktionsLista
{
    private:
        int         antal_transaktioner;
        Transaktion transaktioner[MAX_TRANSAKTIONER]; // antal_transaktioner st element inlagda

    public:
        TransaktionsLista();
        ~TransaktionsLista();
        void   lasIn(istream & is); //lasIn och skrivUt läser in värden till ett TransaktionsLista-objekt från/till fil eller tangentbord/skärm. Använder sig av inläsnings- och utskriftsmetoder i klassen Transaktion.
        void   skrivUt(ostream & os);
        void   laggTill(Transaktion & t); //lägga till ett nytt transaktionsobjekt sist i arrayen transaktioner
        double totalKostnad(); // beräknar och returnerar summan av alla utgifter på resan
        double liggerUteMed(const string &namnet); // räknar ut hur mycket en viss person, dvs med namnet namnet har betalat för andra personer (ta bort sig själv)
        double arSkyldig(const string &namnet); // räknar ut hur mycket en viss person, dvs med namnet namnet är skyldig andra
        PersonLista FixaPersoner(); // skapa och returnera ett objekt av typen PersonLista. Skapa unika personobjekt med info om alla personer (namn, vad de betalat samt vad de är skyldiga)
 };

//--------------------------------------------------
//------------- Huvudprogram:

int main() {
    
    cout << "Startar med att läsa från en fil." << endl;

        TransaktionsLista transaktioner;
        ifstream is("resa.txt");
        transaktioner.lasIn(is);

        int operation = 1;
        while (operation != 0)
        {
            cout << endl;
            cout << "Välj i menyn nedan:" << endl;
            cout << "0. Avsluta. Alla transaktioner sparas på fil." << endl;
            cout << "1. Skriv ut information om alla transaktioner." << endl;
            cout << "2. Läs in en transaktion från tangentbordet." << endl;
            cout << "3. Beräkna totala kostnaden." << endl;
            cout << "4. Hur mycket ärr en viss person skyldig?" << endl;
            cout << "5. Hur mycket ligger en viss person ute med?" << endl;
            cout << "6. Lista alla personer mm och FIXA" << endl;

            cin >> operation;
            cout << endl;

            switch (operation)
            {
                case 1:
                {
                    transaktioner.skrivUt(cout);
                    break;
                }
                case 2:
                {
                    Transaktion transaktion;
                    cout << "Ange transaktion i följande format" << endl;
                    transaktion.skrivTitel(cout);
                    transaktion.lasIn(cin);
                    transaktioner.laggTill(transaktion);
                    break;
                }
                case 3:
                {
                    cout << "Den totala kostnanden för resan var "
                       << transaktioner.totalKostnad() << endl;
                    break;
                }
                case 4:
                {
                    cout << "Ange personen: ";
                    string namn;
                    cin >> namn;
                    double ar_skyldig = transaktioner.arSkyldig(namn);
                    if (ar_skyldig == 0.)
                        cout << "Kan inte hitta personen " << namn << endl;
                    else
                        cout << namn << " är skyldig " << ar_skyldig << endl;
                    break;
                }
                case 5:
                {
                    cout << "Ange personen: ";
                    string namn;
                    cin >> namn;
                    double ligger_ute_med = transaktioner.liggerUteMed(namn);
                    if (ligger_ute_med == 0.)
                        cout << "Kan inte hitta personen " << namn << endl;
                    else
                        cout << namn << " ligger ute med " << ligger_ute_med << endl;
                    break;
                }
                case 6:
                {
                    cout << "Nu skapar vi en personarray och reder ut det hela!" << endl;
                    PersonLista lista = transaktioner.FixaPersoner();
                    lista.skrivUtOchFixa();
                    break;
                }
            }
        }

        std::ofstream os("transaktioner.txt");
        transaktioner.skrivUt(os);

        return 0;
}

//--------------------------------------------------
//------------- Implementation av klassmetoder:

//------------- KLASSEN TRANSAKTION: -------------
// Standardkonstruktor
Transaktion::Transaktion()
{
    datum = " ";
    typ = " ";
    namn = " ";
    belopp = 0.0;
    antal_kompisar = 0;
}

//Destuktor
Transaktion::~Transaktion()
{}

// Metoder + Selektorer:

string Transaktion::hamtaNamn()
{
    return namn;
}

double Transaktion::hamtaBelopp()
{
    return belopp;
}

int Transaktion::hamtaAntalKompisar()
{
    return antal_kompisar;
}

bool Transaktion::finnsKompis(const string &namnet)
{
    for (int i = 0; i < antal_kompisar; i++)
    {
        if (kompisar[i] == namnet)
            return true;
    }
    return false;
}

bool Transaktion::lasIn(istream &is)
{
    is >> datum >> typ >> namn >> belopp >> antal_kompisar;
    
    for (int i = 0; i < antal_kompisar; i++)
        is >> kompisar[i];
    
    return !is.eof(); // returnerar true om filen inte är slut
}

void Transaktion::skrivUt(ostream &os)
{
    os << datum << "\t" << typ << "\t" << namn << "\t" << belopp << "\t" << antal_kompisar << "\t";
    
    for (int i = 0; i < antal_kompisar; i++)
        os << kompisar[i] << "\t";
    os << endl;
}

void Transaktion::skrivTitel(ostream &os)
{
    os << "Datum " << "Typ " << "Namn " << "Belopp " << "Antal och lista av kompisar" << endl;
}

//------------- KLASSEN PERSON: -------------
//Standardkonstruktor
Person::Person()
{
    namn = " ";
    betalat_andras = 0.0;
    skyldig = 0.0;
}

// Överlagrad konstruktor
Person::Person(string innamn, double inbetalat_andras, double inskyldig)
{
    namn = innamn;
    betalat_andras = inbetalat_andras;
    skyldig = inskyldig;
}

// Metoder + selektorer:

string Person::hamtaNamn()
{
    return namn;
}

double Person::hamtaBetalat()
{
    return betalat_andras;
}

double Person::hamtaSkyldig()
{
    return skyldig;
}

void Person::skrivUt()
{
    // Om personen betalat mer än den är skyldig = ta från potten, annars ge till potten
    if (betalat_andras > skyldig)
        cout << namn << " ligger ute med " << betalat_andras << " och är skyldig " << skyldig << ". Skall ha " << (betalat_andras - skyldig) << " från potten!" << endl;
    else
        cout << namn << " ligger ute med " << betalat_andras << " och är skyldig " << skyldig << ". Skall ge " << (skyldig - betalat_andras) << " till potten!" << endl;
}

//------------- KLASSEN PERSONLISTA: -------------
// Standardkonstruktor
PersonLista::PersonLista()
{
    antal_personer = 0;
}

// Destruktor
PersonLista::~PersonLista()
{}

// Metoder + selektorer:

void PersonLista::laggTill(Person ny_person)
{
    // tar personobjektet ny_person, och lägger till sist i arrayen personer
    
    personer[antal_personer] = ny_person;
    antal_personer++;
}

void PersonLista::skrivUtOchFixa()
{
    for (int i = 0; i < antal_personer; i++)
        personer[i].skrivUt();
    
    // Kolla att det går jämnt ut (går inte att jämföra dem med exakt noll, men vi antar att om skillnaden är mindre än 0.01 så är det tillräckligt nära noll):
    if (summaBetalat() - summaSkyldig() < 0.01)
        cout << "Allt går jämnt ut. " << endl;
    else
        cout << "Någon uträkning blev fel någonstans... " << endl;
}

double PersonLista::summaSkyldig()
{
    double summaskyldig = 0.0;
    
    for (int i = 0; i < antal_personer; i++)
        summaskyldig += personer[i].hamtaSkyldig();
    
    return summaskyldig;
}

double PersonLista::summaBetalat()
{
    double summabetalat = 0.0;
    
    for (int i = 0; i < antal_personer; i++)
        summabetalat += personer[i].hamtaBetalat();
    
    return summabetalat;
}

bool PersonLista::finnsPerson(const string& namn)
{
    // loop med if-sats: returnerar true om namnet i inparametern hittas i aktuellt index i personer
    
    for (int i = 0; i < antal_personer; i++)
    {
        if (personer[i].hamtaNamn() == namn)
            return true;
    }
    return false;
}

//------------- KLASSEN TRANSAKTIONSLISTA: -------------
// Standardkonstruktor
TransaktionsLista::TransaktionsLista()
{
    antal_transaktioner = 0;
}

// Destruktor
TransaktionsLista::~TransaktionsLista()
{}

// Metoder + selektorer:

void TransaktionsLista::lasIn(istream & is)
{
    // En inläsningsmetod i klassen TransaktionsLista.
      Transaktion t;
      
      // Så länge det går bra att läsa (filen ej slut)
      while (t.lasIn(is))
      {
           laggTill( t );
      }
}

void TransaktionsLista::skrivUt(ostream & os)
{
    cout << "Antal trans = " << antal_transaktioner << endl;
    
    Transaktion temp;
    temp.skrivTitel(os);
    
    for (int i = 0; i < antal_transaktioner; i++)
        transaktioner[i].skrivUt(os);
}

void TransaktionsLista::laggTill(Transaktion & t)
{
    // lägger till ett nytt transaktionsobjekt sist i arrayen transaktioner
    
    transaktioner[antal_transaktioner] = t;
    antal_transaktioner++;
}

double TransaktionsLista::totalKostnad()
{
    double totalsumma = 0.0;
    
    for (int i = 0; i < antal_transaktioner; i++)
        totalsumma += transaktioner[i].hamtaBelopp();
    return totalsumma;
}

double TransaktionsLista::liggerUteMed(const string &namnet)
{
    double summa = 0.0;
    
    for (int i = 0; i < antal_transaktioner; i++)
        if (transaktioner[i].hamtaNamn() == namnet)
            summa += transaktioner[i].hamtaBelopp() *
                (1.0 - 1.0 / (transaktioner[i].hamtaAntalKompisar() + 1));
    
    return summa;
 }

double TransaktionsLista::arSkyldig(const string &namnet)
{
    double summaskyldig = 0.0;
    
    for (int i = 0; i < antal_transaktioner; i++)
        // belopp delas med antalkompisar + 1 (andelen av personen av transaktionen)
        if (transaktioner[i].finnsKompis(namnet))
            summaskyldig += transaktioner[i].hamtaBelopp()/ (transaktioner[i].hamtaAntalKompisar() + 1);
    
    return summaskyldig;
}

PersonLista TransaktionsLista::FixaPersoner()
{
    // nytt objekt (PersonLista)
    PersonLista plista;
    string pnamn;
    double pbetalat;
    double pskyldig;
    
    // loop som går igenom alla transaktioner, innehåller if-sats som letar efter unika namn
    for (int i = 0; i < antal_transaktioner; i++)
    {
        if (plista.finnsPerson(transaktioner[i].hamtaNamn()) == false) // om personen (namnet) inte redan finns: lägg till ny person med aktuella attribut (namn, vad den betalat, vad den är skyldig)
        {
            pnamn = transaktioner[i].hamtaNamn();
            pbetalat = liggerUteMed(pnamn);
            pskyldig = arSkyldig(pnamn);
            Person p(pnamn, pbetalat, pskyldig);
            plista.laggTill(p);
        }
    }
    return plista;
}
//--------------------------------------------------
