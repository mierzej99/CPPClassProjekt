#include "Miasto.h"
#include <vector>
#include <algorithm>
//funckje
const vector<ObiektHandlowy *> &Miasto::dajSklepy() const {
    return sklepy;
}

Miasto::~Miasto() {
    for (ObiektHandlowy* placowka : this->sklepy){
        delete placowka;
    }
    for (Klient* klient : this->klienci){
        delete klient;
    }
}

void Miasto::dodajObiektHandlowy(ObiektHandlowy *sklep) {
    sklep->ustawMiasto(this);
    this->sklepy.push_back(sklep);
}

void Miasto::dodajKlienta(Klient *klient) {
    klient->ustawMiasto(this);
    this->klienci.push_back(klient);
}

void Miasto::usunObiektHandlowy(ObiektHandlowy *placowka){
    this->sklepy.erase(remove(this->sklepy.begin(), this->sklepy.end(), placowka), this->sklepy.end());
}

const vector<Klient *> &Miasto::dajKlientow() const {
    return klienci;
}

ostream &operator<<(ostream &os, const Miasto &miasto) {\
    os << "-----SKLEPY I SIECI-----" << endl;
    for(ObiektHandlowy* sklep : miasto.dajSklepy()){
        os << *sklep << endl;
    }
    os << "-----KLIENCI-----" << endl;
    for (Klient *klient : miasto.dajKlientow()){
        os << *klient << endl;
    }
    return os;
}

Miasto::Miasto(const vector<ObiektHandlowy *> &sklepy, const vector<Klient *> &klienci) : sklepy(sklepy), klienci(klienci){}

Miasto &Miasto::operator+=(Klient *klient) {
    klienci.push_back(klient);
    return *this;
}

Miasto &Miasto::operator+=(ObiektHandlowy *sklep) {
    sklepy.push_back(sklep);
    return *this;
};


