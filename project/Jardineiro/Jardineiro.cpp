//
// Created by Leonardo Ferreira on 11/10/2025.
//

#include <iostream>
#include "Jardineiro.h"

using namespace std;

/// AÇÕES DO JARDINEIRO
void Jardineiro::entrar(int l, int c) {
    // ACHAMOS QUE FIZESSE SENTIDO TER ISTO VISTO QUE O JARDINEIRO JÁ ESTÁ DENTRO DO JARDIM
    // MAS COMO O RELATÓRIO PEDIA OUTRA COISA OPTAMOS POR DEIXAR COMENTADO
    /*if (dentro) {
        cout << "Erro: O jardineiro já está dentro do jardim.\n";
        return;
    }*/

    if (contaEntradas >= Settings::Jardineiro::max_entradas_saidas && contaSaidas >= Settings::Jardineiro::max_entradas_saidas) {
        cout << "Erro: Limite de entradas do dia atingido! Avance para o dia seguinte.\n";
        return;
    }

    linha = l;
    coluna = c;
    dentro = true;
    contaEntradas++;
    cout << "Jardineiro entrou em (" << char('A' +l) << "," << char('A' + c) << ")\n";
}

void Jardineiro::sair() {
    if (!dentro) {
        cout << "Erro: O jardineiro já está fora do jardim.\n";
        return;
    }

    dentro = false;
    linha = -1;
    coluna = -1;
    contaSaidas++;
    cout << "Jardineiro saiu do jardim.\n";
}

void Jardineiro::mover(char dir) {
    if (contaMov >= Settings::Jardineiro::max_movimentos) {
        cout << "Erro: Limite de movimentos atingido!\n";
        return;
    }

    switch (dir) {
        case 'e': coluna--; break;
        case 'd': coluna++; break;
        case 'c': linha--;  break;
        case 'b': linha++;  break;
        default:
            cout << "Erro: Direcao invalida!\n";
        return;
    }

    contaMov++;
    cout << "Jardineiro moveu-se para (" << char('A' + linha) << "," << char('A'+ coluna) << ") - <" << Settings::Jardineiro::max_movimentos - contaMov << " movimentos restantes>\n";
}

/// VERIFICAÇÕES DE PLANTAÇÕES E COLHEITAS
bool Jardineiro::podePlantar() {
    return contaPlantacoes < Settings::Jardineiro::max_plantacoes;
}

bool Jardineiro::podeColher() {
    return contaColheitas < Settings::Jardineiro::max_colheitas;
}

/// REGISTO DE PLANTAÇÕES E COLHEITAS
void Jardineiro::registaPlantacao() {
    contaPlantacoes++;
}

void Jardineiro::registaColheita() {
    contaColheitas++;
}

/// RESETAR CONTADORES
void Jardineiro::resetContadores() {
    contaMov = 0;
    contaEntradas = 0;
    contaPlantacoes = 0;
    contaColheitas = 0;
}

/// FERRAMENTAS
Ferramenta* Jardineiro::obterFerramentaNaMao() const {
    return naMao;
};