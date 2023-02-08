#pragma once
#include <iostream>
#include "Sklep.h"
using namespace std;

class Klient {
private:
    string imie;
    int budzet;
    int x;
    int y;
    bool mamPrezent = false;
public:
    Klient() = delete;
    Klient(const string &imie, int budzet, int x, int y);
    Klient(const Klient &innyKlient) = delete;
    Klient &operator=(const Klient &innyKlient) = delete;
    virtual ~Klient() = default;

    //wypisywanie
    friend ostream &operator<<(ostream &os, const Klient &klient);

    virtual void zakup(ObiektHandlowy&) = 0;

    int dajBudzet() const;
    void JuzMamPrezent();


};

///////////////////////////////////////podklasy////////////////////////////////////////////////////////
//Maksymaliści cenowi kupują w wybranym sklepie najdroższy dostępny prezent na jaki ich stać.
class Maksymalista : public Klient {
public:
    Maksymalista(string imie, int budzet, int x, int y);
    ~Maksymalista() = default;
    void zakup(ObiektHandlowy&) override;
};

//Minimaliści najtańszy
class Minimalista : public Klient {
public:
    Minimalista(string imie, int budzet, int x, int y) : Klient(imie, budzet, x, y) {}
    void zakup(ObiektHandlowy&) override;
};
/*
//Losowi kupujący próbują kilka razy (np. trzy, stała wartość w tej klasie) wybrać losowo wybrany (z
//oferowanych w sklepie) prezent, jeśli jest dostępny (tj. liczba sztuk jest większa od zera) i mieści się w
//budżecie, to go wybierają (i już nie próbują ponownie losować), wpp. losują ponownie (o ile nie była to
//ostatnia próba)
class Losowy : public Klient {
public:
    Losowy(string imie, int budzet, int x, int y) : Klient(imie, budzet, x, y) {};

    Towar zakup(vector<Sklep *> sklepy);
};

class Tradycjonalista : public Klient {
public:
    Tradycjonalista(string imie, int budzet, int x, int y) : Klient(imie, budzet, x, y) {};

    Towar zakup(vector<Sklep *> sklepy);
};

class Oszczedny : public Klient {
public:
    Oszczedny(string imie, int budzet, int x, int y) : Klient(imie, budzet, x, y) {};

    Towar zakup(vector<Sklep *> sklepy);
};
*/