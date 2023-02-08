#include "Towar.h"

using namespace std;

//konstrukotr
Towar::Towar(const string &nazwa, int cena, int ilosc) : nazwa(nazwa), cena(cena), ilosc(ilosc) {};


//kopiowanie towaru
Towar::Towar(const Towar &innyTowar) {
    nazwa = innyTowar.nazwa;
    cena = innyTowar.cena;
    ilosc = innyTowar.ilosc;
};

Towar& Towar::operator=(const Towar &innyTowar) {
    nazwa = innyTowar.nazwa;
    cena = innyTowar.cena;
    ilosc = innyTowar.ilosc;
    return *this;
};


ostream& operator<<(ostream &os, const Towar &towar) {
    os << "nazwa: " << towar.nazwa << " cena: " << towar.cena << " ilosc: " << towar.ilosc;
    return os;
};

//funkcje
void Towar::zmienCene(int cena) {
    if (cena > 0) this->cena = cena;
    else cerr << "Nie można ustawić niedodatniej ceny." << endl;
}

void Towar::zmienIlosc(int ilosc) {
    if (this->ilosc+ilosc >= 0) this->ilosc += ilosc;
    else cerr << "Nie można ustawić ujemnego stanu magazynowego." << endl;
}

int Towar::dajCene() const {
    return cena;
}

int Towar::dajIlosc() const {
    return ilosc;
}

const string &Towar::dajNazwe() const {
    return nazwa;
};
