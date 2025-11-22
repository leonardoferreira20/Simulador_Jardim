//
// Created by jonhr on 31/10/2025.
//

#include "Regador.h"
#include "../../Solo/Solo.h"
#include "../../Jardim/Jardim.h"

void Regador::utiliza(Solo& solo) {
    if ( estaVazia() ) {
        cout << "A ferramenta, " << getNome() << ", atingiu o limite da sua capacidade.\n";
        return;
    }

    solo.modificaAgua(10);// VERIFICAR VALOR !!
    reduzirCapacidade();
}