#include <iostream>
#include "Towar.h"
#include "Klient.h"

using namespace std;

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


///////////////MAKSYMALISTA////////////////////////////////////////////////////////////////////////////
Maksymalista::Maksymalista(string imie, int budzet, int x, int y) : Klient(imie, budzet, x, y) {};


void Maksymalista::zakup(ObiektHandlowy &placowka) {
    Towar *temp = placowka.NajdrozszyWBudzecie(this->dajBudzet());
    if (temp != nullptr) {
        this->JuzMamPrezent();
        temp->zmienIlosc(-1);
    }
};



