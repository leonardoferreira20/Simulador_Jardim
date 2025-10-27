//
// Created by Leonardo Ferreira on 11/10/2025.
//

#include "Jardim.h"
#include "../Planta/Cacto/Cacto.h"
#include "../Planta/Roseira/Roseira.h"
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
    for (int i = 0; i < n; i++) {
        for (int l = 0; l < nLinhas; l++) {
            for (int c = 0; c < nColunas; c++) {
                Planta* planta = grid[l][c].obterPlanta();
                if ( planta != nullptr && planta->estaViva() ) {
                    planta->agir(grid[l][c]);
                }
            }
        }
    }
};

bool Jardim::planta(int linha, int coluna, char tipo) {
    // Verifica se o jardim foi criado
    if (linha < 0 || linha >= nLinhas || coluna < 0 || coluna >= nColunas) {
        cout << "Posição inválida (" << linha << ", " << coluna << ").\n";
        return false;
    }

    Solo* solo = &grid[linha][coluna];

    // Verifica se a célula já tem planta
    if (solo->obterPlanta() != nullptr) {
        cout << "Já existe uma planta nessa posição.\n";
        return false;
    }

    // Cria a planta conforme o tipo
    Planta* novaPlanta = nullptr;
    tipo = tolower(tipo);

    switch (tipo) {
        case 'c': novaPlanta = new Cacto(); break;
        case 'r': novaPlanta = new Roseira(); break;
        //case 'e': nova = new ErvaDaninha(); break;
        //case 'x': nova = new Exotica(); break;
        default:
            cout << "Tipo de planta desconhecido.\n";
        return false;
    }

    solo->criarPlanta(novaPlanta);
    cout << "Planta " << novaPlanta->getNome() << " plantada em (" << char('A' + linha) << ", " << char('A' + coluna) << ").\n";
    return true;
}

bool Jardim::colhe(int linha, int coluna){
    if (linha < 0 || linha >= nLinhas || coluna < 0 || coluna >= nColunas) {
        cout << "Coordenadas fora do jardim!\n";
        return false;
    }

    Solo* solo = &grid[linha][coluna];

    if ( solo->obterPlanta() != nullptr ) {
        Planta* planta = solo->obterPlanta();

        solo->removerPlanta();
        cout << "A planta " << planta->getNome() << " foi colhida na posição (" << char('A' + linha) << ", " << char('A' + coluna) << ").\n";
        return true;
    }
    return false;
}
