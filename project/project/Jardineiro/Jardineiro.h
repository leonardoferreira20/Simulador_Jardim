//
// Created by Leonardo Ferreira on 11/10/2025.
//

#ifndef JARDINEIRO_H
#define JARDINEIRO_H

#include "../Ferramenta/Ferramenta.h"

class Ferramenta;

class Jardineiro {
    int linha;
    int coluna;
    bool dentro;

    Ferramenta* naMao;
    int contaReset;

    int contaMov;
    int contaEntradas;
    int contaSaidas;
    int contaPlantacoes;
    int contaColheitas;


public:
    Jardineiro() : linha(-1), coluna(-1), dentro(false),
          contaMov(0), contaEntradas(0), contaSaidas(0),
          contaPlantacoes(0), contaColheitas(0), contaReset(0) {}

    bool estaDentro() const { return dentro; };
    int getLinha() const { return linha; };
    int getColuna() const { return coluna; };

    /// AÇÕES DO JARDINEIRO
    void entrar(int l, int c);
    void sair();
    void mover(char dir);

    /// VERIFICAÇÕES DE PLANTAÇÕES E COLHEITAS
    bool podePlantar();
    bool podeColher();

    /// REGISTO DE PLANTAÇÕES E COLHEITAS
    void registaPlantacao();
    void registaColheita();

    /// RESETAR CONTADORES
    void resetContadores();

    /// FERRAMENTAS
    bool temFerramenta() const;
    Ferramenta* obterFerramentaNaMao() const;
};

#endif //JARDINEIRO_H
