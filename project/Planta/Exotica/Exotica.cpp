//
// Created by jonhr on 31/10/2025.
//

#include "Exotica.h"

#include "../../Settings.h"
#include "../../Solo/Solo.h"

#include "../../Settings.h"
#include "../../Solo/Solo.h"

using namespace std;

Exotica::Exotica() {
    agua = Settings::Exotica::inicial_agua;
    nutrientes = Settings::Exotica::inicial_nutrientes;
    viva = true;
}

void Exotica::agir(Solo& solo) {
    // Perde água e nutrientes a cada ciclo
    agua -= Settings::Exotica::perda_agua;
    nutrientes -= Settings::Exotica::perda_nutrientes;

    // Absorve do solo
    solo.retiraNutrientes(Settings::Exotica::absorcao_nutrientes);
    solo.adicionaAgua(Settings::Exotica::absorcao_agua);

    // Morre se não tiver condições ideais
    if (agua < Settings::Exotica::morre_agua_menor ||
        nutrientes < Settings::Exotica::morre_nutrientes_menor ||
        nutrientes > Settings::Exotica::morre_nutrientes_maior)
    {
        morrer(solo);
    }
}

void Exotica::morrer(Solo& solo) {
    viva = false;
    cout << "Uma Exotica murchou.\n";
    solo.removerPlanta();
}

char Exotica::getSimbolo() const {
    return 'E';
}

string Exotica::getNome() const{
    return "Exotica";
}