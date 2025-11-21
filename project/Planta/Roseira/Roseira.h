//
// Created by Leonardo Ferreira on 25/10/2025.
//

#ifndef ROSEIRA_H
#define ROSEIRA_H

#include "../Planta.h"

class Roseira: public Planta {
    public:
        explicit Roseira(int ag = Settings::Roseira::inicial_agua, int nut = Settings::Roseira::inicial_nutrientes);
        void agir(Solo& solo) override;
        void morrer(Solo& solo) override;
        char getSimbolo() const override;
        string getNome() const override;
        Planta* reproduzPlanta() override ;
        bool podeReproduzir()override;
};



#endif //ROSEIRA_H
