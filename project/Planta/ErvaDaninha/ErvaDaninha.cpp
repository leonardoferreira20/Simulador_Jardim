//
// Created by jonhr on 31/10/2025.
//

#include "ErvaDaninha.h"

#include "../../Settings.h"
#include "../../Solo/Solo.h"


ErvaDaninha::ErvaDaninha(int ag, int nut):Planta(ag,nut){
}

void ErvaDaninha::agir(Solo& solo) {
    aumentaTempoVida();

    // Absorve do solo
    solo.modificaNutrientes((-1)*Settings::ErvaDaninha::absorcao_nutrientes);
    solo.modificaAgua((-1)*Settings::ErvaDaninha::absorcao_agua);

    // Morre
    if (obtemTempoVida() == Settings::ErvaDaninha::morre_instantes)
    {
        morrer(solo);
    }
    //Multiplicação
    if (obtemNutrientesP() > Settings::ErvaDaninha::multiplica_nutrientes_maior) {

    }
}

void ErvaDaninha::morrer(Solo& solo) {
    alteraViva(false);
    cout << "Uma ErvaDaninha murchou.\n";
    solo.removerPlanta();
}

char ErvaDaninha::getSimbolo() const {
    return 'E';
}

string ErvaDaninha::getNome() const{
    return "ErvaDaninha";
}

Planta* ErvaDaninha::reproduzPlanta(){
    ErvaDaninha* filho;
    filho = new ErvaDaninha(obtemAguaP(),obtemNutrientesP());
    setAgua(Settings::ErvaDaninha::nova_nutrientes);
    setNutrientes(Settings::ErvaDaninha::nova_nutrientes);
    return filho;
}