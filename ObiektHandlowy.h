//
// Created by michalmierzejewski on 2/8/23.
//

#ifndef CPPPROJEKT_OBIEKTHANDLOWY_H
#define CPPPROJEKT_OBIEKTHANDLOWY_H
#include <iostream>
#include "Towar.h"
#include "Miasto.h"
using namespace std;

class ObiektHandlowy {
protected:
    string nazwa;
    Miasto *miasto; // sklep wie w jakim jest miescie
public:
    //techniczne
    ObiektHandlowy() = delete;
    ObiektHandlowy(string nazwa);
    ObiektHandlowy(const ObiektHandlowy&) = delete;
    ObiektHandlowy &operator=(const ObiektHandlowy&) = delete;
    virtual ~ObiektHandlowy() = default;

    //funkcje
    virtual Towar* NajdrozszyWBudzecie(int budzet) = 0;
    virtual Towar* NajtanszyTowar(int budzet) = 0;
    virtual Towar* LosowyTowar(int budzet) = 0;
    virtual Towar* NajtanszyKonkretnyTowar(string nazwa, int budzet) = 0; //metoda która dla sklepu będzie zwracała towar (jeżeli jest na stanie) a dla sieci najtanszy konkretny towar w sieci
    virtual Towar* KonkretnyTowar(string nazwa, int budzet) = 0;
    virtual ObiektHandlowy* NajblizszySklepZKonkretnymTowarem(string nazwa, int x_klienta, int y_klienta, int budzet) = 0;
    virtual double OdlegloscOdPunktu(int x, int y) = 0;

};


#endif //CPPPROJEKT_OBIEKTHANDLOWY_H
