//
// Created by jonhr on 31/10/2025.
//

#include "Tesoura.h"
#include "../../Solo/Solo.h"
#include "../../Jardim/Jardim.h"
#include "../../Planta/Planta.h"

void Tesoura::utiliza(Solo& solo, ostream& out) {
    if ( solo.temPlanta() ) {
        Planta* planta = solo.obterPlanta();

        if ( planta->isFeia() ) {
            solo.removerPlanta();
            out << "Tesoura usada! Planta feia '" << planta->getNome() << "' eliminada!\n";
        }else {
            out << "Tesoura não cortou (planta não é feia)\n";
        }
    }else {
        out << "Tesoura não cortou (não há planta aqui)\n";
    }
}
