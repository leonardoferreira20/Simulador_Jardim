//
// Created by Leonardo Ferreira on 11/10/2025.
//

#include "Jardim.h"
#include <iostream>

using namespace std;

Jardim::Jardim(int lin, int col) : nLinhas(lin), nColunas(col) {}

void Jardim::imprimir() const {
    std::cout << "   ";
    for (int c = 0; c < nColunas; c++)
        std::cout << char('A' + c) << " ";
    std::cout << std::endl;

    for (int l = 0; l < nLinhas; l++) {
        std::cout << char('A' + l) << "  ";
        for (int c = 0; c < nColunas; c++) {
            //std::cout << grid[l][c].imprimir() << " ";
        }
        std::cout << std::endl;
    }
}


