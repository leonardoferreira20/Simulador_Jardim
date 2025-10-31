//
// Created by Leonardo Ferreira on 11/10/2025.
//

#include <iostream>
#include "Jardineiro.h"

using namespace std;

bool Jardineiro::estaDentro() const {
    return dentro;
}

int Jardineiro::getLinha() const {
    return linha;
}

int Jardineiro::getColuna() const {
    return coluna;
}

void Jardineiro::entrar(int l, int c) {
    linha = l;
    coluna = c;
    dentro = true;
    cout << "Jardineiro entrou em (" << char('A' +l) << "," << char('A' + c) << ")\n";
}

void Jardineiro::sair() {
    dentro = false;
    cout << "Jardineiro saiu do jardim.\n";
}

void Jardineiro::mover(char dir) {
    cout << "Mover: " << dir << " (não implementado ainda)\n";
}

void Jardineiro::setPosicao(int l, int c) {
    linha = l;
    coluna = c;
}