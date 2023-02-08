#pragma once

#include <vector>
#include "ObiektHandlowy.h"
#include "Towar.h"
#include "Siec.h"

using namespace std;

class Siec;

class Sklep : public ObiektHandlowy{
private:
    int x;
    int y;
    vector<Towar *> towary;
    Siec *siec;
public:
    //konstruktor
    Sklep(string nazwa, vector<Towar *> towary, int x, int y, Siec *siec = nullptr);
    Sklep() = delete;
    Sklep(const Sklep &innySklep);
    Sklep &operator=(const Sklep &innySklep);
    ~Sklep();

    //strumień
    friend ostream &operator<<(ostream &os, const Sklep &sklep);

    //funkcje
    Towar* NajdrozszyWBudzecie(int budzet) override;
    Towar* NajtanszyTowar(int budzet) override;
    Towar* LosowyTowar(int budzet) override;
    Towar* KonkretnyTowar(string nazwa) override;
    virtual void ustawSiec(Siec *siec);
    virtual const vector<Towar *> &pokazTowary();
    virtual Siec *pokazSiec();
    virtual void odejdzZSieci(Siec *siec);
};
