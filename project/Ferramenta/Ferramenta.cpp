//
// Created by Leonardo Ferreira on 25/10/2025.
//
#include "Ferramenta.h"

int Ferramenta::contador = 0;

Ferramenta::Ferramenta(int cap, int d) : capacidade(cap), consumo(d) {
    nSerie = (++contador);
}

void Ferramenta::reduzirCapacidade() {
    capacidade -= consumo;
    if (capacidade < 0) {
        capacidade = 0;
    }
}