#include <iostream>
#include "Towar.h"
#include "Klient.h"

using namespace std;

///////////////KLASA BAZOWA//////////////////////////////////////////////
Klient::Klient(const string &imie, int budzet, int x, int y) : imie(imie), budzet(budzet), x(x), y(y) {};

//wypisywanie
ostream &operator<<(ostream &os, const Klient &klient) {
    os << "imie: " << klient.imie << " budzet: " << klient.budzet << " x: " << klient.x << " y: " << klient.y
       << " mam prezent: " << klient.mamPrezent << endl;
    return os;
}

int Klient::dajBudzet() const {
    return budzet;
}

void Klient::JuzMamPrezent() {
    this->mamPrezent = true;
};


bool Klient::CzyMamPrezent() const {
    return mamPrezent;
}

///////////////MAKSYMALISTA////////////////////////////////////////////////////////////////////////////
Maksymalista::Maksymalista(string imie, int budzet, int x, int y) : Klient(imie, budzet, x, y) {};


void Maksymalista::zakup(ObiektHandlowy &placowka) {
    //na początku sprawdzamy czy klient jeszcze nie kupił prezentu
    if (this->CzyMamPrezent()) {cout << "Już masz prezent" << endl; return;}
    //bierzemy najdrozszy prezent w budzecie(tutaj transakcja dzieje się internetowo - dla Klienta sklep to to samo co siec)
    Towar *temp = placowka.NajdrozszyWBudzecie(this->dajBudzet());
    //jezeli dostalismy nullptr to znaczy, że nie udalo się nic znalezc w budzecie
    if (temp != nullptr) {
        this->JuzMamPrezent();
        temp->zmienIlosc(-1);
    }
};

///////////////MINIMALISTA/////////////////////////////////////////////
Minimalista::Minimalista(string imie, int budzet, int x, int y) : Klient(imie, budzet, x, y) {};

void Minimalista::zakup(ObiektHandlowy &placowka) {
    if (this->CzyMamPrezent()) {cout << "Już masz prezent" << endl; return;}
    Towar *temp = placowka.NajtanszyTowar(this->dajBudzet());
    if (temp != nullptr){
        this->JuzMamPrezent();
        temp->zmienIlosc(-1);
    }
};

///////////////LOSOWY//////////////////////////////////////////////////
Losowy::Losowy(string imie, int budzet, int x, int y) : Klient(imie, budzet, x, y) {};

void Losowy::zakup(ObiektHandlowy &placowka) {
    if (this->CzyMamPrezent()) {cout << "Już masz prezent" << endl; return;}
    for (int i = 0; i < 3; i++) {
        Towar *temp = placowka.LosowyTowar(this->dajBudzet());
        if (temp != nullptr) {
            this->JuzMamPrezent();
            temp->zmienIlosc(-1);
            return;
        }
    }
}
///////////////TRADYCJONALISTA///////////////////////////////////////////
Tradycjonalista::Tradycjonalista(string imie, int budzet, int x, int y, string szukanyProdukt) : Klient(imie, budzet, x, y), szukanyProdukt(szukanyProdukt) {};
const string &Tradycjonalista::dajSzukanyProdukt() const {
    return szukanyProdukt;
}
void Tradycjonalista::zakup(Miasto &miasto) {
    if (miasto.dajSklepy().empty() || this->CzyMamPrezent()) {cout << "Transakcja nieudana, albo nie ma już sklepów albo już masz prezent" << endl; return;}

}


