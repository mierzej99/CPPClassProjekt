#include <iostream>
#include <vector>
#include "Towar.h"
#include "ObiektHandlowy.h"
#include "Klient.h"
#include "Miasto.h"

using namespace std;

int main() {

    Miasto Bogatki{};
    vector<Towar *> towary1, towary2, towary3, towary4;
    towary1.push_back(new Towar("1", 1, 1));
    towary1.push_back(new Towar("2", 2, 2));

    towary2.push_back(new Towar("2", 2, 2));
    towary2.push_back(new Towar("3", 3, 3));

    towary3.push_back(new Towar("3", 3, 3));
    towary3.push_back(new Towar("4", 4, 4));

    towary4.push_back(new Towar("4", 4, 4));
    towary4.push_back(new Towar("5", 5, 5));

    Sklep *sklep1 = new Sklep("sklep1", towary1, 1, 1, nullptr);
    Sklep *sklep2 = new Sklep("sklep2", towary2, 2, 2, nullptr);
    Sklep *sklep3 = new Sklep("sklep3", towary3, 3, 3, nullptr);
    Sklep *sklep4 = new Sklep("sklep4", towary4, 4, 4, nullptr);

    Siec *lidl = new Siec("Lidl", 0.15);
    Siec *biedronka = new Siec("Biedronka", 0.1);

    lidl->dodajSklepDoSieci(sklep1);
    lidl->dodajSklepDoSieci(sklep3);

    biedronka->dodajSklepDoSieci(sklep2);
    biedronka->dodajSklepDoSieci(sklep4);

    Bogatki.dodajObiektHandlowy(biedronka);
    Bogatki.dodajObiektHandlowy(lidl);

    biedronka->przejmijSiec(lidl);

    Maksymalista *maks = new Maksymalista("Jan", 100, 1,1);
    Minimalista *mini = new Minimalista("Janina", 100, 1,1);
    Losowy *losowy = new Losowy("Wiesław", 100, 1,1);
    Tradycjonalista *trad = new Tradycjonalista("Wiesława", 100, 3, 3, "2");
    Oszczedny *oszcz = new Oszczedny("Zenon", 100, 1, 1, "3");



    Bogatki.dodajKlienta(maks);
    Bogatki.dodajKlienta(mini);
    Bogatki.dodajKlienta(losowy);
    Bogatki.dodajKlienta(trad);
    Bogatki.dodajKlienta(oszcz);

    //cout << Bogatki << endl;

    for (auto *klient : Bogatki.dajKlientow()){
        klient->zakup(Bogatki);
    }


    cout << Bogatki << endl;

}