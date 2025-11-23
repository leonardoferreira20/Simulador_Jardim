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

    // CONTADORES
    int contaReset;

    int contaMov;
    int contaEntradas;
    int contaSaidas;
    int contaPlantacoes;
    int contaColheitas;

    // FERRAMENTAS
    Ferramenta* mao;
    Ferramenta** inventario;
    int capacidadeInv;
    int tamanhoInv;

public:
    Jardineiro();
    ~Jardineiro();

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
    void expandirInventario();
    void adicionarFerramenta(Ferramenta* f);
    bool pegarFerramenta(int numSerie);
    void largarFerramenta();
    Ferramenta* getFerramentaInventario(int index) const;
    /*void pegar(Ferramenta*);
    void largar(Solo&);*/
};

#endif //JARDINEIRO_H
