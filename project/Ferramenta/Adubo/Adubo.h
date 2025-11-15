//
// Created by jonhr on 31/10/2025.
//

#ifndef ADUBO_H
#define ADUBO_H

#include "../Ferramenta.h"

class Adubo:public Ferramenta {
    Adubo(){
        setDose(Settings::Adubo::dose);
        setCapacidade(Settings::Adubo::capacidade);
        Ferramenta::setNserie();
    }

    void utiliza(Solo& solo) override {solo.modificaAgua(10);};
    char getSimbolo() const override { return 'a'; }
    string getNome() const override { return "Adubo"; }

    void setDose(int x)override {Ferramenta::setDose(x);};
    void setCapacidade (int x) override{Ferramenta::setCapacidade(x);};
};



#endif //ADUBO_H
