//
// Created by Leonardo Ferreira on 23/10/2025.
//

#include <iostream>
#include <sstream>
#include "Interface.h"
#include "../Comando/Comando.h"

using namespace std;

Interface::Interface() : jardim(nullptr), ativo(true){}

Interface::~Interface(){
    delete jardim;
}

void Interface::executar(){
    string linha;
    cout << "\nBem-vindo ao simulador de jardim!. Escreva 'ajuda' para saber os comandos disponíveis." << endl << "Escreva 'fim' para sair.\n";

    while ( ativo ){
        cout << "> ";
        getline(cin, linha);
        processarComando(linha);
    }
};

void Interface::processarComando(const string& linha){
    istringstream iss(linha);
    string cmd;
    iss >> cmd;

    /// CASO O UTILIZADOR ESCREVA COM MAIUSCULAS, O CÓDIGO ESTÁ PREPARADO PARA CONVERTER TUDO PARA MINUSCULAS
    for (int i = 0; i < cmd.length(); i++)
        cmd[i] = tolower(cmd[i]);

    if ( cmd == "jardim" ){
        Comando::comandoJardim(jardim, iss);
    }
    else if ( cmd == "avanca" ){
        Comando::comandoAvanca(jardim, iss);
        cout << endl;
    }
    else if ( cmd == "planta" ) {
        Comando::comandoPlantar(jardim, iss);
    }
    else if ( cmd == "colhe" ) {
        Comando::comandoColher(jardim, iss);
    }
    else if ( cmd == "lplantas" ) {
        Comando::comandoListarPlantas(jardim);
    }
    else if ( cmd == "ajuda" ){
        Comando::comandoAjuda();
    }
    else if ( cmd == "fim" ){
        Comando::comandoFim(ativo);
    }
    else if ( cmd == "" ){
        return;
    }
    else {
        cout << "O comando inserido não existe!\n" << endl;
    }
}
