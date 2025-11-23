//
// Created by jonhr on 31/10/2025.
//

#ifndef ERVADANINHA_H
#define ERVADANINHA_H

#include "../Planta.h"
#include "../../Settings.h"

class ErvaDaninha : public Planta {
    int instantes=0;
public:
    explicit ErvaDaninha(int ag = Settings::ErvaDaninha::inicial_agua, int nut =Settings::ErvaDaninha::inicial_nutrientes);
    Planta* clone()const override;

    void agir(Solo& solo) override;
    void morrer(Solo& solo) override;
    char getSimbolo() const override;
    string getNome() const override;
    int getInstantes() const {return instantes;};
    void aumentaInstantes(){instantes++;};

    Planta* reproduzPlanta() override ;
    bool podeReproduzir() override;
    bool isFeia() override{return true;}
};



#endif //ERVADANINHA_H
