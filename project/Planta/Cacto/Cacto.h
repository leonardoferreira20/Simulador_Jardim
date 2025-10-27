//
// Created by Leonardo Ferreira on 25/10/2025.
//

#ifndef CACTO_H
#define CACTO_H

#include "../Planta.h"

class Cacto : public Planta {

public:
    Cacto();
    void agir(Solo& solo) override;
    void morrer(Solo& solo) override;
    char getSimbolo() const override;
};




#endif //CACTO_H
