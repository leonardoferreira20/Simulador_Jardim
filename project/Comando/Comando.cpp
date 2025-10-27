//
// Created by Leonardo Ferreira on 11/10/2025.
//

#include <iostream>
#include <sstream>
#include "../Solo/Solo.h"
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
    jardim->avanca(n);
    jardim->imprimir();
};

void Comando::comandoAjuda(){
    cout << "Comandos disponíveis:\n"
         << " Criação jardim:\n"
         << "   > jardim <linhas> <colunas>         - Cria um novo jardim\n"
         << " Gestão do Tempo:\n"
         << "   > avanca [n]                        - Avança o tempo\n"
         << " Listagens:\n"
         << "   > lplantas                          - Lista todas as plantas existentes no jardim\n"
         << "   > lplanta <linha> <coluna>          - Mostra informações detalhadas sobre a planta na posição indicada\n"
         << "   > larea                             - Mostra todas as posições ocupadas (plantas e ferramentas) no jardim\n"
         << "   > lsolo <linha> <coluna> [n]        - Mostra a informação do solo na posição indicada (e nas posições vizinhas, se n for fornecido)\n"
         << "   > lferr                             - Lista todas as ferramentas disponíveis (no solo e no inventário do jardineiro)\n"
         << " Movimento e posição do jardineiro:\n"
         << "   > entra <linha> <coluna>            - Coloca o jardineiro dentro do jardim na posição indicada\n"
         << "   > sai                               - Faz o jardineiro sair do jardim\n"
         << "   > e, d, c, b                        - Movem o jardineiro uma célula: esquerda, direita, cima, baixo (respetivamente)\n"
         << " Ações de jardinagem:\n"
         << "   > planta <linha> <coluna> <tipo>    - Planta uma nova planta do tipo indicado na posição especificada (c, r, e, x)\n"
         << "   > colhe <linha> <coluna>            - Colhe (remove) a planta na posição indicada\n"
         << " Terminar:\n"
         << "   fim                                 - Termina o programa\n";
};

void Comando::comandoFim(bool& ativo){
    ativo = false;
    cout << "A terminar o simulador...\n";
};

void Comando::comandoPlantar(Jardim* jardim, istringstream& iss){
    int lin, col;

    if ( iss >> lin >> col ) {
        jardim->getSolo(lin,col)->criarPlanta();
    }

};