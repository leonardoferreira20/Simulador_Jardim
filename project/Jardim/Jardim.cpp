//
// Created by Leonardo Ferreira on 11/10/2025.
//

#include "Jardim.h"
#include <iostream>

using namespace std;

Jardim::Jardim(int lin, int col) : nLinhas(lin), nColunas(col) {
    grid = new Solo*[nLinhas];
    for (int i = 0; i < nLinhas; i++)
        grid[i] = new Solo[nColunas];
}

Jardim::~Jardim() {
    for (int i = 0; i < nLinhas; i++)
        delete[] grid[i];
    delete[] grid;
}

void Jardim::imprimir() const {
    cout << endl << "   ";
    for( int c = 0; c < nColunas; c++ ) {
        cout << char('A' + c) << " ";
    }
    cout << endl;

    for ( int l = 0; l < nLinhas; l++ ){
        cout << char('A' + l) << "  ";

        for (int c = 0; c < nColunas; c++) {
            grid[l][c].imprimir();
            cout << " ";
        }

        cout << endl;
    }
    cout << endl;
}

void Jardim::avanca(int n) {
    /// Vai atuar sobre as PLANTAS que estão no SOLO
    for (int ciclo = 0; ciclo < n; ciclo++) {
        for (int l = 0; l < nLinhas; l++) {
            for (int c = 0; c < nColunas; c++) {
                Solo* s = getSolo(l, c);
                if (s->obterPlanta() != nullptr)
                    s->obterPlanta()->agir(s);
            }
        }
    }
};




