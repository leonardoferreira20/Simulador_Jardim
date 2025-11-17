//
// Created by Leonardo Ferreira on 25/10/2025.
//


#include "Cacto.h"
#include "../../Settings.h"
#include "../../Solo/Solo.h"
#include <iostream>

using namespace std;

Cacto::Cacto(int ag, int nut) :Planta(ag,nut){

}

void Cacto::agir(Solo& solo){
    // Absorve pouca água e nutrientes
    alteraAgua(solo.obtemAgua()*Settings::Cacto::absorcao_agua_percentagem / 100);
    solo.modificaAgua (-1*solo.obtemAgua()*Settings::Cacto::absorcao_agua_percentagem / 100);
    if (solo.obtemNutrientes()>Settings::Cacto::absorcao_nutrientes) {
        alteraNutrientes (Settings::Cacto::absorcao_nutrientes);
        solo.modificaNutrientes(-1*Settings::Cacto::absorcao_nutrientes);
    }

    // Verifica se morre por excesso de água ou falta de nutrientes
    if ( solo.obtemAgua() > Settings::Cacto::morre_agua_solo_maior ||
         solo.obtemNutrientes() < Settings::Cacto::morre_nutrientes_solo_menor ) {
        morrer(solo);
    }
}

void Cacto::morrer(Solo& solo){
    alteraViva (false);
    cout << "Morreu um cacto.\n";

    solo.removerPlanta();
}

char Cacto::getSimbolo() const{
    return 'C';
}

string Cacto::getNome() const{
    return "Cacto";
}