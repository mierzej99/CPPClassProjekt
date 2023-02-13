#include <iostream>
#include <random>
#include "Towar.h"
#include "Klient.h"

using namespace std;

///////////////KLASA BAZOWA//////////////////////////////////////////////
Klient::Klient(const string &imie, int budzet, int x, int y) : imie(imie), budzet(budzet), x(x), y(y) {};

//wypisywanie
ostream &operator<<(ostream &os, const Klient &klient) {
    klient.wypisz(os);
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

void Klient::ustawMiasto(Miasto *miasto) {
    this->miasto = miasto;
}

void Klient::wypisz(ostream &os) const {
    os << "imie: " << this->imie << " budzet: " << this->budzet << " x: " << this->x << " y: " << this->y
       << " mam prezent: " << this->mamPrezent;
}

void Klient::przelew(double budzet) {
    this->budzet += budzet;
}

///////////////MAKSYMALISTA////////////////////////////////////////////////////////////////////////////
Maksymalista::Maksymalista(string imie, int budzet, int x, int y) : Klient(imie, budzet, x, y) {};


void Maksymalista::zakup(Miasto &miasto) {
    //losowo wybieram placowke (strone internetowa) do (na) ktorej wejdzie klient
    int losowyIndeks = rand() % miasto.dajSklepy().size();
    ObiektHandlowy *placowka = miasto.dajSklepy()[losowyIndeks];
    //na początku sprawdzamy czy klient jeszcze nie kupił prezentu
    if (this->CzyMamPrezent()) {
        cout << "Już masz prezent" << endl;
        return;
    }
    //bierzemy najdrozszy prezent w budzecie(tutaj transakcja dzieje się internetowo - dla Klienta sklep to to samo co siec)
    Towar *tempTowar = placowka->NajdrozszyWBudzecie(this->dajBudzet());
    //jezeli dostalismy nullptr to znaczy, że nie udalo się nic znalezc w budzecie
    if (tempTowar != nullptr) {
        this->JuzMamPrezent();
        tempTowar->zmienIlosc(-1);
        this->przelew(-tempTowar->dajCene());
        placowka->przelew(tempTowar->dajCene(), tempTowar->dajSklep());
    }
};

///////////////MINIMALISTA/////////////////////////////////////////////
Minimalista::Minimalista(string imie, int budzet, int x, int y) : Klient(imie, budzet, x, y) {};

void Minimalista::zakup(Miasto &miasto) {
    //losowo wybieram placowke (strone internetowa) do (na) ktorej wejdzie klient
    int losowyIndeks = rand() % miasto.dajSklepy().size();
    ObiektHandlowy *placowka = miasto.dajSklepy()[losowyIndeks];
    if (this->CzyMamPrezent()) {
        cout << "Już masz prezent" << endl;
        return;
    }
    Towar *tempTowar = placowka->NajtanszyTowar(this->dajBudzet());
    if (tempTowar != nullptr) {
        this->JuzMamPrezent();
        tempTowar->zmienIlosc(-1);
        this->przelew(-tempTowar->dajCene());
        placowka->przelew(tempTowar->dajCene(), tempTowar->dajSklep());
    }
};

///////////////LOSOWY//////////////////////////////////////////////////
Losowy::Losowy(string imie, int budzet, int x, int y) : Klient(imie, budzet, x, y) {};

void Losowy::zakup(Miasto &miasto) {
    //losowo wybieram placowke (strone internetowa) do (na) ktorej wejdzie klient
    int losowyIndeks = rand() % miasto.dajSklepy().size();
    ObiektHandlowy *placowka = miasto.dajSklepy()[losowyIndeks];
    if (this->CzyMamPrezent()) {
        cout << "Już masz prezent" << endl;
        return;
    }
    Towar *tempTowar = nullptr;
    for (int i = 0; i < 3; i++) {
        tempTowar = placowka->LosowyTowar(this->dajBudzet());
        if (tempTowar != nullptr) {
            this->JuzMamPrezent();
            tempTowar->zmienIlosc(-1);
            this->przelew(-tempTowar->dajCene());
            placowka->przelew(tempTowar->dajCene(), tempTowar->dajSklep());
            return;
        }
    }
}

///////////////OSZCZĘDNY/////////////////////////////////////////////////
Oszczedny::Oszczedny(string imie, int budzet, int x, int y, const string &szukanyProdukt) : Klient(imie, budzet, x, y),
                                                                                            szukanyProdukt(
                                                                                                    szukanyProdukt) {};

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
    ObiektHandlowy *placowka = nullptr;
    for (ObiektHandlowy *sklep: miasto.dajSklepy()) {
        tempTowar = sklep->NajtanszyKonkretnyTowar(this->dajSzukanyProdukt(), this->dajBudzet());
        if (tempTowar != nullptr && tempTowar->dajCene() < min_cena) {szukanyTowar = tempTowar; placowka = sklep;}
    }
    if (szukanyTowar != nullptr && szukanyTowar->dajCene() <= this->dajBudzet()) {
        this->JuzMamPrezent();
        szukanyTowar->zmienIlosc(-1);
        this->przelew(-szukanyTowar->dajCene());
        placowka->przelew(tempTowar->dajCene(), tempTowar->dajSklep());
    }
}

void Oszczedny::wypisz(ostream &os) const {
    Klient::wypisz(os);
    os << ", Szukam produktu: " << this->dajSzukanyProdukt();
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

        if (tempSklep != nullptr && tempSklep->OdlegloscOdPunktu(this->dajX(), this->dajY()) < min_odl) {
            sklepZSzukanymTowarem = tempSklep;
            min_odl = tempSklep->OdlegloscOdPunktu(this->dajX(), this->dajY());
        }
    }
    if (sklepZSzukanymTowarem != nullptr) {
        this->JuzMamPrezent();
        Towar *tempTowar = sklepZSzukanymTowarem->KonkretnyTowar(this->dajSzukanyProdukt(), this->dajBudzet());
        tempTowar->zmienIlosc(-1);
        this->przelew(-tempTowar->dajCene());
        sklepZSzukanymTowarem->przelew(tempTowar->dajCene(), tempTowar->dajSklep());
    }

}

void Tradycjonalista::wypisz(ostream &os) const {
    Klient::wypisz(os);
    os << ", Szukam produktu: " << this->dajSzukanyProdukt();
}



