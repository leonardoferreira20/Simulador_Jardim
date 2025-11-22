//
// Created by jonhr on 31/10/2025.
//

#include "VaraEspecial.h"
#include "../../Solo/Solo.h"
#include "../../Jardim/Jardim.h"

using namespace std;

void VaraEspecial::utiliza(Solo& solo) { // ARGUMENTO SOLO IGNORADO PROPOSITADAMENTE
    if ( estaVazia() ) {
        cout << "A ferramenta, " << getNome() << ", atingiu o limite da sua capacidade.\n";
        return;
    }

    int aguaAtual = solo.obtemAgua();
    solo.modificaAgua(100-aguaAtual);

    reduzirCapacidade();
}