//
// Created by Leonardo Ferreira on 11/10/2025.
//

#ifndef JARDIM_H
#define JARDIM_H

#include <iostream>

using namespace std;

class Solo;
class Jardineiro;

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
    Jardineiro* jardineiro;

    int valorRandom2 (int min, int max) {return min + rand() %  (max - min + 1);}

    public:
        Jardim(int lin, int col);
        ~Jardim();
        Jardim(const Jardim& outro);

        int getNumLinhas () const { return nLinhas; }
        int getNumColunas () const { return nColunas; }

        string imprimir () const;
        void avanca();
        bool planta(int linha, int coluna, char tipo, ostream& out);
        bool colhe(int linha, int coluna, ostream& out);
        string listarPlantas();
        string listarPlanta(int linha, int coluna);
        Solo* getSolo(int linha, int coluna);
        Jardineiro& getJardineiro() const;
        bool posicaoValida(int linha, int coluna) const;
        Solo* soloParaReproduzir(int lin, int col,int ErvaDaninha);

        // FERRAMENTAS
        bool spawnFerramentaAleatoria();
        string verificarEApanharFerramenta();
};


#endif //JARDIM_H
