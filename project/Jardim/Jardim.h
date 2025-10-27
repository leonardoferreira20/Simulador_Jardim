//
// Created by Leonardo Ferreira on 11/10/2025.
//

#ifndef JARDIM_H
#define JARDIM_H

#include <iostream>

#include "../Solo/Solo.h"
#include "../Jardineiro/Jardineiro.h"

using namespace std;

/**
 * @class Jardim
 *
 * @brief Representa o ambiente principal da simulação.
 * Esta classe contém a grelha de solo (estrutura retangular de células),
 * o jardineiro e os métodos responsáveis por atualizar e imprimir o estado
 * do jardim. Também processa os comandos e controla o avanço temporal da simulação.
 */
class Jardim {
    int nLinhas;
    int nColunas;
    Solo** grid;
    Jardineiro jardineiro;

    public:
        Jardim(int lin, int col);
        ~Jardim();

        void imprimir () const;
        void avanca(int n);
        Solo* getSolo(int linha, int coluna);
};


#endif //JARDIM_H
