//
// Created by jonhr on 31/10/2025.
//

#include "Tesoura.h"
#include "../../Solo/Solo.h"
#include "../../Jardim/Jardim.h"
#include "../../Planta/Planta.h"

void Tesoura::utiliza(Solo& solo) {
    Planta* planta = solo.obterPlanta();
    if (!planta ) {
        return;
    }

    if ( planta->isFeia() ) {
        solo.removerPlanta();
    }
}
