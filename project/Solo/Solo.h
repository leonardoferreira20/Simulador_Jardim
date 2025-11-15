//
// Created by Leonardo Ferreira on 11/10/2025.
//

#ifndef SOLO_H
#define SOLO_H

#include <iostream>
#include "../Planta/Planta.h"

using namespace std;

class Planta;

class Solo {
    int agua;
    int nutrientes;
    Planta* planta;
    //Ferramenta* ferramenta;

public:
    Solo();
    int getAgua() const {return agua;};
    int getNutrientes()const {return nutrientes;};
    void imprimir () const;
    void modificaAgua (int q){agua += q;}
    void modificaNutrientes (int q){nutrientes += q;}
    Planta* obterPlanta() const;
    void criarPlanta(Planta* p);
    void removerPlanta();
    void imprimirDetalhado() const;

    bool temPlanta() const;
    //bool temFerramenta() const { return ferramenta != nullptr; }

    //Ferramenta* getFerramenta() const;
};



#endif //SOLO_H
