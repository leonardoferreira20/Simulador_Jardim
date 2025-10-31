//
// Created by Leonardo Ferreira on 11/10/2025.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

#include "../Solo/Solo.h"
#include "Comando.h"

using namespace std;

void Comando::comandoJardim(Jardim*& jardim, istringstream& iss){
    int lin, col;

    if ( iss >> lin >> col && (lin < 27 && col < 27) && (lin > 0 && col > 0) ) {
        if (!iss.eof()) {
            cout << "Uso: jardim <linhas> <colunas>\n";
            return;
        }
        if ( jardim != nullptr ) {
            cout << "Já se encontra um jardim criado!\n";
            return;
        }
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

void Comando::comandoPlantar(Jardim* jardim, istringstream& iss){
    int lin, col;
    char tipo;

    if ( jardim == nullptr ){
        cout << "Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n";
        return;
    }

    if (iss >> lin >> col >> tipo) {
        jardim->planta(lin-1, col-1, tipo);
    } else {
        cout << "Uso: planta <linha> <coluna> <tipo>\n";
    }

    jardim->imprimir();
};

void Comando::comandoColher(Jardim* jardim, istringstream& iss){
    int lin, col;

    if ( jardim == nullptr ){
        cout << "Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n";
        return;
    }

    if (iss >> lin >> col ) {
        jardim->colhe(lin-1, col-1);
    } else {
        cout << "Uso: colhe <linha> <coluna>\n";
    }

    jardim->imprimir();
};

void Comando::comandoListarPlantas(Jardim* jardim) {
    if (jardim == nullptr) {
        cout << "Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n";
        return;
    }

    jardim->listarPlantas();
    jardim->imprimir();
}

void Comando::comandoListarPlanta(Jardim* jardim, istringstream& iss) {
    int lin, col;

    if (jardim == nullptr) {
        cout << "Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n";
        return;
    }

    if ( iss >> lin >> col ){
        jardim->listarPlanta(lin-1, col-1);
        jardim->imprimir();
    }
    else {
        cout << "Utilização: \n"
             << "\t> lplantas                 - Lista todas as plantas existentes no jardim\n"
             << "\t> lplanta <linha> <coluna> - Mostra informações detalhadas sobre a planta na posição indicada\n";
    }
}

/*void Comando::comandoListarInfoSolo(Jardim* jardim, istringstream& iss) {
    int lin, col;

    if (jardim == nullptr) {
        cout << "Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n";
        return;
    }

    if ( iss >> lin >> col ){
        jardim->getSolo(lin-1, col-1);
        //solo->imprimir();

        //jardim->imprimir();
    }
    else {
        cout << "Utilização: \n"
             << "\t> lsolo <linha> <coluna> [n]     - Lista toda a informação do solo na posição introduzida, caso [n] seja fornecido, indica também nas posições vizinhas\n";
    }
}*/

void Comando::comandoEntrarJardim(Jardim* jardim, istringstream& iss) {
    int lin, col;

    if (jardim == nullptr) {
        cout << "Erro: ainda não existe um jardim. Crie-o com 'jardim <linhas> <colunas>'.\n";
        return;
    }

    iss >> lin >> col;

    if (!jardim->posicaoValida(lin, col)) {
        cout << "Posição fora dos limites do jardim.\n";
        return;
    }

    jardim->getJardineiro().entrar(lin, col);
}

void Comando::comandoSairJardim(Jardim* jardim) {

    if (jardim == nullptr) {
        cout << "Erro: ainda não existe um jardim.\n";
        return;
    }

    if (!jardim->getJardineiro().estaDentro()) {
        cout << "O jardineiro já está fora do jardim.\n";
        return;
    }

    jardim->getJardineiro().sair();
}

void Comando::comandoMoverJardim(Jardim* jardim, istringstream& iss) {

    if (jardim == nullptr) {
        cout << "Erro: ainda não existe um jardim.\n";
        return;
    }

    if (!jardim->getJardineiro().estaDentro()) {
        cout << "O jardineiro já está fora do jardim.\n";
    }

    /*switch (iss.str()) {
        case 'e':
            jardim->getJardineiro().entrar(lin, col);
            break;
        case 'd':
            break;
        case 'f':
            break;
        case 'b':
            break;
        default:
            return;
    }*/

}

bool Comando::criaFicheiro( string nome) {
    std::filesystem::path ficheiro = "Save/" + nome + ".txt";
    ofstream out(ficheiro);
    if (!out) {
        cout << "Erro ao criar o ficheiro: " << ficheiro << "\n";
        return false;
    }
    return true;
}

bool Comando::comandoProcuraFicheiro(string nome){
    if ((nome.find('.') != string::npos) || (nome.find('/')!= string::npos)) {
        return false;
    }
    std::filesystem::path ficheiro = "Save/" + nome + ".txt";
    if (exists(ficheiro)) {
        return true;
    }
    return false;
}

void Comando::comandoGrava(Jardim* jardim, istringstream& iss){
    string resposta,nome;

    if (jardim == nullptr) {
        cout << "Nao existe jardim para gravar!\n";
        return;
    }
    if (iss >> nome){
        if (!iss.eof()) {
            cout << "Uso: gravar <nome>\n";
            return;
        }
        if (comandoProcuraFicheiro(nome)) {
            std::filesystem::path ficheiro = "Save/" + nome + ".txt";
            cout << "Ficheiro existe! Quer gravar novamente?(s/n)\n";
            cin >> resposta;
            if (resposta == "s") {
                cout << "Comando por implementar dentro de gravar novamente\n";
            }else if (resposta == "n") {
                cout << "Nao foi gravado o ficheiro!\n";
                return;
            }
            else {
                cout << "Comando errado!\n";
                return;
            }
        }else {
            if (!criaFicheiro( nome)) cout << "Erro na criacao de ficheiro!\n";
            cout << "Comando por implementar na gravacao nova!\n";
        }
    }else cout << "Uso: grava <nome>\n";
}

void Comando::comandoRecupera(Jardim* jardim, istringstream& iss){
    string nome;

    if (iss >> nome){
        if (!iss.eof()) {
            cout << "Uso: recupera <nome>\n";
            return;
        }
        if (comandoProcuraFicheiro(nome)){
            cout << "Gravacao existente com esse nome! Por implementar comando!" << endl;
        }else {
            cout << "Gravação com este nome não existe!\n Nome: " << nome << endl;
        }
    }else cout << "Uso: recupera <nome>\n";
}

void Comando::comandoApaga(Jardim* jardim, istringstream& iss){
    string nome;

    if (iss >> nome){
        if (!iss.eof()) {
            cout << "Uso: apaga <nome>\n";
            return;
        }
        if (comandoProcuraFicheiro(nome)) {
            cout << "Comando por implementar!\n";
            cout << "Gravacao com nome: " << nome << " apagada com sucesso!\n" << endl;
        }else {
            cout << "Comando por implementar!\n";
            cout << "Gravacao com nome: " << nome << " nao existe!\n" << endl;
        }
    }else cout << "Uso: apaga <nome>\n";
    cout << "Funcao por implementar. POO" << endl;
}

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
         << " Ficheiros:\n"
         << "   > grava <nome_ficheiro>.txt         - Grava o ficheiro com o nome indicado\n"
         << "   > recupera <nome_ficheiro>.txt      - Abre o ficheiro guardado com o nome indicado\n"
         << "   > apaga <nome_ficheiro>.txt         - Apaga o ficheiro guardado com o nome indicado\n"
         << " Terminar:\n"
         << "   fim                                 - Termina o programa\n";
};

void Comando::comandoFim(bool& ativo){
    ativo = false;
    cout << "A terminar o simulador...\n";
};