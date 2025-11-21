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

void Roseira::agir(Solo& solo){
    aumentaTempoVida();
    // Perde água e nutrientes a cada ciclo
    if (solo.obtemAgua()>=Settings::Roseira::absorcao_agua){
        solo.modificaAgua(Settings::Roseira::absorcao_agua*-1);
        alteraAgua(Settings::Roseira::absorcao_agua);
    }else if (solo.obtemAgua()>0) {
        alteraAgua(solo.obtemAgua());
        solo.modificaAgua(solo.obtemAgua()*-1);
    }
    if (solo.obtemNutrientes()>=Settings::Roseira::absorcao_nutrientes) {
        solo.modificaNutrientes(Settings::Roseira::absorcao_nutrientes*-1);
        alteraNutrientes(Settings::Roseira::absorcao_nutrientes);
    }else if (solo.obtemNutrientes()>0) {
        alteraNutrientes(solo.obtemNutrientes());
        solo.modificaNutrientes(solo.obtemNutrientes()*-1);
    }

    alteraAgua(Settings::Roseira::perda_agua*-1);
    alteraNutrientes(Settings::Roseira::perda_nutrientes*-1);

    // Morre se não tiver condições ideais
    if (obtemAguaP() < Settings::Roseira::morre_agua_menor ||
        obtemNutrientesP() < Settings::Roseira::morre_nutrientes_menor ||
        obtemNutrientesP() > Settings::Roseira::morre_nutrientes_maior)
    {
        if (obtemNutrientesP()>0) solo.modificaNutrientes(obtemNutrientesP());
        if ( obtemAguaP()>0) solo.modificaAgua(obtemAguaP());
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

Planta* Roseira::reproduzPlanta(){
    Roseira* filho;

    filho = new Roseira(obtemAguaP()*Settings::Roseira::original_agua_percentagem/100,Settings::Roseira::nova_nutrientes);
    filho->setAgua(obtemAguaP()*Settings::Roseira::original_agua_percentagem/100);
    filho->setNutrientes(Settings::Roseira::original_nutrientes);

    setAgua(obtemAguaP()*Settings::Roseira::original_agua_percentagem/100);
    setNutrientes(Settings::Roseira::original_nutrientes);

    return filho;
}

bool Roseira::podeReproduzir() {
    if (obtemNutrientesP()>Settings::Roseira::multiplica_nutrientes_maior) {
        return true;
    }
    return false;
}
