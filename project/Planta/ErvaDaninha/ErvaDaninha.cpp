//
// Created by jonhr on 31/10/2025.
//

#include <iostream>
#include "ErvaDaninha.h"
#include "../../Settings.h"
#include "../../Solo/Solo.h"

using namespace std;

ErvaDaninha::ErvaDaninha(int ag, int nut) : Planta(ag, nut), ultimaReproducao(0) {
}

Planta* ErvaDaninha::clone() const {
    return new ErvaDaninha(*this);
}

void ErvaDaninha::agir(Solo& solo) {
    aumentaTempoVida();

    // Absorve água
    if (solo.obtemAgua() >= Settings::ErvaDaninha::absorcao_agua) {
        solo.modificaAgua(Settings::ErvaDaninha::absorcao_agua * -1);
        alteraAgua(Settings::ErvaDaninha::absorcao_agua);
    } else if (solo.obtemAgua() > 0) {
        alteraAgua(solo.obtemAgua());
        solo.modificaAgua(solo.obtemAgua() * -1);
    }

    // Absorve nutrientes
    if (solo.obtemNutrientes() >= Settings::ErvaDaninha::absorcao_nutrientes) {
        solo.modificaNutrientes(Settings::ErvaDaninha::absorcao_nutrientes * -1);
        alteraNutrientes(Settings::ErvaDaninha::absorcao_nutrientes);
    } else if (solo.obtemNutrientes() > 0) {
        alteraNutrientes(solo.obtemNutrientes());
        solo.modificaNutrientes(solo.obtemNutrientes() * -1);
    }

    // Morre aos 60 instantes (usa >= para não falhar)
    if (obtemTempoVida() >= Settings::ErvaDaninha::morre_instantes) {
        morrer(solo, cout);
    }
}

void ErvaDaninha::morrer(Solo& solo, ostream& out) {
    alteraViva(false);
    out << "Uma " << getNome() << " murchou.\n";
    solo.removerPlanta();
}

char ErvaDaninha::getSimbolo() const {
    return 'E';
}

string ErvaDaninha::getNome() const {
    return "ErvaDaninha";
}

bool ErvaDaninha::podeReproduzir() {
    // >30 nutrientes e passaram 5 instantes desde a última reprodução
    if (obtemNutrientesP() > Settings::ErvaDaninha::multiplica_nutrientes_maior &&
        (obtemTempoVida() - ultimaReproducao) >= Settings::ErvaDaninha::multiplica_instantes) {
        return true;
    }
    return false;
}

Planta* ErvaDaninha::reproduzPlanta() {
    // última reprodução aqui
    ultimaReproducao = obtemTempoVida();

    // Filho nasce com os valores iniciais
    ErvaDaninha* filho = new ErvaDaninha(Settings::ErvaDaninha::inicial_agua,
                                         Settings::ErvaDaninha::inicial_nutrientes);
    return filho;
}
