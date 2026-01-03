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

    // recém-nascida não reproduz
    if (isRecemNascida())
        return;

    // tem de cumprir as regras da própria planta
    if (!podeReproduzir())
        return;

    // escolher destino: se for erva daninha pode ser ocupado
    int permiteOcupado = reproduzEmSoloOcupado() ? 1 : 0;
    Solo* destino = jardim.soloParaReproduzir(linha, coluna, permiteOcupado);

    if (destino == nullptr)
        return;

    // Se permite substituir (erva daninha), mata a planta existente
    if (reproduzEmSoloOcupado() && destino->temPlanta()) {
        destino->removerPlanta();
        cout << "morreu" << endl; // mantive a tua mensagem
    }

    Planta* filho = reproduzPlanta();
    if (filho == nullptr)
        return;

    filho->setRecemNascida(true);
    destino->criarPlanta(filho);
}
