#pragma once
#include <vector>
#include "Towar.h"
#include "ObiektHandlowy.h"
#include "Sklep.h"
class Sklep;


using namespace std;


class Siec: public ObiektHandlowy{
private:
    int marza;
    vector<Sklep *> sklepy;
public:
    //konstruktor
    Siec(string nazwa, int marza, vector<Sklep *> sklepy);
    Siec() = delete;
    Siec(const Siec &innaSiec) = delete;
    Siec &operator=(const Siec &innaSiec) = delete;
    ~Siec();

    //wypisywanie
    friend ostream &operator<<(ostream &os, const Siec &siec);

    //funckje
    Towar* NajdrozszyWBudzecie(int budzet) override;
    //Towar* NajtanszyTowar(int budzet) override;
    virtual void przejmijSiec(Siec *SiecDoPrzejecia);
    virtual void usunSklepzSieci(const Sklep *sklep);
    virtual void dodajSklepDoSieci(const Sklep *sklep);
    const vector<Sklep *> &pokazSklepy();



};