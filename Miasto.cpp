#include "Miasto.h"

using namespace std;
//konstruktor
Miasto::Miasto(const vector<Sklep *> &sklepy, const vector<Siec *> &sieci, const vector<Klient *> &klienci) : sklepy(
        sklepy), sieci(sieci), klienci(klienci) {};

//wypisywanie
ostream &operator<<(ostream &os, const Miasto &miasto) {
    os << "Sklepy: ";
    for (const auto &sklep : miasto.sklepy) {
        os << *sklep << " ";
    }
    os << endl;
    os << "Sieci: ";
    for (const auto &siec : miasto.sieci) {
        os << *siec << " ";
    }
    os << endl;
    os << "Klienci: ";
    for (const auto &klient : miasto.klienci) {
        os << *klient << " ";
    }
    os << endl;
    return os;
}
//destruktor
Miasto::~Miasto() {};
