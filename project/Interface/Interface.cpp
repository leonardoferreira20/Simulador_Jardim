//
// Created by Leonardo Ferreira on 23/10/2025.
//

#include <iostream>
#include <sstream>
#include "Interface.h"
#include "../Comando/Comando.h"
#include "../Jardim/Jardim.h"

using namespace std;

Interface::Interface() : jardim(nullptr), ativo(true) {
    srand(time(NULL));
}

Interface::~Interface(){
    delete jardim;
    Comando::limparGravacoes();
}

void Interface::executar(){
    string linha;
    cout << "\nBem-vindo ao simulador de jardim!. Escreva 'ajuda' para saber os comandos disponíveis." << endl
         << "Escreva 'fim' para sair.\n";

    while ( ativo ){
        cout << "> ";
        getline(cin, linha);
        processarComando(linha, cout);
    }
};

void Interface::processarComando(const string& linha, ostream& out){
    istringstream iss(linha);
    string cmd;
    iss >> cmd;

    // CASO O UTILIZADOR ESCREVA COM MAIUSCULAS, O CÓDIGO ESTÁ PREPARADO PARA CONVERTER TUDO PARA MINUSCULAS
    for (int i = 0; i < cmd.length(); i++)
        cmd[i] = tolower(cmd[i]);

    if (jardim == nullptr && cmd != "ajuda" && !cmd.empty() && cmd != "fim") {
        if ( cmd == "jardim" ){
            Jardim* novoJardim = Comando::comandoJardim(iss, cout);

            if (novoJardim == nullptr)
                return;

            if (jardim != nullptr) {
                out << "Já se encontra um jardim criado!\n";
                delete novoJardim;
                return;
            }

            jardim = novoJardim;
        }
        else if ( cmd == "executa" ) {
            Comando::comandoRunscript(iss, *this, cout);
        }
        else {
            out << "Comando invalido! Jardim nao iniciado!\n" << "Comandos disponiveis: \n-> jardim <linhas> <colunas> \n-> ajuda\n";
        }
    }
    else {
        if ( cmd == "avanca" ){
            Comando::comandoAvanca(jardim, iss, cout);
        }
        else if ( cmd == "planta" ) {
            Comando::comandoPlantar(jardim, iss, cout);
        }
        else if ( cmd == "colhe" ) {
            Comando::comandoColher(jardim, iss, cout);
        }
        else if ( cmd == "lplantas" ) {
            Comando::comandoListarPlantas(jardim, cout);
        }
        else if ( cmd == "lplanta" ) {
            Comando::comandoListarPlanta(jardim, iss, cout);
        }
        else if ( cmd == "larea" ) {
            Comando::comandoListarArea(jardim, cout);
        }
        else if ( cmd == "lsolo" ) {
            Comando::comandoListarInfoSolo(jardim, iss, cout);
        }
        else if ( cmd == "lferr" ) {
            Comando::comandoListarFerramenta(jardim, cout);
        }
        else if ( cmd == "entra" ) {
            Comando::comandoEntrarJardim(jardim, iss, cout);
        }
        else if (cmd == "sai") {
            Comando::comandoSairJardim(jardim, cout);
        }
        else if (cmd == "e" || cmd == "d" || cmd == "c" || cmd == "b") {
            Comando::comandoMoverJardim(jardim, cmd[0], cout);
        }
        else if ( cmd == "larga" ) {
            Comando::comandoLargaFerramenta(jardim, cout);
        }
        else if ( cmd == "pega" ) {
            Comando::comandoPegaFerramenta(jardim, iss, cout);
        }
        else if ( cmd == "compra" ){
            Comando::comandoCompra(jardim, iss, cout);
        }
        else if ( cmd == "grava" ){
            Comando::comandoGrava(jardim, iss, cout);
        }
        else if ( cmd == "recupera" ){
            Comando::comandoRecupera(jardim, iss, cout);
        }
        else if ( cmd == "apaga" ){
            Comando::comandoApaga(iss, cout);
        }
        else if ( cmd == "ajuda" ){
            out << Comando::comandoAjuda();
        }
        else if ( cmd == "fim" ){
            Comando::comandoFim(ativo, cout);
        }
        else if ( cmd == "" ){
            return;
        }
        else {
            out << "Comando invalido!\n" << endl;
        }
    }
}
