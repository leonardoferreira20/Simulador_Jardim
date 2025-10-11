//
// Created by Leonardo Ferreira on 11/10/2025.
//

#ifndef JARDIM_H
#define JARDIM_H

#include <string>
#include "../Solo/Solo.h"

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
    public:
        // Constructor
        Jardim(int lin, int col);

        // Destrutor
        //~Jardim();

        void imprimir () const;
        void executaComando(const string& comando);
        void avanca(int n);
        //Solo* getSolo(int linha, int coluna);
    private:
        int nLinhas;
        int nColunas;
};



#endif //JARDIM_H
