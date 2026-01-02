//
// Created by Leonardo Ferreira on 25/10/2025.
//

#ifndef CACTO_H
#define CACTO_H

#include "../../Settings.h"
#include "../Planta.h"

class Cacto : public Planta {

public:
    explicit Cacto(int ag = Settings::Jardim::agua_min,int nut = Settings::Jardim::nutrientes_min);
    Planta* clone()const override;

    void agir(Solo& solo) override;
    void morrer(Solo& solo, ostream& out) override;
    char getSimbolo() const override;
    string getNome() const override;

    Planta* reproduzPlanta() override ;
    bool podeReproduzir()override;
    bool isFeia() override{return true;}
};




#endif //CACTO_H
