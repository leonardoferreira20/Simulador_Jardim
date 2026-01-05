//
// Created by jonhr on 31/10/2025.
//

#include "Regador.h"
#include "../../Solo/Solo.h"
#include "../../Jardim/Jardim.h"

void Regador::utiliza(Solo& solo, ostream& out) {
    if ( !estaVazia() ) {
        solo.modificaAgua(getConsumo());  // +10 água no solo
        reduzirCapacidade();                // -10 do regador

        out << "Regador usado: +" << getConsumo() << " agua no solo (regador: " << getCapacidade() << "/" << Settings::Regador::capacidade << ")\n";
    }
}