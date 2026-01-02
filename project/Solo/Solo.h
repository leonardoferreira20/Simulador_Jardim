//
// Created by Leonardo Ferreira on 11/10/2025.
//

#ifndef SOLO_H
#define SOLO_H

#include <iostream>
#include "../Settings.h"

using namespace std;

class Planta;
class Ferramenta;

class Solo {
    int agua;
    int nutrientes;
    Planta* planta;

    Ferramenta* ferramenta;

public:
    Solo();
    Solo(const Solo& outro);
    ~Solo();



    Solo& operator=(const Solo& outro);



    int obtemAgua() const {return agua;};
    int obtemNutrientes()const {return nutrientes;};

    void imprimir () const;
    void modificaAgua (int q){agua += q;}
    void modificaNutrientes (int q){nutrientes += q;}
    void encherAgua (){ agua = Settings::Jardim::agua_max; }

    // PLANTAS
    Planta* obterPlanta() const;
    void criarPlanta(Planta* p);
    void removerPlanta();
    void imprimirDetalhado() const;
    bool temPlanta() const;

    // FERRAMENTAS
    Ferramenta* obterFerramenta();
    bool temFerramenta() const;
    void colocarFerramenta(Ferramenta* ferramenta);
    void removerFerramenta();

};



#endif //SOLO_H
