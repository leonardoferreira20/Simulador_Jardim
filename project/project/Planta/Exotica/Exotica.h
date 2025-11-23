//
// Created by jonhr on 31/10/2025.
//

#ifndef EXOTICA_H
#define EXOTICA_H

#include "../Planta.h"

class Exotica : public Planta {

public:
    explicit Exotica(int ag = Settings::Exotica::inicial_agua, int nut = Settings::Exotica::inicial_nutrientes);
    Planta* clone()const override;

    void agir(Solo& solo) override;
    void morrer(Solo& solo) override;
    char getSimbolo() const override;
    string getNome() const override;

    Planta* reproduzPlanta() override ;
    bool podeReproduzir() override;
};



#endif //EXOTICA_H
