//
// Created by jonhr on 31/10/2025.
//

#include "Adubo.h"
#include "../../Solo/Solo.h"
#include "../../Jardim/Jardim.h"
#include "../../Settings.h"

void Adubo::utiliza(Solo& solo, ostream& out) {
    if ( !estaVazia() ) {
        solo.modificaNutrientes(getConsumo()); // +10 nutrientes no solo
        reduzirCapacidade();                      // -10 do adubo

        out << "Adubo usado: +" << getConsumo() << " nutrientes no solo (adubo: " << getCapacidade() << "/" << Settings::Adubo::capacidade << ")\n";
    }
}
