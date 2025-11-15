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

    Ferramenta();
    virtual ~Ferramenta() = default;
    int getCapacidade() const {return capacidade;}
    int getDose() const {return dose;}
    int getNserie() const {return nserie;}

    virtual void setDose(int x) {dose=x;};
    virtual void setNserie() {nserie+= ++contador;};
    virtual void setCapacidade (int x) {capacidade=x;};
    virtual void gastaCapacidade() {capacidade -= dose;};
    // Métodos abstratos (a serem implementados pelas subclasses)
    virtual void utiliza(Solo& solo) = 0;
    virtual void reduzCapacidade() {capacidade -= dose;}
    virtual char getSimbolo() const = 0;
    virtual string getNome() const = 0;

private:
    int capacidade;
    int dose;
    int nserie=1000;
    static int contador;
};



#endif //FERRAMENTA_H
