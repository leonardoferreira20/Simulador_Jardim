//
// Created by Leonardo Ferreira on 11/10/2025.
//

#include "Solo.h"
#include <iostream>
#include "../Planta/Planta.h"

int valorRandom (int min, int max) {return min + rand() %  (max - min + 1);}

Solo::Solo() :
agua(valorRandom (Settings::Jardim::agua_min,Settings::Jardim::agua_max)),
nutrientes(valorRandom(Settings::Jardim::nutrientes_min,Settings::Jardim::nutrientes_max)),
planta(nullptr)/*, ferramenta(nullptr)*/ {}

Solo::Solo(const Solo& outro){
    agua = outro.agua;
    nutrientes = outro.nutrientes;

    if (outro.planta != nullptr) {
        planta = outro.planta->clone();
    }else planta = nullptr;
}

/*
Ferramenta* Solo::getFerramenta() const{
    return ferramenta;
}
*/

void Solo::criarPlanta(Planta* p){
    planta = p;
}

void Solo::removerPlanta() {
    if ( planta != nullptr ) {
        delete planta;
        planta = nullptr;
    };
}

Planta* Solo::obterPlanta() const{
    return planta;
}

void Solo::imprimir() const {
    if (planta != nullptr)
        cout << planta->getSimbolo();
    //else if (ferramenta != nullptr)
    //    cout << ferramenta->getSimbolo();
    else
        cout << '.';
}


void Solo::imprimirDetalhado() const {
    cout << "Água: " << agua << " | Nutrientes: " << nutrientes << " | Planta: ";

    if (planta != nullptr) {
        cout << planta->getSimbolo();

        if (planta->estaViva())
            cout << " (viva)";
        else
            cout << " (morta)";
    } else {
        cout << "Nenhuma";
    }

    cout << endl;
}

bool Solo::temPlanta() const {
    return planta != nullptr;
}