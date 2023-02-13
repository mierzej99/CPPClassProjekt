//
// Created by michalmierzejewski on 2/8/23.
//
#include <cmath>
#include <vector>
#include <algorithm>
#include "ObiektHandlowy.h"
using namespace std;
ObiektHandlowy::ObiektHandlowy(string nazwa) : nazwa(nazwa){}

void ObiektHandlowy::ustawMiasto(Miasto *miasto) {
    this->miasto = miasto;
}

Miasto *ObiektHandlowy::dajMiasto() const {
    return miasto;
}

ostream &operator<<(ostream &os, const ObiektHandlowy &handlowy) {
    handlowy.wypisz(os);
    return os;
}

const string &ObiektHandlowy::dajNazwe() const {
    return nazwa;
}



///////////////PODKLASY/////////////////////////////////
//////////////SKLEP////////////////////////////////////
//konstruktor
Sklep::Sklep(string nazwa, vector<Towar *> towary, int x, int y, Siec *siec) : ObiektHandlowy(nazwa), x(x), y(y),
                                                                               towary(towary), siec(siec) {
    for(Towar *towar : towary){
        towar->ustawSklep(this);
    }
};

//destruktor
Sklep::~Sklep() {
    for (Towar *t: towary) {
        delete t;
    }
    //delete siec; // to byłby błąd - podwójne usuwanie
}


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
    if (temp->dajCene() <= budzet && temp->dajIlosc() > 0) return temp;
    else return nullptr;
}

Towar *Sklep::KonkretnyTowar(string nazwa, int budzet) {
    Towar *szukanyTowar = nullptr;
    for (Towar *towar : this->pokazTowary()){
        if (towar->dajNazwe() == nazwa && towar->dajIlosc() > 0 && towar->dajCene() <= budzet) {szukanyTowar = towar;}
    }
    return szukanyTowar;
}

Towar *Sklep::NajtanszyKonkretnyTowar(string nazwa, int budzet) {
    return this->KonkretnyTowar(nazwa, budzet);
}

double Sklep::OdlegloscOdPunktu(int x, int y) {
    return sqrt(pow(this->dajX()-x,2) + pow(this->dajY()-y,2));
}

int Sklep::dajX() const {
    return x;
}

int Sklep::dajY() const {
    return y;
}

ObiektHandlowy *Sklep::NajblizszySklepZKonkretnymTowarem(string nazwa, int x_klienta, int y_klienta, int budzet) {
    if(this->KonkretnyTowar(nazwa, budzet) != nullptr) return this;
    else return nullptr;
}

void Sklep::wypisz(ostream &os) const {
    os << "nazwa Sklepu: " << this->nazwa << ", siec: " << this->siec->dajNazwe() << ", saldo: " << this->saldo << endl;
    for (int i = 0; i < this->towary.size(); i++) cout << " towar " << i << ": " << *(this->towary[i]) << endl;
}

void Sklep::przelew(double kwota, Sklep* sklep) {
    this->saldo += kwota;
}

////////////SIEĆ///////////////////////////////////////
//konstruktor
Siec::Siec(string nazwa, double marza, vector<Sklep *> sklepy) : ObiektHandlowy(nazwa), marza(marza), sklepy(sklepy) {
    for (int i = 0; i < sklepy.size(); i++) {
        sklepy[i]->ustawSiec(this);
    }
};



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
    double min_odl = 100000; //TODO: mądrzej
    for (Sklep *sklep: this->pokazSklepy()) {
        if (sklep->NajblizszySklepZKonkretnymTowarem(nazwa, x_klienta, y_klienta, budzet) != nullptr &&
            sklep->OdlegloscOdPunktu(x_klienta, y_klienta) < min_odl &&
            sklep->KonkretnyTowar(nazwa, budzet)->dajCene() <= budzet) { // jezeli w sieci bede dwa sklepy tak samo blisko ale w jednym cenia bedzie za wysoka to slabo
            szukanySklep = sklep;
            min_odl = sklep->OdlegloscOdPunktu(x_klienta, y_klienta);
        }
    }
    return  szukanySklep;
}

Towar *Siec::KonkretnyTowar(string nazwa, int budzet) {
    return nullptr;
}

double Siec::OdlegloscOdPunktu(int x, int y) {
    return 0;
}

Siec::Siec(string nazwa, double marza) : ObiektHandlowy(nazwa), marza(marza) {}

void Siec::dodajSklepDoSieci(Sklep *sklep) {

    this->sklepy.push_back(sklep);
    sklep->ustawSiec(this);
}

void Siec::przejmijSiec(Siec *siecDoPrzejecia) {
    siecDoPrzejecia->dajMiasto()->usunObiektHandlowy(siecDoPrzejecia);
    siecDoPrzejecia->ustawMiasto(nullptr);
    cout << "dupa" << endl;
    for (Sklep *sklep : siecDoPrzejecia->pokazSklepy()){
        siecDoPrzejecia->usunSklepzSieci(sklep);
        sklep->ustawSiec(this);
        this->dodajSklepDoSieci(sklep);
    }
    delete siecDoPrzejecia;
}

void Siec::wypisz(ostream &os) const {
    os << "nazwa Sieci: " << this->nazwa << ", marza: " << this->marza << ", saldo: " << this->saldo << endl;
    for (int i = 0; i < this->sklepy.size(); i++) cout << " sklep " << i << ": " << *(this->sklepy[i]) << endl;
}

void Siec::przelew(double kwota, Sklep *sklep) {
    sklep->przelew((1-this->marza)*kwota, sklep);
    this->saldo += this->marza * kwota;
};