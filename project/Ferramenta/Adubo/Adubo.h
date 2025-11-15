//
// Created by jonhr on 31/10/2025.
//

#ifndef ADUBO_H
#define ADUBO_H

#include "../Ferramenta.h"
#include "../../Settings.h"

class Adubo:public Ferramenta {
    explicit Adubo(int cap = Settings::Adubo::capacidade, int d = Settings::Adubo::dose);

    void utiliza(Solo& solo) override {solo.modificaAgua(10);};
    char getSimbolo() const override { return 'a'; }
    string getNome() const override { return "Adubo"; }

    void setDose(int x)override {Ferramenta::setDose(x);};
    void setCapacidade (int x) override{Ferramenta::setCapacidade(x);};
};



#endif //ADUBO_H
