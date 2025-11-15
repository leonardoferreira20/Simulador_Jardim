//
// Created by Leonardo Ferreira on 25/10/2025.
//

#include <iostream>
#include "Roseira.h"
#include "../../Settings.h"
#include "../../Solo/Solo.h"

using namespace std;

Roseira::Roseira(int ag, int nut):Planta(ag,nut) {

}

void Roseira::agir(Solo& solo) {
    // Perde água e nutrientes a cada ciclo
if (solo.obtemAgua()>=Settings::Roseira::absorcao_agua && solo.obtemNutrientes()>=Settings::Roseira::absorcao_nutrientes) {
    solo.modificaNutrientes(Settings::Roseira::absorcao_nutrientes*-1);
    solo.modificaAgua(Settings::Roseira::absorcao_agua*-1);
    alteraAgua(Settings::Roseira::perda_agua);
    alteraNutrientes(Settings::Roseira::perda_agua);
}
    alteraAgua(Settings::Roseira::perda_agua*-1);
    alteraNutrientes(Settings::Roseira::perda_nutrientes*-1);

    // Absorve do solo

    // Morre se não tiver condições ideais
    if (obtemAguaP() < Settings::Roseira::morre_agua_menor ||
        obtemNutrientesP() < Settings::Roseira::morre_nutrientes_menor ||
        obtemNutrientesP() > Settings::Roseira::morre_nutrientes_maior)
    {
        morrer(solo);
    }
}

void Roseira::morrer(Solo& solo) {
    alteraViva (false);
    cout << "Uma roseira murchou.\n";
    solo.removerPlanta();
}

char Roseira::getSimbolo() const {
    return 'R';
}

string Roseira::getNome() const{
    return "Roseira";
}