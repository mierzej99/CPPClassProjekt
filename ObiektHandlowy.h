//
// Created by michalmierzejewski on 2/8/23.
//
#ifndef CPPPROJEKT_OBIEKTHANDLOWY_H
#define CPPPROJEKT_OBIEKTHANDLOWY_H
#include <iostream>
#include <vector>
#include "Towar.h"
#include "Miasto.h"
using namespace std;

class Miasto;
class ObiektHandlowy {
protected:
    string nazwa;
    Miasto *miasto = nullptr; // sklep lub siec wie w jakim jest miescie
    double saldo = 0;
public:
    //techniczne
    ObiektHandlowy() = delete;
    explicit ObiektHandlowy(string nazwa);
    Miasto *dajMiasto() const;
    ObiektHandlowy(const ObiektHandlowy&) = delete;
    ObiektHandlowy &operator=(const ObiektHandlowy&) = delete;
    virtual ~ObiektHandlowy() = default;

    //wypisywanie
    virtual void wypisz(ostream& os) const = 0;
    friend ostream &operator<<(ostream &os, const ObiektHandlowy &handlowy);

    //settery i gettery
    const string &dajNazwe() const;
    void ustawMiasto(Miasto *miasto);
    virtual void przelew(double kwota, Sklep *sklep) = 0;


    //funkcje
    virtual Towar* NajdrozszyWBudzecie(int budzet) = 0;
    virtual Towar* NajtanszyTowar(int budzet) = 0;
    virtual Towar* LosowyTowar(int budzet) = 0;
    virtual Towar* NajtanszyKonkretnyTowar(string nazwa, int budzet) = 0; //metoda która dla sklepu będzie zwracała towar (jeżeli jest na stanie) a dla sieci najtanszy konkretny towar w sieci
    virtual ObiektHandlowy* NajblizszySklepZKonkretnymTowarem(string nazwa, int x_klienta, int y_klienta, int budzet) = 0;
    virtual Towar* KonkretnyTowar(string nazwa, int budzet) = 0;
    virtual double OdlegloscOdPunktu(int x, int y) = 0;

};
//////////////PODKLASY//////////////////////////////////////////////
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
    Sklep(const Sklep &innySklep) = delete;// nie kopiujemy sklepów
    Sklep &operator=(const Sklep &innySklep) = delete; // j.w.
    virtual ~Sklep();

    //wypisywanie
    void wypisz(ostream &os) const override;

    //settery i gettery
    int dajX() const;
    int dajY() const;
    virtual void ustawSiec(Siec *siec);
    virtual const vector<Towar *> &pokazTowary();
    virtual Siec *pokazSiec();
    virtual void odejdzZSieci(Siec *siec);
    virtual void przelew(double kwota, Sklep *sklep) override;

    //funkcje
    Towar* NajdrozszyWBudzecie(int budzet) override;
    Towar* NajtanszyTowar(int budzet) override;
    Towar* LosowyTowar(int budzet) override;
    Towar* NajtanszyKonkretnyTowar(string nazwa, int budzet) override;
    Towar* KonkretnyTowar(string nazwa, int budzet) override;
    ObiektHandlowy* NajblizszySklepZKonkretnymTowarem(string nazwa, int x_klienta, int y_klienta, int budzet) override;
    double OdlegloscOdPunktu(int x, int y) override; // nie ma sensu odleglośc od sieci
    virtual Sklep& operator+=(Towar*);
};


class Siec: public ObiektHandlowy {
private:
    double marza;
    vector<Sklep *> sklepy;
public:
    //konstruktor
    Siec(string nazwa, double marza, vector<Sklep *> sklepy);
    Siec(string nazwa, double marza);
    Siec() = delete;
    Siec(const Siec &innaSiec) = delete;
    Siec &operator=(const Siec &innaSiec) = delete;
    virtual ~Siec();

    //wypisywanie
    void wypisz(ostream &os) const override;

    //settery i gettery
    virtual void usunSklepzSieci(const Sklep *sklep);
    virtual void dodajSklepDoSieci(Sklep *sklep);
    const vector<Sklep *> &pokazSklepy();
    virtual void przelew(double kwota, Sklep *sklep) override;

    //funckje
    Towar* NajdrozszyWBudzecie(int budzet) override;
    Towar* NajtanszyTowar(int budzet) override;
    Towar* LosowyTowar(int budzet) override;
    Towar* NajtanszyKonkretnyTowar(string nazwa, int budzet) override;
    ObiektHandlowy* NajblizszySklepZKonkretnymTowarem(string nazwa, int x_klienta, int y_klienta, int budzet) override;
    Towar* KonkretnyTowar(string nazwa, int budzet) override;
    double OdlegloscOdPunktu(int x, int y) override;
    virtual void przejmijSiec(Siec *SiecDoPrzejecia);
    virtual Siec& operator+=(Sklep*);

};


#endif //CPPPROJEKT_OBIEKTHANDLOWY_H
