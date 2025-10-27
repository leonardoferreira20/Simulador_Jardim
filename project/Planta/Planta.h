//
// Created by Leonardo Ferreira on 25/10/2025.
//

#ifndef PLANTA_H
#define PLANTA_H

#include <iostream>
#include "../Solo/Solo.h"
#include "../Settings.h"

using namespace std;

/**
 * @class Planta
 * @brief Classe base abstrata que representa uma planta genérica no jardim.
 *
 * Esta classe define os atributos e comportamentos comuns a todas as plantas,
 * como a quantidade de água, nutrientes e o estado de vida.
 * As subclasses (Cacto, Roseira, etc.) implementam o seu comportamento específico
 * através dos métodos virtuais puros.
 */
class Planta {

public:
    int agua;
    int nutrientes;
    bool viva;

    Planta();
    virtual ~Planta() = default;

    // Métodos abstratos (a serem implementados pelas subclasses)
    virtual void agir(Solo& solo) = 0;         ///< Comportamento da planta a cada ciclo
    virtual void morrer(Solo& solo) = 0;       ///< Define o que acontece quando a planta morre
    virtual char getSimbolo() const = 0;       ///< Retorna o símbolo usado na grelha

    // Métodos comuns a todas as plantas
    bool estaViva() const;
    void adicionarAgua(int quant);
    void adicionarNutrientes(int quant);
};

#endif // PLANTA_H
