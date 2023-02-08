#pragma once
#include <iostream>
#include "Sklep.h"
#include "Miasto.h"
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
    virtual void zakup(Miasto&) = 0;

    int dajBudzet() const;
    void JuzMamPrezent();

    bool CzyMamPrezent() const;


};

///////////////////////////////////////podklasy////////////////////////////////////////////////////////
//Maksymaliści cenowi kupują w wybranym sklepie najdroższy dostępny prezent na jaki ich stać.
class Maksymalista : public Klient {
public:
    Maksymalista(string imie, int budzet, int x, int y);
    Maksymalista() = delete;
    Maksymalista(const Maksymalista&) = delete;
    Maksymalista &operator=(const Maksymalista&) = delete;
    ~Maksymalista() override = default;

    //funkcje
    void zakup(ObiektHandlowy&) override;
};

//Minimaliści najtańszy
class Minimalista : public Klient {
public:
    Minimalista(string imie, int budzet, int x, int y);
    Minimalista() = delete;
    Minimalista(const Minimalista&) = delete;
    Minimalista &operator=(const Minimalista&) = delete;
    ~Minimalista() override = default;

    //funkcje
    void zakup(ObiektHandlowy&) override;
};

//Losowi kupujący próbują kilka razy (np. trzy, stała wartość w tej klasie) wybrać losowo wybrany (z
//oferowanych w sklepie) prezent, jeśli jest dostępny (tj. liczba sztuk jest większa od zera) i mieści się w
//budżecie, to go wybierają (i już nie próbują ponownie losować), wpp. losują ponownie (o ile nie była to
//ostatnia próba)
class Losowy : public Klient {
public:
    Losowy(string imie, int budzet, int x, int y);
    Losowy() = delete;
    Losowy(const Losowy&) = delete;
    Losowy &operator=(const Losowy&) = delete;
    ~Losowy() override = default;


    void zakup(ObiektHandlowy&) override;
};

//Tradycjonaliści nie kupują przez Internet i szukają
//najbliższego im zwykłego sklepu z poszukiwanym towarem (jeśli jest kilka w tej samej odległości wybierają
//dowolny z nich).
class Tradycjonalista : public Klient {
private:
    string szukanyProdukt;
public:
    const string &dajSzukanyProdukt() const;

    Tradycjonalista(string imie, int budzet, int x, int y, string Szukany);
    Tradycjonalista() = delete;
    Tradycjonalista(const Tradycjonalista&) = delete;
    Tradycjonalista &operator=(const Tradycjonalista&) = delete;
    ~Tradycjonalista() override = default;

    void zakup(Miasto&) override;
};


//Oszczędni pobierają listę sklepów z miasta, dowiadują się
//o cenę poszukiwanego produktu we wszystkich sklepach i kupują tam, gdzie jest najtaniej (jeśli kilka sklepów
//oferuje taką samą cenę, to wybierają dowolny z nich).
class Oszczedny : public Klient {
public:
    Oszczedny(string imie, int budzet, int x, int y) : Klient(imie, budzet, x, y) {};

    Towar zakup(vector<Sklep *> sklepy);
};
