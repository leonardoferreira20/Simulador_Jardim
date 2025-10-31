//
// Created by Leonardo Ferreira on 11/10/2025.
//

#include <iostream>
#include "Jardineiro.h"

using namespace std;

void Jardineiro::entrar(int l, int c) {
    linha = l;
    coluna = c;
    dentro = true;
    cout << "Jardineiro entrou em (" << l << "," << c << ")\n";
}

void Jardineiro::sair() {
    dentro = false;
    cout << "Jardineiro saiu do jardim.\n";
}

void Jardineiro::mover(char dir) {
    cout << "Mover: " << dir << " (não implementado ainda)\n";
}