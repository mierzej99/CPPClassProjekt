#pragma once
#include "Towar.h"
#include "Sklep.h"
#include "Siec.h"
#include "Klient.h"

using namespace std;


class Miasto {
private:
    vector<ObiektHandlowy *> sklepy;
    vector<Klient *> klienci;
public:
    //konstruktor
    Miasto(const vector<ObiektHandlowy *> &sieci, const vector<Klient *> &klienci);
    Miasto(const Miasto &inneMiasto) = delete;
    Miasto &operator=(const Miasto &inneMiasto) = delete;
    virtual ~Miasto() = default;

    //wypisywanie
    friend ostream &operator<<(ostream &os, const Miasto &miasto);

    //funkcje
    virtual void dodajSklep(Sklep *sklep);
    virtual void dodajSiec(Siec *siec);
    virtual void dodajKlienta(Klient *klient);
    virtual void startMiasta();

    const vector<ObiektHandlowy *> &dajSklepy() const;


};