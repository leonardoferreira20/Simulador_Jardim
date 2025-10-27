//
// Created by Leonardo Ferreira on 25/10/2025.
//


#include "Cacto.h"
#include "../../Settings.h"
#include "../../Solo/Solo.h"
#include <iostream>

using namespace std;

Cacto::Cacto(){
    agua = Settings::Jardim::agua_min;
    nutrientes = Settings::Jardim::nutrientes_min;
    viva = true;
}

void Cacto::agir(Solo& solo){
    // Absorve pouca água e nutrientes
    agua += Settings::Cacto::absorcao_agua_percentagem / 10;
    nutrientes += Settings::Cacto::absorcao_nutrientes;

    // Verifica se morre por excesso de água ou falta de nutrientes
    /*if ( solo.getAgua() > Settings::Cacto::morre_agua_solo_maior ||
         solo.getNutrientes() < Settings::Cacto::morre_nutrientes_solo_menor ){
        morrer(solo);
    }*/
}

void Cacto::morrer(Solo& solo){
    viva = false;
    cout << "Morreu um cacto.\n";
}

char Cacto::getSimbolo() const{
    return 'C';
}