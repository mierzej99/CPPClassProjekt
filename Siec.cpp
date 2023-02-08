#include <iostream>
#include <algorithm>
#include <vector>
#include "Siec.h"

//konstruktor
Siec::Siec(string nazwa, int marza, vector<Sklep *> sklepy) : ObiektHandlowy(nazwa), marza(marza), sklepy(sklepy) {
    for(int i = 0; i < sklepy.size(); i++){
        sklepy[i]->ustawSiec(this);
    }
};


//wypisywanie
ostream &operator<<(ostream &os, const Siec &siec) {
    os << "nazwa: " << siec.nazwa << " marza: " << siec.marza << endl;
    for (int i = 0; i < siec.sklepy.size(); i++) cout << " sklep " << i << ": " << *(siec.sklepy[i]) << endl;
    return os;
}

//destruktor

//funckje

void Siec::usunSklepzSieci(const Sklep* sklep) {
    this->sklepy.erase(remove(this->sklepy.begin(), this->sklepy.end(), sklep), this->sklepy.end());
};

void Siec::dodajSklepDoSieci(const Sklep *sklep){};

const vector<Sklep *>& Siec::pokazSklepy() {
    return sklepy;
};

void Siec::przejmijSiec(Siec *SiecDoPrzejecia) {

}

Siec::~Siec()
{
    for (Sklep* sklep : sklepy)
        delete sklep;
}

Towar* Siec::NajdrozszyWBudzecie(int budzet) {
    int max = 0;
    Towar *maksymalnyProdukt = nullptr, *temp = nullptr;

    for(Sklep* sklep : this->pokazSklepy()){
        temp = sklep->NajdrozszyWBudzecie(budzet);
        if (temp != nullptr && temp->dajCene() > max){max = temp->dajCene(); maksymalnyProdukt=temp;}
        //idziemy po wszystkich sklepach
        }
    return temp;

};