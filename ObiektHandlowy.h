//
// Created by michalmierzejewski on 2/8/23.
//

#ifndef CPPPROJEKT_OBIEKTHANDLOWY_H
#define CPPPROJEKT_OBIEKTHANDLOWY_H
#include <iostream>
#include "Towar.h"
using namespace std;

class ObiektHandlowy {
protected:
    string nazwa;
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
    virtual Towar* KonkretnyTowar(string nazwa, int x_klienta, int y_klienta) = 0;





};


#endif //CPPPROJEKT_OBIEKTHANDLOWY_H
