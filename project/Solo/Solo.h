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

    void imprimir () const;
    void adicionaAgua (int q);
    void retiraNutrientes (int q);
    Planta* obterPlanta() const;
    void criarPlanta(Planta* p);
    void removerPlanta();
    void imprimirDetalhado() const;

    bool temPlanta() const;
    //bool temFerramenta() const { return ferramenta != nullptr; }

    //Ferramenta* getFerramenta() const;
};



#endif //SOLO_H
