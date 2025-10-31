//
// Created by jonhr on 31/10/2025.
//

#include "ErvaDaninha.h"

#include "../../Settings.h"
#include "../../Solo/Solo.h"


ErvaDaninha::ErvaDaninha() {
    agua = Settings::ErvaDaninha::inicial_agua;
    nutrientes = Settings::ErvaDaninha::inicial_nutrientes;
    instantes = 0;
    viva = true;
}

void ErvaDaninha::agir(Solo& solo) {
    // Diminui a variavel instantes se chegar a 0 morre
    instantes+=1;

    // Absorve do solo
    solo.retiraNutrientes(Settings::ErvaDaninha::absorcao_nutrientes);
    solo.adicionaAgua(Settings::ErvaDaninha::absorcao_agua);

    // Morre
    if (instantes == Settings::ErvaDaninha::morre_instantes)
    {
        morrer(solo);
    }
    //Multiplicação
    if (nutrientes > Settings::ErvaDaninha::multiplica_nutrientes_maior) {

    }
}

void ErvaDaninha::morrer(Solo& solo) {
    viva = false;
    cout << "Uma ErvaDaninha murchou.\n";
    solo.removerPlanta();
}

char ErvaDaninha::getSimbolo() const {
    return 'E';
}

string ErvaDaninha::getNome() const{
    return "ErvaDaninha";
}