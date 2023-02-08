#include <iostream>
#include <vector>
#include "Towar.h"
#include "Sklep.h"
#include "Siec.h"
#include "Klient.h"
#include "Miasto.h"

using namespace std;

int main() {
    vector<Towar *> towary;
    towary.push_back(new Towar("1", 1, 1));
    towary.push_back(new Towar("2", 2, 2));
    vector<Sklep *> sklepy;
    sklepy.push_back(new Sklep("dupa jasia", towary, 2, 2));
    Siec siu("lidl", 0.5, sklepy);
    cout << *(siu.pokazSklepy()[0]->pokazSiec()) << endl;
    Towar* t1 = new Towar("dupa jasia", 1, 1);
    cout << *t1 << endl;
    delete t1;

    Maksymalista maks("jasiu", 100, 10,10);
    maks.zakup(siu);
    cout << maks << endl;
    cout << siu << endl;
}