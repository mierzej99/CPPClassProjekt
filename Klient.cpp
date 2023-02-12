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

int Klient::dajX() const {
    return x;
}

int Klient::dajY() const {
    return y;
}

///////////////MAKSYMALISTA////////////////////////////////////////////////////////////////////////////
Maksymalista::Maksymalista(string imie, int budzet, int x, int y) : Klient(imie, budzet, x, y) {};


void Maksymalista::zakup(ObiektHandlowy &placowka) {
    //na początku sprawdzamy czy klient jeszcze nie kupił prezentu
    if (this->CzyMamPrezent()) {
        cout << "Już masz prezent" << endl;
        return;
    }
    //bierzemy najdrozszy prezent w budzecie(tutaj transakcja dzieje się internetowo - dla Klienta sklep to to samo co siec)
    Towar *tempTowar = placowka.NajdrozszyWBudzecie(this->dajBudzet());
    //jezeli dostalismy nullptr to znaczy, że nie udalo się nic znalezc w budzecie
    if (tempTowar != nullptr) {
        this->JuzMamPrezent();
        tempTowar->zmienIlosc(-1);
    }
};

///////////////MINIMALISTA/////////////////////////////////////////////
Minimalista::Minimalista(string imie, int budzet, int x, int y) : Klient(imie, budzet, x, y) {};

void Minimalista::zakup(ObiektHandlowy &placowka) {
    if (this->CzyMamPrezent()) {
        cout << "Już masz prezent" << endl;
        return;
    }
    Towar *tempTowar = placowka.NajtanszyTowar(this->dajBudzet());
    if (tempTowar != nullptr) {
        this->JuzMamPrezent();
        tempTowar->zmienIlosc(-1);
    }
};

///////////////LOSOWY//////////////////////////////////////////////////
Losowy::Losowy(string imie, int budzet, int x, int y) : Klient(imie, budzet, x, y) {};

void Losowy::zakup(ObiektHandlowy &placowka) {
    if (this->CzyMamPrezent()) {
        cout << "Już masz prezent" << endl;
        return;
    }
    Towar *tempTowar = nullptr;
    for (int i = 0; i < 3; i++) {
        tempTowar = placowka.LosowyTowar(this->dajBudzet());
        if (tempTowar != nullptr) {
            this->JuzMamPrezent();
            tempTowar->zmienIlosc(-1);
            return;
        }
    }
}


///////////////OSZCZĘDNY/////////////////////////////////////////////////
Oszczedny::Oszczedny(string imie, int budzet, int x, int y) : Klient(imie, budzet, x, y) {};

const string &Oszczedny::dajSzukanyProdukt() const {
    return szukanyProdukt;
}

void Oszczedny::zakup(Miasto &miasto) {
    //najpierw sprawdzam czy są jakieś sklepy i czy klient potrzebuje prezentu.
    if (miasto.dajSklepy().empty() || this->CzyMamPrezent()) {
        cout << "Transakcja nieudana, albo nie ma już sklepów albo już masz prezent" << endl;
        return;
    }
    int min_cena = 100000; //TODO: zrobić mądrzej
    Towar *szukanyTowar = nullptr, *tempTowar = nullptr;
    for (ObiektHandlowy *sklep: miasto.dajSklepy()) {
        tempTowar = sklep->NajtanszyKonkretnyTowar(this->dajSzukanyProdukt());
        if (tempTowar != nullptr && tempTowar->dajCene() < min_cena) szukanyTowar = tempTowar;
    }
    if (szukanyTowar != nullptr && szukanyTowar->dajCene() <= this->dajBudzet()) {
        this->JuzMamPrezent();
        szukanyTowar->zmienIlosc(-1);
    }
}


///////////////TRADYCJONALISTA///////////////////////////////////////////
Tradycjonalista::Tradycjonalista(const string &imie, int budzet, int x, int y, const string &szukanyProdukt) : Klient(
        imie, budzet, x, y), szukanyProdukt(szukanyProdukt) {};

const string &Tradycjonalista::dajSzukanyProdukt() const {
    return szukanyProdukt;
}

void Tradycjonalista::zakup(Miasto &miasto) {
    //najpierw sprawdzam czy są jakieś sklepy i czy klient potrzebuje prezentu.
    if (miasto.dajSklepy().empty() || this->CzyMamPrezent()) {
        cout << "Transakcja nieudana, albo nie ma już sklepów albo już masz prezent" << endl;
        return;
    }
    int min_odl = 1000000; //TODO: zrobić mądrzej min
    ObiektHandlowy *sklepZSzukanymTowarem = nullptr, *tempSklep = nullptr;
    //bierzemy od miasta listę sklepów (w tym też sieci sklepów)i szukamy najbliższego z dostępnym towarem.
    for (ObiektHandlowy *sklep: miasto.dajSklepy()) {
        tempSklep = sklep->NajblizszySklepZKonkretnymTowarem(this->dajSzukanyProdukt(), this->dajX(), this->dajY(),
                                                             this->dajBudzet());
        if (tempSklep != nullptr && tempSklep->OdlegloscOdPunktu(this->dajX(), this->dajY()) < min_odl) sklepZSzukanymTowarem = tempSklep;
    }
    if (sklepZSzukanymTowarem != nullptr){
        this->JuzMamPrezent();
        sklepZSzukanymTowarem->KonkretnyTowar(this->dajSzukanyProdukt(), this->dajBudzet())->zmienIlosc(-1);
    }

}



