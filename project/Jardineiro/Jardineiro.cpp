//
// Created by Leonardo Ferreira on 11/10/2025.
//

#include <iostream>
#include <sstream>
#include "Jardineiro.h"
#include "../Settings.h"

using namespace std;

Jardineiro::Jardineiro() : linha(-1), coluna(-1), dentro(false), contaMov(0), contaEntradas(0), contaSaidas(0),
    contaPlantacoes(0), contaColheitas(0), mao(nullptr), capacidadeInv(10), tamanhoInv(0), contaReset(0) {

    inventario = new Ferramenta*[capacidadeInv];
    for (int i = 0; i < capacidadeInv; i++) {
        inventario[i] = nullptr;
    }
}

Jardineiro::Jardineiro(const Jardineiro& o)
    : linha(o.linha),
      coluna(o.coluna),
      dentro(o.dentro),
      contaReset(o.contaReset),
      contaMov(o.contaMov),
      contaEntradas(o.contaEntradas),
      contaSaidas(o.contaSaidas),
      contaPlantacoes(o.contaPlantacoes),
      contaColheitas(o.contaColheitas),
      mao(o.mao ? o.mao->clone() : nullptr),
      inventario(nullptr),
      capacidadeInv(o.capacidadeInv),
      tamanhoInv(o.tamanhoInv) {

    inventario = new Ferramenta*[capacidadeInv];
    for (int i = 0; i < capacidadeInv; i++) inventario[i] = nullptr;

    for (int i = 0; i < tamanhoInv; i++) {
        inventario[i] = o.inventario[i] ? o.inventario[i]->clone() : nullptr;
    }
}

Jardineiro::~Jardineiro() {
    delete mao;
    mao = nullptr;

    if (inventario != nullptr) {
        for (int i = 0; i < tamanhoInv; i++) {
            delete inventario[i];
            inventario[i] = nullptr;
        }
        delete[] inventario;
        inventario = nullptr;
    }
}

Jardineiro& Jardineiro::operator=(const Jardineiro& o) {
    if (this == &o) return *this;

    //Limpar estado atual
    delete mao;
    mao = nullptr;

    if (inventario != nullptr) {
        for (int i = 0; i < tamanhoInv; i++) {
            delete inventario[i];
            inventario[i] = nullptr;
        }
        delete[] inventario;
        inventario = nullptr;
    }

    //Copiar valores simples
    linha = o.linha;
    coluna = o.coluna;
    dentro = o.dentro;

    contaReset = o.contaReset;
    contaMov = o.contaMov;
    contaEntradas = o.contaEntradas;
    contaSaidas = o.contaSaidas;
    contaPlantacoes = o.contaPlantacoes;
    contaColheitas = o.contaColheitas;

    capacidadeInv = o.capacidadeInv;
    tamanhoInv = o.tamanhoInv;

    //Clonar ferramentas
    mao = o.mao ? o.mao->clone() : nullptr;

    inventario = new Ferramenta*[capacidadeInv];
    for (int i = 0; i < capacidadeInv; i++) inventario[i] = nullptr;

    for (int i = 0; i < tamanhoInv; i++) {
        inventario[i] = o.inventario[i] ? o.inventario[i]->clone() : nullptr;
    }

    return *this;
}

/// AÇÕES DO JARDINEIRO
string Jardineiro::entrar(int l, int c) {
    ostringstream oss;
    // ACHAMOS QUE FIZESSE SENTIDO TER ISTO VISTO QUE O JARDINEIRO JÁ ESTÁ DENTRO DO JARDIM
    // MAS COMO O RELATÓRIO PEDIA OUTRA COISA OPTAMOS POR DEIXAR COMENTADO
    /*if (dentro) {
        cout << "Erro: O jardineiro já está dentro do jardim.\n";
        return;
    }*/
    if (!dentro && contaEntradas >= Settings::Jardineiro::max_entradas_saidas && contaSaidas >= Settings::Jardineiro::max_entradas_saidas) {
        oss << "Erro: Limite de entradas do dia atingido! Avance para o dia seguinte.\n";
        return oss.str();
    }

    linha = l;
    coluna = c;
    dentro = true;
    contaEntradas++;
    oss << "Jardineiro entrou em (" << char('A' +l) << "," << char('A' + c) << ")\n";
    return oss.str();
}

string Jardineiro::sair() {
    ostringstream oss;
    if (!dentro) {
        oss << "Erro: O jardineiro já está fora do jardim.\n";
        return oss.str();
    }

    dentro = false;
    linha = -1;
    coluna = -1;
    contaSaidas++;
    oss << "Jardineiro saiu do jardim.\n";
    return  oss.str();
}

string Jardineiro::mover(char dir) {
    ostringstream oss;
    if (contaMov >= Settings::Jardineiro::max_movimentos) {
        oss << "Erro: Limite de movimentos atingido!\n";
        return oss.str();
    }

    switch (dir) {
        case 'e': coluna--; break;
        case 'd': coluna++; break;
        case 'c': linha--;  break;
        case 'b': linha++;  break;
        default:
            oss << "Erro: Direcao invalida!\n";
        return oss.str();
    }

    contaMov++;
    oss << "Jardineiro moveu-se para (" << char('A' + linha) << "," << char('A'+ coluna) << ") - <" << Settings::Jardineiro::max_movimentos - contaMov << " movimentos restantes>\n";
    return oss.str();
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
    contaReset++;
    if (contaReset%2==0) {
        contaMov = 0;
        contaEntradas = 0;
        contaPlantacoes = 0;
        contaColheitas = 0;
    }
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

string Jardineiro::adicionarFerramenta(Ferramenta* f) {
    ostringstream oss;

    if (f == nullptr) return oss.str();

    if (tamanhoInv >= capacidadeInv) {
        expandirInventario();
    }

    inventario[tamanhoInv] = f;
    tamanhoInv++;

    oss << "Ferramenta " << f->getNome() << " (nº serie " << f->getNSerie() << ") adicionada ao inventário.\n";
    return oss.str();
}

bool Jardineiro::pegarFerramenta(int numSerie, ostream& out) {
    int indice = -1;

    for (int i = 0; i < tamanhoInv; i++) {
        if (inventario[i]->getNSerie() == numSerie) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        out << "Ferramenta com número de série " << numSerie << " não encontrada no inventário.\n";
        return false;
    }

    if (obterFerramentaNaMao() != nullptr) {
        out << adicionarFerramenta(obterFerramentaNaMao());
    }

    mao = inventario[indice];

    for (int i = indice; i < tamanhoInv - 1; i++) {
        inventario[i] = inventario[i + 1];
    }
    inventario[tamanhoInv - 1] = nullptr;
    tamanhoInv--;

    out << "Ferramenta " << obterFerramentaNaMao()->getNome() << " (numero " << obterFerramentaNaMao()->getNSerie() << ") agora está na mão.\n";
    return true;
}

void Jardineiro::removerFerramentaVazia() {
    // Remove e destrói a ferramenta que está na mão (quando fica vazia)
    if (mao != nullptr) {
        delete mao;
        mao = nullptr;
    }
}

string Jardineiro::largarFerramenta() {
    ostringstream oss;
    if (obterFerramentaNaMao() == nullptr) {
        oss << "Não há ferramenta na mão para largar.\n";
        return oss.str();
    }

    oss << "Ferramenta " << obterFerramentaNaMao()->getNome() << " (numero " << obterFerramentaNaMao()->getNSerie() << ") guardada no inventário.\n";

    oss << adicionarFerramenta(obterFerramentaNaMao());
    mao = nullptr;
    return oss.str();
}

Ferramenta* Jardineiro::getFerramentaInventario(int index) const {
    if (index >= 0 && index < tamanhoInv) {
        return inventario[index];
    }
    return nullptr;
}