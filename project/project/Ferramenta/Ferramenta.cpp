//
// Created by Leonardo Ferreira on 25/10/2025.
//
#include "../Solo/Solo.h"
#include "Ferramenta.h"

int Ferramenta::contador = 0;

Ferramenta::Ferramenta(int cap, int d):capacidade(cap),dose(d){
    setNserie();
}