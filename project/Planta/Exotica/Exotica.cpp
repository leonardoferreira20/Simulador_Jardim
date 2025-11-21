//
// Created by jonhr on 31/10/2025.
//

#include "Exotica.h"

#include "../../Settings.h"
#include "../../Solo/Solo.h"

#include "../../Settings.h"
#include "../../Solo/Solo.h"

using namespace std;

Exotica::Exotica(int ag, int nut):Planta (ag, nut){

}

void Exotica::agir(Solo& solo) {
    aumentaTempoVida();
    // Perde água e nutrientes a cada ciclo
    alteraAgua((-1)*Settings::Exotica::perda_agua);
    alteraNutrientes((-1)*Settings::Exotica::perda_nutrientes);

    // Absorve do solo
    solo.modificaNutrientes(Settings::Exotica::absorcao_nutrientes);
    solo.modificaAgua(Settings::Exotica::absorcao_agua);

    // Morre se não tiver condições ideais
    if (solo.obtemAgua() < Settings::Exotica::morre_agua_menor ||
        obtemNutrientesP() < Settings::Exotica::morre_nutrientes_menor ||
        obtemNutrientesP() > Settings::Exotica::morre_nutrientes_maior)
    {
        morrer(solo);
    }
}

void Exotica::morrer(Solo& solo) {
    alteraViva(false);
    cout << "Uma Exotica murchou.\n";
    solo.removerPlanta();
}

char Exotica::getSimbolo() const {
    return 'X';
}

string Exotica::getNome() const{
    return "Exotica";
}

Planta* Exotica::reproduzPlanta(){
    Exotica* filho;
    filho = new Exotica(obtemAguaP(),obtemNutrientesP());
    filho->alteraAgua((-1)*obtemAguaP()/2);
    filho->alteraNutrientes((-1)*obtemNutrientesP()/2);

    setAgua(obtemAguaP()*Settings::Exotica::original_agua_percentagem/100);
    setNutrientes(Settings::Exotica::original_nutrientes);

    return filho;
}

bool Exotica::podeReproduzir() {
    if (obtemNutrientesP()>Settings::Roseira::multiplica_nutrientes_maior) {
        return true;
    }
    return false;
}