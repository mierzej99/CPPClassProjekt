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
    Sklep(const Sklep &innySklep) = delete;

    // nie kopiujemy sklepów
    Sklep &operator=(const Sklep &innySklep) = delete; // j.w.
    ~Sklep();

    //strumień
    friend ostream &operator<<(ostream &os, const Sklep &sklep);

    //funkcje
    Towar* NajdrozszyWBudzecie(int budzet) override;
    Towar* NajtanszyTowar(int budzet) override;
    Towar* LosowyTowar(int budzet) override;
    Towar* NajtanszyKonkretnyTowar(string nazwa, int budzet) override;
    Towar* KonkretnyTowar(string nazwa, int budzet) override;
    ObiektHandlowy* NajblizszySklepZKonkretnymTowarem(string nazwa, int x_klienta, int y_klienta, int budzet) override;
    int dajX() const;
    int dajY() const;
    double OdlegloscOdPunktu(int x, int y) override; // nie ma sensu odleglośc od sieci
    virtual void ustawSiec(Siec *siec);
    virtual const vector<Towar *> &pokazTowary();
    virtual Siec *pokazSiec();
    virtual void odejdzZSieci(Siec *siec);
};
