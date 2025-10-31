//
// Created by jonhr on 31/10/2025.
//

#ifndef ERVADANINHA_H
#define ERVADANINHA_H

#include "../Planta.h"

class ErvaDaninha : public Planta {
    int instantes;
public:
    ErvaDaninha();
    void agir(Solo& solo) override;
    void morrer(Solo& solo) override;
    char getSimbolo() const override;
    string getNome() const override;
};



#endif //ERVADANINHA_H
