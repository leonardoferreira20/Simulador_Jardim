//
// Created by Leonardo Ferreira on 11/10/2025.
//

#include "Jardim.h"
#include <iostream>

using namespace std;

Jardim::Jardim(int lin, int col) : nLinhas(lin), nColunas(col) {}

void Jardim::imprimir() const {
    cout << endl << "  ";
    for( int c = 0; c < nColunas; c++ ) {
        cout << char('A' + c) << " ";
    }
    cout << endl;

    for ( int l = 0; l < nLinhas; l++ ){
        cout << char('A' + l) << "  ";
        cout << endl;
    }
    cout << endl;
}


