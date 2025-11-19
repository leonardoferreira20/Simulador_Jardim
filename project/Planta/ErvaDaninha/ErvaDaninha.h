//
// Created by jonhr on 31/10/2025.
//

#ifndef ERVADANINHA_H
#define ERVADANINHA_H

#include "../Planta.h"

class ErvaDaninha : public Planta {
    int instantes;
public:
    explicit ErvaDaninha(int ag = Settings::ErvaDaninha::inicial_agua, int nut =Settings::ErvaDaninha::inicial_nutrientes);
    void agir(Solo& solo) override;
    void morrer(Solo& solo) override;
    char getSimbolo() const override;
    string getNome() const override;

    //Obter
    int obtemInstantes()const {return instantes;};

    //Modificar
    void aumentaInst() {instantes++;}

    Planta* reproduzPlanta() override ;
};



#endif //ERVADANINHA_H
