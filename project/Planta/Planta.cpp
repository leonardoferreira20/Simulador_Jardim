//
// Created by Leonardo Ferreira on 25/10/2025.
//

#include "Planta.h"

Planta::Planta() : agua(0), nutrientes(0), viva(true) {}

bool Planta::estaViva() const {
    return viva;
}

void Planta::adicionarAgua(int quant) {
    agua += quant;
}

void Planta::adicionarNutrientes(int quant) {
    nutrientes += quant;
}
