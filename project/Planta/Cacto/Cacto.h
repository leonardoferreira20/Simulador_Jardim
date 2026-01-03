#ifndef CACTO_H
#define CACTO_H

#include "../../Settings.h"
#include "../Planta.h"

class Cacto : public Planta {
    int contaAguaAlta;          // nº instantes seguidos com agua no solo > 100
    int contaNutZero;           // nº instantes seguidos com nutrientes no solo == 0
    int nutrientesAbsorvidos;   // total de nutrientes absorvidos durante a vida

public:
    explicit Cacto(int ag = 0,
                   int nut = 0);

    Planta* clone() const override;

    void agir(Solo& solo) override;
    void morrer(Solo& solo, ostream& out) override;

    char getSimbolo() const override;
    string getNome() const override;

    Planta* reproduzPlanta() override;
    bool podeReproduzir() override;

    bool isFeia() override { return false; } // cacto é neutro
};

#endif //CACTO_H