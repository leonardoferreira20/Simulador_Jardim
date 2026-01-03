//
// Created by Leonardo Ferreira on 25/10/2025.
//

#include "Planta.h"
#include "../Jardim/Jardim.h"
#include "../Solo/Solo.h"

Planta::Planta(int ag, int nut) : agua(ag), nutrientes(nut), viva(true), recemNascida(false){
}

void Planta::tentaReproduzir(Jardim& jardim, int linha, int coluna) {
    if (!estaViva())
        return;

    if (isRecemNascida())
        return;

    if (!podeReproduzir())
        return;

    bool podeOcupado = reproduzEmSoloOcupado();
    int permiteOcupado = podeOcupado ? 1 : 0;

    Solo* destino = jardim.soloParaReproduzir(linha, coluna, permiteOcupado);
    if (destino == nullptr)
        return;

    if (podeOcupado && destino->temPlanta()) {
        destino->removerPlanta();
    }

    Planta* filho = reproduzPlanta();
    if (filho == nullptr)
        return;

    filho->setRecemNascida(true);
    destino->criarPlanta(filho);
}

