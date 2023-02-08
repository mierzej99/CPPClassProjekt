#pragma once
#include <iostream>
using namespace std;

class Towar {
private:
    string nazwa;
    int cena;
    int ilosc;
public:
    //konstrukotr
    Towar(const string &nazwa, int cena, int ilosc);
    Towar() = delete;
    Towar(const Towar &innyTowar);
    Towar &operator=(const Towar &innyTowar);
    ~Towar() = default;

    friend ostream &operator<<(ostream &os, const Towar &towar);

    //funkcje
    virtual void zmienCene(int cena);

    int dajIlosc() const;

    virtual void zmienIlosc(int ilosc);

    int dajCene() const;

    const string &dajNazwe() const;

};