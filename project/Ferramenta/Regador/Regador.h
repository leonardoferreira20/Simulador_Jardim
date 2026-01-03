//
// Created by jonhr on 31/10/2025.
//

#ifndef REGADOR_H
#define REGADOR_H

#include "../Ferramenta.h"
#include "../../Settings.h"

using namespace std;

class Regador: public Ferramenta {
    public:
        Regador() : Ferramenta(Settings::Regador::capacidade, Settings::Regador::dose) {}

        char getSimbolo() const override { return 'G'; }
        string getNome() const override { return "Regador"; }
        void utiliza(Solo& solo, ostream& out) override;
        Ferramenta* clone() const override { return new Regador(*this); }
};



#endif //REGADOR_H
