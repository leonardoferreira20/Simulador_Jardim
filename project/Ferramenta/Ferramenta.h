//
// Created by Leonardo Ferreira on 25/10/2025.
//

#ifndef FERRAMENTA_H
#define FERRAMENTA_H

#include <iostream>

using namespace std;

class Solo;

class Ferramenta {
    int capacidade;
    int consumo;
    int nSerie;
    static int contador;

    public:
        Ferramenta(int capacidade, int consumo);

        virtual ~Ferramenta() = default;

        int getCapacidade() const { return capacidade; }
        int getConsumo() const { return consumo; }
        int getNSerie() const { return nSerie; }

        bool estaVazia() const { return capacidade <= 0; }

        void reduzirCapacidade();

        virtual char getSimbolo() const = 0;
        virtual string getNome() const = 0;
        virtual void utiliza(Solo& solo) = 0;
};



#endif //FERRAMENTA_H
