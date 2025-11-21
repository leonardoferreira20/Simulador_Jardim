//
// Created by Leonardo Ferreira on 11/10/2025.
//

#include "Jardim.h"
#include "../Planta/Cacto/Cacto.h"
#include "../Planta/Roseira/Roseira.h"
#include "../Planta/ErvaDaninha/ErvaDaninha.h"
#include "../Planta/Exotica/Exotica.h"
#include <iostream>

using namespace std;
int valorRandom2 (int min, int max) {return min + rand() %  (max - min + 1);}

Jardim::Jardim(int lin, int col) : nLinhas(lin), nColunas(col) {
    jardineiro = new Jardineiro();
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

            if ( jardineiro->estaDentro() && jardineiro->getLinha() == l && jardineiro->getColuna() == c) {
                cout << "*";
            }else {
                grid[l][c].imprimir();
            }

            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}

Solo* Jardim::soloParaReproduzir(int linha, int col, int ErvaDaninha) {
    int livresL[8];
    int livresC[8];
    int count = 0;
    int indice, linhaEscolhida, colunaEscolhida;

    for (int i = linha - 1; i <= linha + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {

            if (i == linha && j == col)
                continue;

            if (!posicaoValida(i, j))
                continue;

            Solo* s = getSolo(i, j);

            if (!s->temPlanta()) {
                livresL[count] = i;
                livresC[count] = j;
                count++;
            }

            if (s->temPlanta() && ErvaDaninha == 1) {
                livresL[count] = i;
                livresC[count] = j;
                count++;
            }

        }
    }

    if (count == 0)
        return nullptr;

    indice = valorRandom2(0, count - 1);
    linhaEscolhida = livresL[indice];
    colunaEscolhida = livresC[indice];

    return getSolo(linhaEscolhida, colunaEscolhida);
}

void Jardim::avanca(int n) {
    for (int i = 0; i < n; i++) {
        for (int l = 0; l < nLinhas; l++) {
            for (int c = 0; c < nColunas; c++) {
                Planta* planta = grid[l][c].obterPlanta();

                if (planta != nullptr && planta->estaViva() ) {
                    if ( !planta->isRecemNascida() && planta->podeReproduzir()) {
                        Solo* plantar;
                        if (planta->getSimbolo() != 'E') {
                            plantar = soloParaReproduzir(l,c,0);
                        }
                        else {
                            plantar = soloParaReproduzir(l,c,1);
                        }
                        if (plantar != nullptr) {
                            Planta* filho = planta->reproduzPlanta();
                            if (filho != nullptr) {
                                if (planta->getSimbolo() == 'E') {
                                    plantar->removerPlanta();cout<<"morreu"<<endl;
                                };
                                filho->setRecemNascida(true);
                                plantar->criarPlanta(filho);
                            }
                        }
                    }
                    planta->agir(grid[l][c]);
                }
            }
        }

        // RESET DE TODOS OS TRUES ADICIONADOS NA REPRODUÇÃO
        for (int l = 0; l < nLinhas; l++) {
            for (int c = 0; c < nColunas; c++) {
                Planta* p = grid[l][c].obterPlanta();
                if (p != nullptr && p->isRecemNascida()) {
                    p->setRecemNascida(false);
                }
            }
        }

    }
}

bool Jardim::planta(int linha, int coluna, char tipo) {
    if (linha < 0 || linha >= nLinhas || coluna < 0 || coluna >= nColunas) {
        cout << "Posição inválida (" << linha << ", " << coluna << ").\n";
        return false;
    }

    Solo* solo = &grid[linha][coluna];

    if (solo->obterPlanta() != nullptr) {
        cout << "Já existe uma planta nessa posição.\n";
        return false;
    }

    Planta* novaPlanta = nullptr;
    tipo = tolower(tipo);

    switch (tipo) {
        case 'c': novaPlanta = new Cacto(); break;
        case 'r': novaPlanta = new Roseira(); break;
        case 'e': novaPlanta = new ErvaDaninha(); break;
        case 'x': novaPlanta = new Exotica(); break;
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
        cout << "Posição inválida (" << linha << ", " << coluna << ").\n";
        return false;
    }

    Solo* solo = &grid[linha][coluna];

    if (solo->obterPlanta() != nullptr) {
        cout << "A planta " << solo->obterPlanta()->getNome() << " foi colhida da posição (" << char('A' + linha) << ", " << char('A' + coluna) << ").\n";
        solo->removerPlanta();
        return false;
    }
    return true;
}

void Jardim::listarPlantas() {
    bool encontrou = false;

    cout << "--------------------------- Lista de plantas no jardim --------------------------- \n";
    cout << "\t\t| " << "\t TIPO " << "\t| " << "\t POSIÇÃO " << "\t| " << "\tAGUA " << "\t| " << "\t  NUTRIENTES " << "\t| " << endl;

    for (int l = 0; l < nLinhas; l++) {
        for (int c = 0; c < nColunas; c++) {
            Planta* planta = grid[l][c].obterPlanta();
            if (planta != nullptr) {
                encontrou = true;
                cout << "\t\t| "
                     << "\t" << planta->getNome()
                     << "\t| "
                     << "\t (" << char('a' + l) << ", " << char('a' + c) << ")"
                     << "\t\t| "
                     << "\t " << planta->obtemAguaP()
                     << "\t\t| "
                     << "\t\t " << planta->obtemNutrientesP()
                     << "\t\t\t|\n";
            }
        }
    }
    cout << "---------------------------------------------------------------------------------- \n";

    if ( !encontrou ) {
        cout << "Não existem plantas no jardim!\n" << "Experimente plantar primeiro utilizando o comando - > planta <linha> <coluna> <tipo>\n" << endl;
    }
};

void Jardim::listarPlanta(int linha, int coluna) {
    bool encontrou = false;

    cout << "--------------------------- Lista de plantas no jardim --------------------------- \n";
    cout << "\t\t| " << "\t TIPO " << "\t| " << "\t POSIÇÃO " << "\t| " << "\tAGUA " << "\t| " << "\t  NUTRIENTES " << "\t| " << endl;

    Planta* planta = grid[linha][coluna].obterPlanta();
    if (planta != nullptr) {
        encontrou = true;
        cout << "\t\t| "
             << "\t" << planta->getNome()
             << "\t| "
             << "\t (" << char('a' + linha) << ", " << char('a' + coluna) << ")"
             << "\t\t| "
             << "\t " << planta->obtemAguaP()
             << "\t\t| "
             << "\t\t " << planta->obtemNutrientesP()
             << "\t\t\t|\n";
    }
    cout << "---------------------------------------------------------------------------------- \n";

    if ( !encontrou ) {
        cout << "Não existem plantas no jardim!\n" << "Experimente plantar primeiro utilizando o comando - > planta <linha> <coluna> <tipo>\n" << endl;
    }
};

bool Jardim::posicaoValida(int linha, int coluna) const {
    return linha >= 0 && linha < nLinhas && coluna >= 0 && coluna < nColunas;
}

Solo* Jardim::getSolo(int linha, int coluna) {
    return &grid[linha][coluna];
}

Jardineiro& Jardim::getJardineiro() const{
    return *jardineiro;
}