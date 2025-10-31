//
// Created by Leonardo Ferreira on 25/10/2025.
//

#ifndef FERRAMENTA_H
#define FERRAMENTA_H

#include <iostream>
#include "../Solo/Solo.h"
class Solo;

class Ferramenta {

public:
    int capacidade;
    int dose;
    int nserie;

    Ferramenta();
    virtual ~Ferramenta() = default;

    // Métodos abstratos (a serem implementados pelas subclasses)
    virtual void utiliza(Solo& solo) = 0;
    virtual void reduzCapacidade(Solo& solo) = 0;
    virtual char getSimbolo() const = 0;
    virtual string getNome() const = 0;

};



#endif //FERRAMENTA_H
