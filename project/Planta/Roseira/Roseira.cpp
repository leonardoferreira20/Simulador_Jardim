//
// Created by Leonardo Ferreira on 25/10/2025.
//

#include <iostream>
#include "Roseira.h"
#include "../../Settings.h"
#include "../../Solo/Solo.h"

using namespace std;

Roseira::Roseira() {
    agua = Settings::Roseira::inicial_agua;
    nutrientes = Settings::Roseira::inicial_nutrientes;
    viva = true;
}

void Roseira::agir(Solo& solo) {
    // Perde água e nutrientes a cada ciclo
    agua -= Settings::Roseira::perda_agua;
    nutrientes -= Settings::Roseira::perda_nutrientes;

    // Absorve do solo
    solo.retiraNutrientes(Settings::Roseira::absorcao_nutrientes);
    solo.adicionaAgua(Settings::Roseira::absorcao_agua);

    // Morre se não tiver condições ideais
    if (agua < Settings::Roseira::morre_agua_menor ||
        nutrientes < Settings::Roseira::morre_nutrientes_menor ||
        nutrientes > Settings::Roseira::morre_nutrientes_maior)
    {
        morrer(solo);
    }
}

void Roseira::morrer(Solo& solo) {
    viva = false;
    cout << "Uma roseira murchou.\n";
    solo.removerPlanta();
}

char Roseira::getSimbolo() const {
    return 'R';
}

string Roseira::getNome() const{
    return "Roseira";
}