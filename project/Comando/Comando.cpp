//
// Created by Leonardo Ferreira on 11/10/2025.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

#include "Comando.h"
#include "../Solo/Solo.h"
#include "../Interface/Interface.h"
#include "../Jardim/Jardim.h"
#include "../Jardineiro/Jardineiro.h"
#include "../Planta/Planta.h"
#include "../Ferramenta/Adubo/Adubo.h"
#include "../Ferramenta/Tesoura/Tesoura.h"
#include "../Ferramenta/Regador/Regador.h"
#include "../Ferramenta/VaraEspecial/VaraEspecial.h"

using namespace std;

/// CRIAR JARDIM
Jardim* Comando::comandoJardim(istringstream& iss){
    int lin, col;

    if (!(iss >> lin >> col)) {
        cout << "Uso: jardim <linhas> <colunas>\n" << endl;
        return nullptr;
    }

    if ((lin <= 0 || lin >= 27) || (col <= 0 || col >= 27)) {
        cout << "Uso: jardim <linhas> <colunas>\n" << endl;
        return nullptr;
    }

    Jardim* jardim = new Jardim(lin, col);

    cout << "Jardim criado com " << lin << " linhas e " << col << " colunas.\n";

    jardim->imprimir();
    return jardim;
};

/// AVANÇAR NO TEMPO
void Comando::comandoAvanca(Jardim* jardim, istringstream& iss){
    if ( jardim == nullptr ){
        cout << "Erro: Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    int n = 1;
    iss >> n;
    for (int i = 0; i < n;i++) {
        jardim->avanca();
        jardim->getJardineiro().resetContadores();
    }
    jardim->imprimir();
};

/// LISTAR INFORMAÇÃO SOBRE PLANTAS
void Comando::comandoListarPlantas(Jardim* jardim) {

    if (jardim == nullptr) {
        cout << "Erro: Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    jardim->listarPlantas();
    jardim->imprimir();
    cout << endl;
}

void Comando::comandoListarPlanta(Jardim* jardim, istringstream& iss) {
    string coords;
    int lin, col;

    if ( jardim == nullptr ) {
        cout << "Erro: Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    if ( !(iss >> coords) ) {
        cout << "Uso: lplanta <AA>\n" << endl;
        return;
    }

    if ( !converteCoordenada(coords, lin, col) ) {
        cout << "Erro: Coordenadas inválidas.\n" << endl;
        return;
    }

    if ( !jardim->posicaoValida(lin, col) ) {
        cout << "Erro: Posição fora dos limites.\n" << endl;
        return;
    }

    jardim->listarPlanta(lin, col);
    jardim->imprimir();
}

/// LISTAR INFORMAÇÃO SOBRE O SOLO
void Comando::comandoListarInfoSolo(Jardim* jardim, istringstream& iss) {
    string coords;
    int lin, col;
    int raio = 0;

    if (jardim == nullptr) {
        cout << "Erro: Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    if (!(iss >> coords)) {
        cout << "Uso: lsolo <AA> [n]\n" << endl;
        return;
    }

    if (!converteCoordenada(coords, lin, col)) {
        cout << "Erro: Coordenadas inválidas.\n" << endl;
        return;
    }

    iss >> raio; // opcional

    if (!jardim->posicaoValida(lin, col)) {
        cout << "Erro: Posição fora dos limites.\n" << endl;
        return;
    }

    Solo* solo = jardim->getSolo(lin, col);

    if (solo == nullptr) {
        cout << "Erro inesperado: solo inexistente.\n" << endl;
        return;
    }

    solo->imprimirDetalhado();

    // Se houver raio, listar vizinhos
    if (raio > 0) {
        cout << "\nVizinhos (raio " << raio << "):\n";
        for (int dl = -raio; dl <= raio; dl++) {
            for (int dc = -raio; dc <= raio; dc++) {
                int nl = lin + dl;
                int nc = col + dc;

                if (jardim->posicaoValida(nl, nc)) {
                    cout << " - ";
                    jardim->getSolo(nl, nc)->imprimirDetalhado();
                }
            }
        }
    }

    cout << endl;
    jardim->imprimir();
}

void Comando::comandoListarArea(Jardim* jardim) {
    if (jardim == nullptr) {
        cout << "Erro: Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    bool encontrou = false;

    for (int l = 0; l < jardim->getNumLinhas(); ++l) {
        for (int c = 0; c < jardim->getNumColunas(); ++c) {
            Solo* solo = jardim->getSolo(l, c);
            if (solo != nullptr) {
                if ( solo->temPlanta() ) {
                    Planta* p = solo->obterPlanta();
                    cout << "  (" << char('A' + l) << "," << char('A' + c) << ") - Planta: " << p->getNome() << "\n";
                    encontrou = true;
                }
                else if (solo->temFerramenta()) {
                    Ferramenta* f = solo->obterFerramenta();
                    cout << "  (" << char('A' + l) << "," << char('A' + c) << ") - Ferramenta: " << f->getNome() << "\n";
                    encontrou = true;
                }
            }
        }
    }

    if (!encontrou)
        cout << "  Nenhuma célula ocupada.\n";
}

/// AÇÕES DO JARDINEIRO
void Comando::comandoEntrarJardim(Jardim* jardim, istringstream& iss) {
    string coords;
    int lin, col;

    if ( jardim == nullptr ) {
        cout << "Erro: Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    if ( !(iss >> coords) ) {
        cout << "Uso: entra <AA>\n" << endl;
        return;
    }

    if ( !converteCoordenada(coords, lin, col) ) {
        cout << "Erro: Coordenadas inválidas. Use formato <AA>.\n" << endl;
        return;
    }

    if ( !jardim->posicaoValida(lin, col) ) {
        cout << "Erro: Posição fora dos limites do jardim.\n" << endl;
        return;
    }

    jardim->getJardineiro().entrar(lin, col);
    jardim->verificarEApanharFerramenta();
    jardim->imprimir();
}

void Comando::comandoSairJardim(Jardim* jardim) {

    if (jardim == nullptr) {
        cout << "Erro: Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    if (!jardim->getJardineiro().estaDentro()) {
        cout << "Erro: O jardineiro já está fora do jardim.\n" << endl;
        return;
    }

    jardim->getJardineiro().sair();
    jardim->imprimir();
}

void Comando::comandoMoverJardim(Jardim* jardim, char direcao) {
    if (jardim == nullptr) {
        cout << "Erro: Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    Jardineiro& jardineiro = jardim->getJardineiro();

    if (!jardineiro.estaDentro()) {
        cout << "Erro: O jardineiro está fora do jardim.\n" << endl;
        return;
    }

    int lin = jardineiro.getLinha();
    int col = jardineiro.getColuna();

    switch (direcao) {
        case 'e': col--; break;
        case 'd': col++; break;
        case 'c': lin--; break;
        case 'b': lin++; break;
        default:
            cout << "Erro: Direção inválida.\n" << endl;
        return;
    }

    if (!jardim->posicaoValida(lin, col)) {
        cout << "Erro: O jardineiro não pode sair do jardim.\n" << endl;
        return;
    }

    jardineiro.mover(direcao);
    jardim->verificarEApanharFerramenta();
    jardim->imprimir();
}

void Comando::comandoPlantar(Jardim* jardim, istringstream& iss){
    string coords;
    char tipo, extra;
    int lin, col;

    if ( jardim == nullptr ) {
        cout << "Erro: Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    if ( !(iss >> coords >> tipo) ) {
        cout << "Uso: planta <AA> <tipo>\n";
        return;
    }

    if (iss>>extra) {
        cout << "Uso: planta <AA> <tipo>\n";
        return;
    }

    if ( !converteCoordenada(coords, lin, col) ) {
        cout << "Erro: Coordenadas inválidas. Use formato <AA>.\n" << endl;
        return;
    }

    Jardineiro& jardineiro = jardim->getJardineiro();

    if ( !jardineiro.estaDentro() ) {
        cout << "Erro: O jardineiro está fora do jardim.\n" << endl;
        return;
    }

    if ( !jardim->posicaoValida(lin, col) ) {
        cout << "Erro: Posição fora dos limites do jardim.\n" << endl;
        return;
    }

    if ( !jardineiro.podePlantar() ) {
        cout << "Erro: Limite de plantações atingido!\n" << endl;
        return;
    }

    jardim->planta(lin, col, tipo);
    jardineiro.registaPlantacao();
    jardim->imprimir();
}

void Comando::comandoColher(Jardim* jardim, istringstream& iss){
    string coords;
    int lin, col;

    if ( jardim == nullptr ) {
        cout << "Erro: Crie primeiro um jardim com 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    Jardineiro& jardineiro = jardim->getJardineiro();
    if ( !jardineiro.estaDentro() ) {
        cout << "Erro: O jardineiro está fora do jardim.\n" << endl;
        return;
    }

    if ( !(iss >> coords) ) {
        cout << "Use: colhe <AA>\n" << endl;
        return;
    }

    if ( !converteCoordenada(coords, lin, col) ) {
        cout << "Erro: Coordenadas inválidas.\n" << endl;
        return;
    }

    if ( !jardim->posicaoValida(lin, col) ) {
        cout << "Erro: Posição fora dos limites.\n" << endl;
        return;
    }

    if ( !jardineiro.podeColher() ) {
        cout << "Erro: Limite de colheitas atingido!\n" << endl;
        return;
    }

    jardim->colhe(lin, col);
    jardineiro.registaColheita();
    jardim->imprimir();
};

/// FERRAMENTAS
void Comando::comandoListarFerramenta(Jardim* jardim) {

    if (jardim == nullptr) {
        cout << "Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n";
        return;
    }

    bool encontrou = false;

    cout << "Ferramentas disponíveis:\n";

    // Ferramentas no SOLO
    for (int l = 0; l < jardim->getNumLinhas(); l++) {
        for (int c = 0; c < jardim->getNumColunas(); c++) {

            Solo* solo = jardim->getSolo(l, c);
            if (solo != nullptr && solo->temFerramenta()) {

                Ferramenta* f = solo->obterFerramenta();
                cout << "  Solo ("
                     << char('A' + l) << char('A' + c) << ") - "
                     << f->getNome()
                     << " [nº série: " << f->getNSerie() << "]\n";

                encontrou = true;
            }
        }
    }

    // Ferramentas do JARDINEIRO
    Jardineiro& j = jardim->getJardineiro();

    // Ferramenta na mão
    Ferramenta* mao = j.obterFerramentaNaMao();
    if (mao != nullptr) {
        cout << "  Jardineiro (na mão) - " << mao->getNome() << " [nº série: " << mao->getNSerie() << "]\n";
        encontrou = true;
    }

    // Ferramentas no inventário
    for (int i = 0; ; i++) {
        Ferramenta* f = j.getFerramentaInventario(i);
        if (f == nullptr)
            break;

        cout << "  Jardineiro (inventário) - " << f->getNome() << " [nº série: " << f->getNSerie() << "]\n";

        encontrou = true;
    }

    if (!encontrou) {
        cout << "  Nenhuma ferramenta disponível.\n";
    }
}

void Comando::comandoLargaFerramenta(Jardim* jardim) {
    if (jardim == nullptr) {
        cout << "Erro: Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    Jardineiro& jardineiro = jardim->getJardineiro();

    if (!jardineiro.estaDentro()) {
        cout << "Erro: O jardineiro está fora do jardim.\n" << endl;
        return;
    }

    if (jardineiro.obterFerramentaNaMao() == nullptr) {
        cout << "Erro: O jardineiro não tem nenhuma ferramenta na mão.\n" << endl;
        return;
    }

    jardineiro.largarFerramenta();
    jardim->imprimir();
}

void Comando::comandoPegaFerramenta(Jardim* jardim, istringstream& iss) {
    int nSerie;

    if (jardim == nullptr) {
        cout << "Erro: Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    Jardineiro& jardineiro = jardim->getJardineiro();

    if ( !jardineiro.estaDentro() ) {
        cout << "Erro: O jardineiro está fora do jardim.\n" << endl;
        return;
    }

    if ( !(iss >> nSerie) ) {
        cout << "Uso: pega <n>\n";
        return;
    }

    jardim->getJardineiro().pegarFerramenta(nSerie);
    jardim->imprimir();
}

void Comando::comandoCompra(Jardim* jardim, istringstream& iss) {
    if (jardim == nullptr) {
        cout << "Erro: ainda não existe um jardim.\n";
        return;
    }

    Jardineiro& j = jardim->getJardineiro();

    if (!j.estaDentro()) {
        cout << "Erro: o jardineiro tem de estar dentro do jardim para comprar ferramentas.\n";
        return;
    }

    char tipo;
    if (!(iss >> tipo)) {
        cout << "Uso: compra <g|a|t|v>\n";
        return;
    }

    Ferramenta* nova = nullptr;

    switch (tipo) {
        case 'g':
            nova = new Regador();
        break;
        case 'a':
            nova = new Adubo();
        break;
        case 't':
            nova = new Tesoura();
        break;
        case 'v':
            nova = new VaraEspecial();
        break;
        default:
            cout << "Erro: tipo de ferramenta invalido. Use g, a, t ou v.\n";
        return;
    }

    j.adicionarFerramenta(nova);

    cout << "Ferramenta comprada com sucesso: " << nova->getNome() << " (nº serie " << nova->getNSerie() << ")\n";
}

/// FICHEIROS/MEMÓRIA
bool Comando::criaFicheiro( string nome) {
    filesystem::path ficheiro = "Save/" + nome + ".txt";
    ofstream out(ficheiro);
    if (!out) {
        cout << "Erro ao criar o ficheiro: " << ficheiro << "\n" << endl;
        return false;
    }
    return true;
}

bool Comando::validaNomeficheiro(string nome) {
    if ((nome.find('.') != string::npos) || (nome.find('/')!= string::npos)) {
        cout << "Nome invalido de ficheiro: " << nome << "\n" << endl;
        return false;
    }
    return true;
}

bool Comando::procuraFicheiro(string nome, string pasta){
    filesystem::path ficheiro = pasta + "/" + nome + ".txt";
    if (exists(ficheiro)) {
        return true;
    }
    return false;
}

void Comando::comandoGrava(Jardim* jardim, istringstream& iss){
    string resposta,nome;
    string pasta = "Save";

    if (jardim == nullptr) {
        cout << "Nao existe jardim para gravar!\n";
        return;
    }
    if (!(iss >> nome)) {
        cout << "Uso: apaga <nome>\n" << endl;
        return;
    }
    if (!iss.eof()) {
        cout << "Uso: apaga <nome>\n" << endl;
        return;
    }
    if (!validaNomeficheiro(nome))
        return;
    if (procuraFicheiro(nome,pasta)) {
        filesystem::path ficheiro = pasta + "/" + nome + ".txt";
        cout << "Ficheiro existe! Quer gravar novamente?(s/n)\n" << endl;
        cin >> resposta;
        if (resposta == "s") {
            cout << "Comando por implementar dentro de gravar novamente\n" << endl;
        }else if (resposta == "n") {
            cout << "Nao foi gravado o ficheiro!\n" << endl;
            return;
        }
        else {
            cout << "Comando errado!\n" << endl;
            return;
        }
    }else {
        if (!criaFicheiro( nome)) cout << "Erro na criacao de ficheiro!\n" << endl;
        cout << "Cria Ficheiro! Comando por implementar na gravacao nova!\n";
    }
}

void Comando::comandoRecupera(Jardim* jardim, istringstream& iss){
    string nome;
    string pasta = "Save";
    if (!(iss >> nome)) {
        cout << "Uso: apaga <nome>\n";
        return;
    }
    if (!iss.eof()) {
        cout << "Uso: recupera <nome>\n";
        return;
    }
    if (!validaNomeficheiro(nome))
        return;
    if (procuraFicheiro(nome,pasta)){
        cout << "Gravacao existente com esse nome! Por implementar comando!" << endl;
    }else {
        cout << "Gravacao com nome: " << nome << " nao existe!\n" << endl;
    }
}

void Comando::comandoApaga(istringstream& iss){
    string nome;
    string pasta = "Save";
    if (!(iss >> nome)) {
        cout << "Uso: apaga <nome>\n";
        return;
    }
    if (!iss.eof()) {
        cout << "Uso: apaga <nome>\n";
        return;
    }
    if (!validaNomeficheiro(nome)) {
        return;
    }
    if (!validaNomeficheiro(pasta)) {
        return;
    }
    if (procuraFicheiro(nome,pasta)) {
        filesystem::path ficheiro = pasta + "/" + nome + ".txt";
        if (filesystem::remove(ficheiro)) {
            cout << "Gravacao com nome: " << nome << " apagada com sucesso!\n" << endl;
        }
    }else {
        cout << "Gravacao com nome: " << nome << " nao existe!\n" << endl;
    }
}

/// CORRER UM SCRIPT
void Comando::comandoRunscript(istringstream& iss, Interface& ui) {
    string nome, linha;
    string pasta = "Script";
    if (!(iss >> nome)) {
        cout << "Uso: executa <ficheiro>\n";
        return;
    }
    if (!iss.eof()) {
        cout << "Uso: executa <ficheiro>\n";
        return;
    }
    if (!validaNomeficheiro(nome)) {
        return;
    }
    if (procuraFicheiro(nome,pasta)){
        cout << "Ficheiro com nome: " << nome << " existe!\n" << endl;
    }else {
        cout << "Ficheiro com nome: " << nome << " nao existe!\n" << endl;
        return;
    }
    filesystem::path ficheiro = pasta + "/" + nome + ".txt";

    ifstream abre(ficheiro);
    if (!abre) {
        cout << "Erro a abrir ficheiro!";
        return;
    }
    while (getline(abre, linha)) {
        if (linha.empty()) continue;
        cout << "> " << linha << endl; //simula o > da Interface para mostrar o comando que estamos a usar
        ui.processarComando(linha);
    }
}

/// AJUDA
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
         << "   Ações de jardinagem:\n"
         << "       > planta <linha> <coluna> <tipo> - Planta uma nova planta do tipo indicado na posição especificada (c, r, e, x)\n"
         << "       > colhe <linha> <coluna>         - Colhe (remove) a planta na posição indicada\n"
         << "   Ferramentas:\n"
         << "       > larga                         - Larga a ferramenta que o jardineiro tem atualmente na mão.\n"
         << "       > pega <n>                      - Pega na ferramenta com número de série n (se estiver na célula ou inventário).\n"
         << "       > compra <c>                    - Compra uma nova ferramenta do tipo c (ex.: g, a, t, z).\n"
         << " Ficheiros:\n"
         << "   > grava <nome_ficheiro>.txt         - Grava o ficheiro com o nome indicado\n"
         << "   > recupera <nome_ficheiro>.txt      - Abre o ficheiro guardado com o nome indicado\n"
         << "   > apaga <nome_ficheiro>.txt         - Apaga o ficheiro guardado com o nome indicado\n"
         << " Terminar:\n"
         << "   > fim                               - Termina o programa\n";
};

/// TERMINAR O PROGRAMA
void Comando::comandoFim(bool& ativo){
    ativo = false;
    cout << "A terminar o simulador...\n";
}

/// CONVERTER CARACTERS PARA NÚMEROS
bool Comando::converteCoordenada(const string& s, int& linha, int& coluna) {

    if (s.length() != 2)
        return false;

    char L = toupper(s[0]);
    char C = toupper(s[1]);

    if ( (L < 'A' || L > 'Z') || (C < 'A' || C > 'Z') ) {
        return false;
    }

    linha = L - 'A';
    coluna = C - 'A';

    return true;
}