#include <iostream>
#include <algorithm>
#include <vector>
#include "Siec.h"

//konstruktor
Siec::Siec(string nazwa, int marza, vector<Sklep *> sklepy) : ObiektHandlowy(nazwa), marza(marza), sklepy(sklepy) {
    for (int i = 0; i < sklepy.size(); i++) {
        sklepy[i]->ustawSiec(this);
    }
};

ostream &operator<<(ostream &os, const Siec &siec) {
    os << "nazwa: " << siec.nazwa << " marza: " << siec.marza << endl;
    for (int i = 0; i < siec.sklepy.size(); i++) cout << " sklep " << i << ": " << *(siec.sklepy[i]) << endl;
    return os;
}


void Siec::usunSklepzSieci(const Sklep *sklep) {
    this->sklepy.erase(remove(this->sklepy.begin(), this->sklepy.end(), sklep), this->sklepy.end());
};

const vector<Sklep *> &Siec::pokazSklepy() {
    return sklepy;
};


Siec::~Siec() {
    for (Sklep *sklep: sklepy)
        delete sklep;
}

Towar *Siec::NajdrozszyWBudzecie(int budzet) {
    int max = 0;
    Towar *maksymalnyProdukt = nullptr, *temp = nullptr;

    for (Sklep *sklep: this->pokazSklepy()) {
        temp = sklep->NajdrozszyWBudzecie(budzet);
        if (temp != nullptr && temp->dajCene() > max) {
            max = temp->dajCene();
            maksymalnyProdukt = temp;
        }
        //idziemy po wszystkich sklepach
    }
    return maksymalnyProdukt;

}

Towar *Siec::NajtanszyTowar(int budzet) {
    int min = budzet + 1;
    Towar *minimalnyProdukt = nullptr, *temp = nullptr;

    for (Sklep *sklep: this->pokazSklepy()) {
        temp = sklep->NajtanszyTowar(budzet);
        if (temp != nullptr && temp->dajCene() < min) {
            min = temp->dajCene();
            minimalnyProdukt = temp;
        }
        //idziemy po wszystkich sklepach
    }
    return minimalnyProdukt;
}

Towar *Siec::LosowyTowar(int budzet) {
    if (this->pokazSklepy().empty()) return nullptr;
    srand(time(NULL));
    int losowyIndeks = rand() % this->pokazSklepy().size();
    return this->pokazSklepy()[losowyIndeks]->LosowyTowar(budzet);
}

Towar *Siec::NajtanszyKonkretnyTowar(string nazwa, int budzet) {
    Towar *szukanyTowar = nullptr, *tempTowar = nullptr;
    int min_cena = 10000; //TODO: mądrzej zrobić min
    for (Sklep *sklep: this->pokazSklepy()) {
        tempTowar = sklep->NajtanszyKonkretnyTowar(nazwa, budzet);
        if (tempTowar != nullptr && tempTowar->dajCene() < min_cena) szukanyTowar = tempTowar;
    }
    return szukanyTowar;
}


ObiektHandlowy *Siec::NajblizszySklepZKonkretnymTowarem(string nazwa, int x_klienta, int y_klienta, int budzet) {
    Sklep *szukanySklep = nullptr, *tempSklep = nullptr;
    double min_odl = 100000; //TODO:mądrzej
    for (Sklep *sklep: this->pokazSklepy()) {
        if (sklep->NajblizszySklepZKonkretnymTowarem(nazwa, x_klienta, y_klienta, budzet) != nullptr &&
            sklep->OdlegloscOdPunktu(x_klienta, y_klienta) < min_odl &&
            sklep->KonkretnyTowar(nazwa, budzet)->dajCene() <= budzet) { // jezeli w sieci bede dwa sklepy tak samo blisko ale w jednym cenia bedzie za wysoka to slabo
            szukanySklep = tempSklep;
        }
    }
    return  szukanySklep;
}
