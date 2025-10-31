//
// Created by jonhr on 31/10/2025.
//

#ifndef EXOTICA_H
#define EXOTICA_H

#include "../Planta.h"

class Exotica : public Planta {

public:
    Exotica();
    void agir(Solo& solo) override;
    void morrer(Solo& solo) override;
    char getSimbolo() const override;
    string getNome() const override;

};



#endif //EXOTICA_H
