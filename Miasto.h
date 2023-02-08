#pragma once
#include "Towar.h"
#include "Sklep.h"
#include "Siec.h"
#include "Klient.h"

using namespace std;

class Miasto {
private:
    vector<Sklep *> sklepy;
    vector<Siec *> sieci;
    vector<Klient *> klienci;
public:
    //konstruktor
    Miasto(const vector<Sklep *> &sklepy, const vector<Siec *> &sieci, const vector<Klient *> &klienci);

    //kopiowanie
    Miasto(const Miasto &inneMiasto) = delete;

    Miasto &operator=(const Miasto &inneMiasto) = delete;

    //wypisywanie
    friend ostream &operator<<(ostream &os, const Miasto &miasto);
    //destruktor
    virtual ~Miasto();

    void dodajSklep(Sklep *sklep);

    void dodajSiec(Siec *siec);

    void dodajKlienta(Klient *klient);

    void startMiasta();




};