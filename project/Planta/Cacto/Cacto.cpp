//
// Created by Leonardo Ferreira on 25/10/2025.
//

#include "Cacto.h"
#include "../../Solo/Solo.h"
#include <iostream>

using namespace std;

Cacto::Cacto(int ag, int nut)
    : Planta(ag, nut), contaAguaAlta(0), contaNutZero(0), nutrientesAbsorvidos(0) {
}

Planta* Cacto::clone() const {
    return new Cacto(*this);
}

void Cacto::agir(Solo& solo) {
    aumentaTempoVida();

    //
    int aguaSolo = solo.obtemAgua();
    int qtdAgua = aguaSolo * Settings::Cacto::absorcao_agua_percentagem / 100;

    if (qtdAgua > 0) {
        solo.modificaAgua(-qtdAgua);
        alteraAgua(qtdAgua);
    }

    //
    int nutSolo = solo.obtemNutrientes();
    int qtdNut = 0;

    if (nutSolo >= Settings::Cacto::absorcao_nutrientes) {
        qtdNut = Settings::Cacto::absorcao_nutrientes;
    } else if (nutSolo > 0) {
        qtdNut = nutSolo;
    }

    if (qtdNut > 0) {
        solo.modificaNutrientes(-qtdNut);
        alteraNutrientes(qtdNut);
        nutrientesAbsorvidos += qtdNut;
    }

    // -
    if (solo.obtemAgua() > Settings::Cacto::morre_agua_solo_maior) {
        contaAguaAlta++;
    } else {
        contaAguaAlta = 0;
    }

    if (solo.obtemNutrientes() == 0) {
        contaNutZero++;
    } else {
        contaNutZero = 0;
    }

    // morre se agua > 100 durante 3 instantes seguidos
    // ou se nutrientes == 0 durante mais do que 3 instantes seguidos
    if (contaAguaAlta >= 3 || contaNutZero > 3) {
        morrer(solo, cout);
    }
}

void Cacto::morrer(Solo& solo, ostream& out) {
    alteraViva(false);

    // Ao morrer deixa no solo todos os nutrientes que absorveu durante a vida (a agua nao)
    if (nutrientesAbsorvidos > 0) {
        solo.modificaNutrientes(nutrientesAbsorvidos);
    }

    out << "Morreu um " << getNome() << endl;
    solo.removerPlanta();
}

char Cacto::getSimbolo() const {
    return 'C';
}

string Cacto::getNome() const {
    return "Cacto";
}

bool Cacto::podeReproduzir() {
    // multiplica se nutr > 100 e agua > 50
    if (obtemNutrientesP() > Settings::Cacto::multiplica_nutrientes_maior &&
        obtemAguaP() > Settings::Cacto::multiplica_agua_maior) {
        return true;
    }
    return false;
}

Planta* Cacto::reproduzPlanta() {
    // divide água e nutrientes em partes iguais entre o original e o novo
    int filhoAgua = obtemAguaP() / 2;
    int filhoNut  = obtemNutrientesP() / 2;

    int paiAgua = obtemAguaP() - filhoAgua;
    int paiNut  = obtemNutrientesP() - filhoNut;

    setAgua(paiAgua);
    setNutrientes(paiNut);

    Cacto* filho = new Cacto(filhoAgua, filhoNut);
    return filho;
}
