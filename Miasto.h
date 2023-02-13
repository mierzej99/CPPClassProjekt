#pragma once
#include <iostream>
#include <vector>
#include "Klient.h"

using namespace std;

class ObiektHandlowy;
class Sklep;
class Siec;
class Klient;
class Miasto {
private:
    vector<ObiektHandlowy *> sklepy;
    vector<Klient *> klienci;
public:
    //konstruktor
    Miasto() = default;
    Miasto(const vector<ObiektHandlowy *> &sklepy, const vector<Klient *> &klienci);
    Miasto(const Miasto &inneMiasto) = delete;
    Miasto &operator=(const Miasto &inneMiasto) = delete;
    virtual ~Miasto();

    //settery i gettery
    const vector<ObiektHandlowy *> &dajSklepy() const;
    void usunObiektHandlowy(ObiektHandlowy *placowka);
    const vector<Klient *> &dajKlientow() const;

    //wypisywanie
    friend ostream &operator<<(ostream &os, const Miasto &miasto);

    //funkcje
    virtual void dodajObiektHandlowy(ObiektHandlowy *sklep);
    virtual void dodajKlienta(Klient *klient);
    virtual Miasto& operator+=(Klient*);
    virtual Miasto& operator+=(ObiektHandlowy*);


};