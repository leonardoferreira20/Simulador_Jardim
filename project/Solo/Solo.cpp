//
// Created by Leonardo Ferreira on 11/10/2025.
//

#include "Solo.h"
#include <iostream>
#include "../Planta/Planta.h"

Solo::Solo() : agua(5), nutrientes(5), planta(nullptr)/*, ferramenta(nullptr)*/ {}

void Solo::adicionaAgua(int q){
    agua += q;
    if (agua > 10) agua = 10; // limite máximo
}

void Solo::retiraNutrientes(int q){
    nutrientes -= q;
    if (nutrientes < 0) nutrientes = 0;
}

/*
Ferramenta* Solo::getFerramenta() const{
    return ferramenta;
}
*/

void Solo::criarPlanta(Planta* p){
    planta = p;
}

Planta* Solo::obterPlanta() const{
    return planta;
}

void Solo::imprimir() const {
    if (planta != nullptr)
        cout << planta->getSimbolo();  // Ex: 'R' para Roseira, 'C' para Cacto
    //else if (ferramenta != nullptr)
    //    cout << ferramenta->getSimbolo();  // Ex: 'T' para Tesoura
    else
        cout << '.';
}