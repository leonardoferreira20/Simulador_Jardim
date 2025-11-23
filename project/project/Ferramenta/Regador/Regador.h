//
// Created by jonhr on 31/10/2025.
//

#ifndef REGADOR_H
#define REGADOR_H

#include "../Ferramenta.h"
#include "../../Settings.h"

class Regador: public Ferramenta{
public:
    explicit Regador(int cap = Settings::Regador::capacidade, int d = Settings::Regador::dose);

    void utiliza(Solo& solo) override {solo.modificaAgua(10);};
    char getSimbolo() const override { return 'g'; }
    string getNome() const override { return "Regador"; }

    void setDose(int x)override {Ferramenta::setDose(x);};
    void setCapacidade (int x) override{Ferramenta::setCapacidade(x);};
};



#endif //REGADOR_H
