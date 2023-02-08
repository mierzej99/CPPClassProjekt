#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Sklep.h"

using namespace std;

//konstruktor
Sklep::Sklep(string nazwa, vector<Towar *> towary, int x, int y, Siec *siec) : ObiektHandlowy(nazwa), x(x), y(y),
                                                                               towary(towary), siec(siec) {};

//destruktor
Sklep::~Sklep() {
    for (Towar *t: towary) {
        delete t;
    }
    delete siec;
}

//strumień
ostream &operator<<(ostream &os, const Sklep &sklep) {
    os << "nazwa: " << sklep.nazwa << ", siec: " << sklep.siec << endl;
    for (int i = 0; i < sklep.towary.size(); i++) cout << " towar " << i << ": " << *(sklep.towary[i]) << endl;
    return os;
};

//funkcje
void Sklep::ustawSiec(Siec *siec) {
    this->siec = siec;
}

const vector<Towar *> &Sklep::pokazTowary() {
    return towary;
}

Siec *Sklep::pokazSiec() {
    return siec;
}

void Sklep::odejdzZSieci(Siec *siec) {
    if (this->siec == nullptr) cout << "Ten sklep już jest niezrzeszony" << endl;
    else {
        (this->siec)->usunSklepzSieci(this);
        this->siec = nullptr;
    }
};

Towar *Sklep::NajdrozszyWBudzecie(int budzet) {
    int max = 0;
    Towar *maksymalnyProdukt = nullptr;
    for (Towar *towar: this->pokazTowary()) {
        if (towar->dajIlosc() > 0 && towar->dajCene() <= budzet && towar->dajCene() > max) {
            max = towar->dajCene();
            maksymalnyProdukt = towar;
        }
        //idziemy po wszystkich towarach które mają ilość > 0 w sklepie i szukamy najdrozszego na ktory nas stac
    }
    return maksymalnyProdukt;

};

Towar *Sklep::NajtanszyTowar(int budzet) {
    int min = budzet + 1;
    Towar *minimalnyProdukt = nullptr;
    for (Towar *towar: this->pokazTowary()) {
        if (towar->dajIlosc() > 0 && towar->dajCene() < min) {
            min = towar->dajCene();
            minimalnyProdukt = towar;
        }
        //idziemy po wszystkich towarach które mają ilość > 0 w sklepie i szukamy najtanszego towaru
    }
    return minimalnyProdukt;

}

Towar *Sklep::LosowyTowar(int budzet) {
    if (this->pokazTowary().empty()) return nullptr;
    srand( time( NULL ) );
    int losowyIndeks = rand() % this->pokazTowary().size();
    Towar *temp = this->pokazTowary()[losowyIndeks];
    if (temp->dajCene() <= budzet) return temp;
    else return nullptr;
}

Towar *Sklep::KonkretnyTowar(string nazwa) {
    Towar *szukanyTowar = nullptr;
    for (Towar *towar : this->pokazTowary()){
        if (towar->dajNazwe() == nazwa) szukanyTowar = towar;
    }
    return szukanyTowar;
};

