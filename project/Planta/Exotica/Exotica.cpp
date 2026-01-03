#include <iostream>
#include "Exotica.h"
#include "../../Settings.h"
#include "../../Solo/Solo.h"

using namespace std;

Exotica::Exotica(int ag, int nut) : Planta(ag, nut) {}

Planta* Exotica::clone() const {
    return new Exotica(*this);
}

void Exotica::agir(Solo& solo) {
    aumentaTempoVida();

    solo.modificaNutrientes(Settings::Exotica::fertiliza_nutrientes);
    solo.modificaAgua(Settings::Exotica::fertiliza_agua);
}

void Exotica::morrer(Solo& solo, ostream& out) {
    alteraViva(false);
    out << "Uma " << getNome() << " murchou.\n";
    solo.removerPlanta();
}

char Exotica::getSimbolo() const { return 'x'; }
string Exotica::getNome() const { return "Exotica"; }

bool Exotica::isFeia() { return true; }

bool Exotica::podeReproduzir() {
    return false;
}

Planta* Exotica::reproduzPlanta() {
    return nullptr;
}
