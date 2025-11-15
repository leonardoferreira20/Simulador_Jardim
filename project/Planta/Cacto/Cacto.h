//
// Created by Leonardo Ferreira on 25/10/2025.
//

#ifndef CACTO_H
#define CACTO_H

#include "../Planta.h"

class Cacto : public Planta {

public:
    explicit Cacto(int ag = Settings::Jardim::agua_min,int nut = Settings::Jardim::nutrientes_min);
    void agir(Solo& solo) override;
    void morrer(Solo& solo) override;
    char getSimbolo() const override;
    string getNome() const override;

};




#endif //CACTO_H
