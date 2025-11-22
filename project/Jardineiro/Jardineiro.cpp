//
// Created by Leonardo Ferreira on 11/10/2025.
//

#include <iostream>
#include "Jardineiro.h"
#include "../Settings.h"

using namespace std;

Jardineiro::Jardineiro() : linha(-1), coluna(-1), dentro(false), contaMov(0), contaEntradas(0), contaSaidas(0),
    contaPlantacoes(0), contaColheitas(0), mao(nullptr), capacidadeInv(10), tamanhoInv(0) {

    inventario = new Ferramenta*[capacidadeInv];
    for (int i = 0; i < capacidadeInv; i++) {
        inventario[i] = nullptr;
    }
}

Jardineiro::~Jardineiro() {
    delete mao;
    if (inventario != nullptr) {
        for (int i = 0; i < tamanhoInv; i++) {
            delete inventario[i];
        }
        delete[] inventario;
    }
}

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
    return mao;
};

void Jardineiro::expandirInventario() {
    int novaCapacidade = capacidadeInv * 2;
    Ferramenta** novoInv = new Ferramenta*[novaCapacidade];

    for (int i = 0; i < tamanhoInv; i++) {
        novoInv[i] = inventario[i];
    }

    for (int i = tamanhoInv; i < novaCapacidade; i++) {
        novoInv[i] = nullptr;
    }

    delete[] inventario;
    inventario = novoInv;
    capacidadeInv = novaCapacidade;
}

void Jardineiro::adicionarFerramenta(Ferramenta* f) {
    if (f == nullptr) return;

    if (tamanhoInv >= capacidadeInv) {
        expandirInventario();
    }

    inventario[tamanhoInv] = f;
    tamanhoInv++;

    cout << "Ferramenta " << f->getNome() << " (numero " << f->getNSerie() << ") adicionada ao inventário.\n";
}

bool Jardineiro::pegarFerramenta(int numSerie) {
    int indice = -1;

    for (int i = 0; i < tamanhoInv; i++) {
        if (inventario[i]->getNSerie() == numSerie) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        cout << "Ferramenta com número de série " << numSerie << " não encontrada no inventário.\n";
        return false;
    }

    if (obterFerramentaNaMao() != nullptr) {
        adicionarFerramenta(obterFerramentaNaMao());
    }

    mao = inventario[indice];

    for (int i = indice; i < tamanhoInv - 1; i++) {
        inventario[i] = inventario[i + 1];
    }
    inventario[tamanhoInv - 1] = nullptr;
    tamanhoInv--;

    cout << "Ferramenta " << obterFerramentaNaMao()->getNome() << " (numero " << obterFerramentaNaMao()->getNSerie() << ") agora está na mão.\n";
    return true;
}

void Jardineiro::largarFerramenta() {
    if (obterFerramentaNaMao() == nullptr) {
        cout << "Não há ferramenta na mão para largar.\n";
        return;
    }

    cout << "Ferramenta " << obterFerramentaNaMao()->getNome() << " (numero " << obterFerramentaNaMao()->getNSerie() << ") guardada no inventário.\n";

    adicionarFerramenta(obterFerramentaNaMao());
    mao = nullptr;
}

Ferramenta* Jardineiro::getFerramentaInventario(int index) const {
    if (index >= 0 && index < tamanhoInv) {
        return inventario[index];
    }
    return nullptr;
}