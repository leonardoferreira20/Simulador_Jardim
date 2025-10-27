//
// Created by Leonardo Ferreira on 11/10/2025.
//

#ifndef SOLO_H
#define SOLO_H

#include <string>
#include "../Planta/Planta.h"

using namespace std;

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
    
    //Ferramenta* getFerramenta() const;
};



#endif //SOLO_H
