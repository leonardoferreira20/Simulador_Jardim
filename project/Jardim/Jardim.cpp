//
// Created by Leonardo Ferreira on 11/10/2025.
//

#include "Jardim.h"
#include "../Jardineiro/Jardineiro.h"
#include "../Solo/Solo.h"

#include "../Planta/Cacto/Cacto.h"
#include "../Planta/Roseira/Roseira.h"
#include "../Planta/ErvaDaninha/ErvaDaninha.h"
#include "../Planta/Exotica/Exotica.h"

#include "../Ferramenta/Ferramenta.h"
# include "../Ferramenta/Adubo/Adubo.h"
# include "../Ferramenta/Regador/Regador.h"
# include "../Ferramenta/Tesoura/Tesoura.h"
# include "../Ferramenta/VaraEspecial/VaraEspecial.h"

#include <iostream>
#include <sstream>

using namespace std;

Jardim::Jardim(int lin, int col) : nLinhas(lin), nColunas(col) {
    jardineiro = new Jardineiro();
    grid = new Solo*[nLinhas];
    for (int i = 0; i < nLinhas; i++)
        grid[i] = new Solo[nColunas];


    for (int i = 0; i < 3; i++)
        spawnFerramentaAleatoria();

}


Jardim::Jardim(const Jardim& outro) {
    nLinhas = outro.nLinhas;
    nColunas = outro.nColunas;

    // copiar grelha
    grid = new Solo*[nLinhas];
    for (int i = 0; i < nLinhas; i++) {
        grid[i] = new Solo[nColunas];
        for (int c = 0; c < nColunas; c++) {
            grid[i][c] = outro.grid[i][c]; // Solo::operator= (já faz deep copy de planta/ferramenta)
        }
    }

    // copia de jardineiro
    jardineiro = nullptr;
    if (outro.jardineiro != nullptr) {
        jardineiro = new Jardineiro(*outro.jardineiro); // usa o teu copy ctor do Jardineiro (com clone)
    }
}


Jardim::~Jardim() {
    for (int i = 0; i < nLinhas; i++)
        delete[] grid[i];
    delete[] grid;

    //libertar jardineiro
    delete jardineiro;
    jardineiro = nullptr;
}

string Jardim::imprimir() const {
    ostringstream oss;

    oss << "\n   ";
    for (int c = 0; c < nColunas; c++) {
        oss << char('A' + c) << " ";
    }
    oss << "\n";

    for (int l = 0; l < nLinhas; l++) {
        oss << char('A' + l) << "  ";

        for (int c = 0; c < nColunas; c++) {

            char simbolo;

            if (jardineiro->estaDentro() &&
                jardineiro->getLinha() == l &&
                jardineiro->getColuna() == c) {

                simbolo = '*';
            }
            else {
                simbolo = grid[l][c].getSimbolo();
            }

            oss << simbolo << " ";
        }

        oss << "\n";
    }

    oss << "\n";
    return oss.str();
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

void Jardim::avanca(ostream& out) {
    if (jardineiro->estaDentro() && jardineiro->obterFerramentaNaMao() != nullptr) {
        Ferramenta* ferr = jardineiro->obterFerramentaNaMao();
        int linJard = jardineiro->getLinha();
        int colJard = jardineiro->getColuna();

        ferr->utiliza(grid[linJard][colJard], out);

        if (ferr->estaVazia()) {
            out << ferr->getNome() << " ficou vazia e foi descartada!\n";
            jardineiro->removerFerramentaVazia();
        }
    }

    for (int l = 0; l < nLinhas; l++) {
        for (int c = 0; c < nColunas; c++) {
            Planta* planta = grid[l][c].obterPlanta();
            if (planta != nullptr && planta->estaViva()) {
                if (!planta->isRecemNascida())
                    planta->tentaReproduzir(*this, l, c);

                planta->agir(grid[l][c]);
            }
        }
    }

    for (int l = 0; l < nLinhas; l++) {
        for (int c = 0; c < nColunas; c++) {
            Planta* p = grid[l][c].obterPlanta();
            if (p != nullptr && p->isRecemNascida()) {
                p->setRecemNascida(false);
            }
        }
    }
}

bool Jardim::planta(int linha, int coluna, char tipo, ostream& out) {
    if (linha < 0 || linha >= nLinhas || coluna < 0 || coluna >= nColunas) {
        out << "Posição inválida (" << linha << ", " << coluna << ").\n";
        return false;
    }

    Solo* solo = &grid[linha][coluna];

    if (solo->obterPlanta() != nullptr) {
        out << "Já existe uma planta nessa posição.\n";
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
            out << "Tipo de planta desconhecido.\n";
        return false;
    }

    solo->criarPlanta(novaPlanta);
    out << "Planta " << novaPlanta->getNome() << " plantada em (" << char('A' + linha) << ", " << char('A' + coluna) << ").\n";
    return true;
}

bool Jardim::colhe(int linha, int coluna, ostream& out){
    if (linha < 0 || linha >= nLinhas || coluna < 0 || coluna >= nColunas) {
        out << "Posição inválida (" << linha << ", " << coluna << ").\n";
        return false;
    }

    Solo* solo = &grid[linha][coluna];

    if (solo->obterPlanta() != nullptr) {
        out << "A planta " << solo->obterPlanta()->getNome() << " foi colhida da posição (" << char('A' + linha) << ", " << char('A' + coluna) << ").\n";
        solo->removerPlanta();
        return false;
    }
    return true;
}

string Jardim::listarPlantas() {
    bool encontrou = false;
    ostringstream oss;

    oss << "--------------------------- Lista de plantas no jardim --------------------------- \n";
    oss << "\t\t| " << "\t TIPO " << "\t| " << "\t POSIÇÃO " << "\t| " << "\tAGUA " << "\t| " << "\t  NUTRIENTES " << "\t| " << endl;

    for (int l = 0; l < nLinhas; l++) {
        for (int c = 0; c < nColunas; c++) {
            Planta* planta = grid[l][c].obterPlanta();
            if (planta != nullptr) {
                encontrou = true;
                oss << "\t\t| "
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
    oss << "---------------------------------------------------------------------------------- \n";

    if ( !encontrou ) {
        oss << "Não existem plantas no jardim!\n" << "Experimente plantar primeiro utilizando o comando - > planta <linha> <coluna> <tipo>\n" << endl;
    }
    return oss.str();
};

string Jardim::listarPlanta(int linha, int coluna) {
    ostringstream oss;
    bool encontrou = false;

    oss << "--------------------------- Lista de plantas no jardim --------------------------- \n";
    oss << "\t\t| " << "\t TIPO " << "\t| " << "\t POSIÇÃO " << "\t| " << "\tAGUA " << "\t| " << "\t  NUTRIENTES " << "\t| " << endl;

    Planta* planta = grid[linha][coluna].obterPlanta();
    if (planta != nullptr) {
        encontrou = true;
        oss << "\t\t| "
             << "\t" << planta->getNome()
             << "\t| "
             << "\t (" << char('a' + linha) << ", " << char('a' + coluna) << ")"
             << "\t\t| "
             << "\t " << planta->obtemAguaP()
             << "\t\t| "
             << "\t\t " << planta->obtemNutrientesP()
             << "\t\t\t|\n";
    }
    oss << "---------------------------------------------------------------------------------- \n";

    if ( !encontrou ) {
        oss << "Não existem plantas no jardim!\n" << "Experimente plantar primeiro utilizando o comando - > planta <linha> <coluna> <tipo>\n" << endl;
    }
    return oss.str();
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

bool Jardim::spawnFerramentaAleatoria() {
    int l, c, tipo;
    Solo* solo;
    Ferramenta* f;

    do {
        l = rand() % nLinhas;
        c = rand() % nColunas;

        // DISCUTIR SOBRE A POSSIBILIDADE DE NAO HAVER POSICOES VAZIAS (LOOP INFINITO)
    } while ( grid[l][c].temFerramenta() );

    solo = &grid[l][c];

    tipo = rand() % 4;

    switch (tipo) {
        case 0: f = new Regador(); break;
        case 1: f = new Adubo(); break;
        case 2: f = new Tesoura(); break;
        case 3: f = new VaraEspecial(); break;
    }

    solo->colocarFerramenta(f);

    return true;
}

string Jardim::verificarEApanharFerramenta() {
    ostringstream oss;

    if (!jardineiro->estaDentro()) {
        return oss.str();
    }

    int lin = jardineiro->getLinha();
    int col = jardineiro->getColuna();

    Solo* solo = getSolo(lin, col);
    if (solo && solo->temFerramenta()) {
        Ferramenta* f = solo->obterFerramenta();

        oss << "O jardineiro apanhou uma " << f->getNome() << " (nº " << f->getNSerie() << ")!\n";

        jardineiro->adicionarFerramenta(f);  // Adiciona ao inventário
        solo->removerFerramenta();           // Remove do solo

        // Spawn nova ferramenta aleatória "por magia"
        spawnFerramentaAleatoria();
    }

    return oss.str();
}

void Jardineiro::forcarFora() {
    // Não mexe nos contadores e não imprime nada
    dentro = false;
    linha = -1;
    coluna = -1;
}
