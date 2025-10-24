//
// Created by Leonardo Ferreira on 11/10/2025.
//

#include <iostream>
#include <sstream>
#include "Comando.h"

using namespace std;

void Comando::comandoJardim(Jardim*& jardim, istringstream& iss){
    int lin, col;

    if ( iss >> lin >> col ){
        delete jardim;
        jardim = new Jardim(lin, col);
        cout << "Jardim criado com " << lin << " linhas e " << col << " colunas.\n";
        jardim->imprimir();
    }
    else {
        cout << "Uso: jardim <linhas> <colunas>\n";
    }
};

void Comando::comandoAvanca(Jardim* jardim, istringstream& iss){
    if ( jardim == nullptr ){
        cout << "Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n";
        return;
    }

    int n = 1;
    iss >> n;
    //jardim->avanca(n);
};

void Comando::comandoAjuda(){
    cout << "Comandos disponíveis:\n"
         << "  jardim <linhas> <colunas>   - cria um novo jardim\n"
         << "  avanca [n]                  - avança o tempo\n"
         << "  fim                         - termina o programa\n";
};

void Comando::comandoFim(bool& ativo){
    ativo = false;
    cout << "A terminar o simulador...\n";
};