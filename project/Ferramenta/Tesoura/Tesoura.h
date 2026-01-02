//
// Created by jonhr on 31/10/2025.
//

#ifndef TESOURA_H
#define TESOURA_H

#include "../Ferramenta.h"

using namespace std;

class Tesoura: public Ferramenta  {
    public:
        Tesoura() : Ferramenta(-1, 0) {}  // infinita

        char getSimbolo() const override { return 'T'; }
        string getNome() const override { return "Tesoura de Poda"; }

        void utiliza(Solo& solo) override;
        Ferramenta* clone() const override { return new Tesoura(*this); }
};



#endif //TESOURA_H
