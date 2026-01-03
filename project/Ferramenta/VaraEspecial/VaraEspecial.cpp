//
// Created by jonhr on 31/10/2025.
//

#include "VaraEspecial.h"
#include "../../Solo/Solo.h"
#include "../../Jardim/Jardim.h"

using namespace std;

void VaraEspecial::utiliza(Solo& solo, ostream& out) {
    int aguaAtual = solo.obtemAgua();
    int nutrientesAtual = solo.obtemNutrientes();

    if ( !estaVazia() ) {
        solo.modificaAgua(100-aguaAtual);
        solo.modificaNutrientes(100-nutrientesAtual);

        reduzirCapacidade();

        out << "Vara especial usada: +" << 100-nutrientesAtual << " nutrientes e +" << 100-aguaAtual << " agua no solo.\n Vara especial: " << getCapacidade() << "/" << Settings::VaraEspecial::capacidade << ")\n";
    }
}