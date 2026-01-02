//
// Created by jonhr on 31/10/2025.
//

#ifndef ADUBO_H
#define ADUBO_H

#include "../Ferramenta.h"
#include "../../Settings.h"

using namespace std;

class Adubo:public Ferramenta {
    public:
        Adubo() : Ferramenta(Settings::Adubo::capacidade, Settings::Adubo::dose) {}

        char getSimbolo() const override { return 'A'; }
        string getNome() const override { return "Adubo"; }

        void utiliza(Solo& solo) override;
        Ferramenta* clone() const override { return new Adubo(*this); }
};



#endif //ADUBO_H
